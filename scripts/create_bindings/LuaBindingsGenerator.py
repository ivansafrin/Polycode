import ConfigParser
import io
import os
import re
from zipfile import *
import fnmatch
import errno

def mkdir_p(path):
	try:
		os.makedirs(path)
	except OSError as e:
		if e.errno == errno.EEXIST:
			pass
		else: raise

class LuaBindingsGenerator(object):

	def __init__(self, config):
		self.config = config
		self.wrappersHeaderList = ""
		self.wrappersHeaderBody = ""
		self.cppRegisterOut = ""
		self.luaClassBindingOut = ""
		self.cppLoaderOut = ""
		self.luaIndexOut = ""
		self.disableGC = self.config.get('lua', 'DisableGarbageCollection').replace(" ", "").split(",")
		self.inheritInModule = self.config.get('lua', 'InheritInModule').replace(" ", "").split(",")
		self.libName = self.config.get('global', 'LibraryName')

		self.cppRegisterOut += "int luaopen_%s(lua_State *L) {\n" % self.libName
		if self.libName != "Polycode" and self.libName != "Physics2D" and self.libName != "Physics3D" and self.libName != "UI":
			self.cppRegisterOut += "CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));\n"
			self.cppRegisterOut += "CoreServices::setInstance(inst);\n"
		self.cppRegisterOut += "\tstatic const luaL_Reg %sLib [] = {\n" % (self.libName)
		mkdir_p("%s/%s" % (self.config.get('lua', 'LuaApiDirectory'), self.libName))

	# ----------------------------------------------------
	# Process file
	# ----------------------------------------------------

	def processTargetFile(self, targetFile):
		self.wrappersHeaderList += "#include \"%s/%s\"\n" % (self.config.get('global', 'HeaderIncludeDirectory'), targetFile)

	# ----------------------------------------------------
	# Process class in file
	# ----------------------------------------------------

	def processClass(self, c):
		inherits = False
		parentClass = ""
		if "parent" in c:
				if c["parent"] in self.inheritInModule: # Parent class is in this module
					self.luaClassBindingOut += "require \"%s/%s\"\n\n" % (self.config.get('lua', 'LibraryName'), c["parent"])
				else: 
					self.luaClassBindingOut += "require \"%s/%s\"\n\n" % (self.config.get('lua', 'DefaultModule'), c["parent"])

				self.luaClassBindingOut += "class \"%s\" (%s)\n\n" % (c["name"], c["parent"])
				parentClass = c["parent"]
				inherits = True
		if inherits == False:
			self.luaClassBindingOut += "class \"%s\"\n\n" % c["name"]

		self.generateLuaProperties(c)
		self.generateGettersForProperties(c)
		self.generateSettersForProperties(c)

		self.generateCBindingsForMethods(c)
		self.generateLuaMethods(c)

		self.cppLoaderOut += "\n\tluaL_newmetatable(L, \"%s.%s\");\n" % (self.libName, c["name"])
		if c["name"] not in self.disableGC:
			self.cppLoaderOut += "\tlua_pushstring(L, \"__gc\");\n"
			self.cppLoaderOut += "\tlua_pushcfunction(L, %s_delete_%s);\n" % (self.libName, c["name"])
			self.cppLoaderOut += "\tlua_settable(L, -3);\n"
		self.cppLoaderOut +="\tlua_pop(L, 1);\n"

		# Delete method (C++ side)
		self.cppRegisterOut += "\t\t{\"delete_%s\", %s_delete_%s},\n" % (c["name"], self.libName, c["name"])
		self.wrappersHeaderBody += "\tstatic int %s_delete_%s(lua_State *L) {\n" % (self.libName, c["name"])
		self.wrappersHeaderBody += "\t\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
		self.wrappersHeaderBody += "\t\tPolyBase **inst = (PolyBase**)lua_touserdata(L, 1);\n"
		self.wrappersHeaderBody += "\t\tdelete ((%s*) *inst);\n" % (c["name"])
		self.wrappersHeaderBody += "\t\t*inst = NULL;\n"
		self.wrappersHeaderBody += "\t\treturn 0;\n"
		self.wrappersHeaderBody += "\t}\n\n"

		self.writeClass(c)
		self.luaIndexOut += "require \"%s/%s\"\n" % (self.libName, c["name"])

	# ----------------------------------------------------
	# Write out the C bindings for Lua property setters
	# ----------------------------------------------------

	def generateSettersForProperties(self, c):
		for pp in c["properties"]:
			if self.isBasicType(pp["type"]):
				self.cppRegisterOut += "\t\t{\"%s_set_%s\", %s_%s_set_%s},\n" % (c["name"], pp["name"], self.libName, c["name"], pp["name"])
				self.wrappersHeaderBody += "static int %s_%s_set_%s(lua_State *L) {\n" % (self.libName, c["name"], pp["name"])
				self.wrappersHeaderBody += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
				self.wrappersHeaderBody += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (c["name"], c["name"])

				outfunc = "this_shouldnt_happen"
				outfuncsuffix = ""
				if pp["type"] == "Number":
					outfunc = "lua_tonumber"
				if pp["type"] == "String":
					outfunc = "lua_tostring"
				if pp["type"] == "int":
					outfunc = "lua_tointeger"
				if pp["type"] == "PolyKEY":
					outfunc = "(PolyKEY)lua_tointeger"
				if pp["type"] == "bool":
					outfunc = "lua_toboolean"
					outfuncsuffix = " != 0"

				self.wrappersHeaderBody += "\t%s param = %s(L, 2)%s;\n" % (pp["type"], outfunc, outfuncsuffix)
				self.wrappersHeaderBody += "\tinst->%s = param;\n" % (pp["name"])

				self.wrappersHeaderBody += "\treturn 0;\n"
				self.wrappersHeaderBody += "}\n\n"
			else:
				self.cppRegisterOut += "\t\t{\"%s_set_%s\", %s_%s_set_%s},\n" % (c["name"], pp["name"], self.libName, c["name"], pp["name"])
				self.wrappersHeaderBody += "static int %s_%s_set_%s(lua_State *L) {\n" % (self.libName, c["name"], pp["name"])
				self.wrappersHeaderBody += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
				self.wrappersHeaderBody += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (c["name"], c["name"])
				self.wrappersHeaderBody += "\tluaL_checktype(L, 2, LUA_TUSERDATA);\n"
				self.wrappersHeaderBody += "\t%s *argInst = (%s*) *((PolyBase**)lua_touserdata(L, 2));\n" % (pp["type"], pp["type"])
				self.wrappersHeaderBody += "\tinst->%s = *argInst;\n" % (pp["name"])
				self.wrappersHeaderBody += "\treturn 0;\n"
				self.wrappersHeaderBody += "}\n\n"

	# ----------------------------------------------------
	# Write out the C bindings for Lua property getters
	# ----------------------------------------------------

	def generateGettersForProperties(self, c):
		for pp in c["properties"]:
			self.cppRegisterOut += "\t\t{\"%s_get_%s\", %s_%s_get_%s},\n" % (c["name"], pp["name"], self.libName, c["name"], pp["name"])
			self.wrappersHeaderBody += "static int %s_%s_get_%s(lua_State *L) {\n" % (self.libName, c["name"], pp["name"])
			self.wrappersHeaderBody += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
			self.wrappersHeaderBody += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (c["name"], c["name"])

			outfunc = "this_shouldnt_happen"
			retFunc = ""
			if pp["type"] == "Number":
				outfunc = "lua_pushnumber"
			if pp["type"] == "String":
				outfunc = "lua_pushstring"
				retFunc = ".c_str()"
			if pp["type"] == "int" or pp["type"] == "PolyKEY":
				outfunc = "lua_pushinteger"
			if pp["type"] == "bool":
				outfunc = "lua_pushboolean"

			if pp["type"] == "Number" or  pp["type"] == "String" or pp["type"] == "int" or pp["type"] == "bool" or pp["type"] == "PolyKEY":
				self.wrappersHeaderBody += "\t%s(L, inst->%s%s);\n" % (outfunc, pp["name"], retFunc)
			else:
				if pp["type"].find("*") != -1:
					self.wrappersHeaderBody += "\tif(!inst->%s%s) {\n" % (pp["name"], retFunc)
					self.wrappersHeaderBody += "\t\tlua_pushnil(L);\n"
					self.wrappersHeaderBody += "\t} else {\n"
					self.wrappersHeaderBody += "\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
					self.wrappersHeaderBody += "\t\t*userdataPtr = (PolyBase*)inst->%s%s;\n" % (pp["name"], retFunc)
					self.wrappersHeaderBody += "\t}\n"
				else:
					self.wrappersHeaderBody += "\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
					self.wrappersHeaderBody += "\t*userdataPtr = (PolyBase*)&inst->%s%s;\n" % (pp["name"], retFunc)
			self.wrappersHeaderBody += "\treturn 1;\n"
			self.wrappersHeaderBody += "}\n\n"

	# ----------------------------------------------------
	# Write out the Lua setters and getters for properties in the Lua class
	# ----------------------------------------------------

	def generateLuaProperties(self, c):
		for pp in c["staticProperties"]:
			if "defaultValue" in pp:
				defaultValue  = pp["defaultValue"]
				if re.match(r'\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\+', defaultValue):
					defaultValue = "%s.%s" % (c["name"], defaultValue)
				self.luaClassBindingOut += "%s.%s = %s\n" % (c["name"], pp["name"], defaultValue)

		self.luaClassBindingOut += "\n"
		pidx = 0
		if len(c["properties"]) > 0:
			self.luaClassBindingOut += "function %s:__getvar(name)\n" % c["name"]
			for pp in c["properties"]:
				if pidx == 0:
					self.luaClassBindingOut += "\tif name == \"%s\" then\n" % (pp["name"])
				else:
					self.luaClassBindingOut += "\telseif name == \"%s\" then\n" % (pp["name"])

				if self.isBasicType(pp["type"]):
					self.luaClassBindingOut += "\t\treturn %s.%s_get_%s(self.__ptr)\n" % (self.libName, c["name"], pp["name"])
				else:
					self.luaClassBindingOut += "\t\tlocal retVal = %s.%s_get_%s(self.__ptr)\n" % (self.libName, c["name"], pp["name"])
					self.luaClassBindingOut += self.template_returnPtrLookup("\t\t", self.template_quote(pp["type"]), "retVal")
				pidx = pidx + 1
				
			self.luaClassBindingOut += "\tend\n"
			if "parent" in c:
				self.luaClassBindingOut += "\tif %s[\"__getvar\"] ~= nil then\n" % (c["parent"])
				self.luaClassBindingOut += "\t\treturn %s.__getvar(self, name)\n" % (c["parent"])
				self.luaClassBindingOut += "\tend\n"
			self.luaClassBindingOut += "end\n\n"
			
			self.luaClassBindingOut += "function %s:__setvar(name,value)\n" % c["name"]
			pidx = 0
			for pp in c["properties"]:

				if self.isBasicType(pp["type"]) == True:
					if pidx == 0:
						self.luaClassBindingOut += "\tif name == \"%s\" then\n" % (pp["name"])
					else:
						self.luaClassBindingOut += "\telseif name == \"%s\" then\n" % (pp["name"])
					self.luaClassBindingOut += "\t\t%s.%s_set_%s(self.__ptr, value)\n" % (self.libName, c["name"], pp["name"])
					self.luaClassBindingOut += "\t\treturn true\n"
				else:
					if pidx == 0:
						self.luaClassBindingOut += "\tif name == \"%s\" then\n" % (pp["name"])
					else:
						self.luaClassBindingOut += "\telseif name == \"%s\" then\n" % (pp["name"])
					self.luaClassBindingOut += "\t\t%s.%s_set_%s(self.__ptr, value.__ptr)\n" % (self.libName, c["name"], pp["name"])
					self.luaClassBindingOut += "\t\treturn true\n"
				pidx = pidx + 1
				
			self.luaClassBindingOut += "\tend\n"
			if "parent" in c:
				self.luaClassBindingOut += "\tif %s[\"__setvar\"] ~= nil then\n" % (c["parent"])
				self.luaClassBindingOut += "\t\treturn %s.__setvar(self, name, value)\n" % (c["parent"])
				self.luaClassBindingOut += "\telse\n"
				self.luaClassBindingOut += "\t\treturn false\n"
				self.luaClassBindingOut += "\tend\n"
			else:
				self.luaClassBindingOut += "\treturn false\n"
			self.luaClassBindingOut += "end\n"

	# ----------------------------------------------------
	# Write out the Lua class file for the class
	# ----------------------------------------------------

	def writeClass(self, c):
		self.luaClassBindingOut += "function %s:__delete()\n" % (c["name"])
		self.luaClassBindingOut += "\tif self then %s.delete_%s(self.__ptr) end\n" % (self.libName, c["name"])
		self.luaClassBindingOut += "end\n"
		if c["name"] != "EventDispatcher":
			fout = open("%s/%s/%s.lua" % (self.config.get('lua', 'LuaApiDirectory'), self.libName, c["name"]), "w")
			fout.write(self.luaClassBindingOut)
			fout.close()
		self.luaClassBindingOut = ""

	# ----------------------------------------------------
	# Create The C binding wrappers for class methods
	# ----------------------------------------------------

	def generateCBindingsForMethods(self, c):
		for method in c["methods"]:
			idx = 1
			if method["name"] == c["name"]:
				self.cppRegisterOut += "\t\t{\"%s\", %s_%s},\n" % (c["name"], self.libName, c["name"])
				self.wrappersHeaderBody += "\tstatic int %s_%s(lua_State *L) {\n" % (self.libName, c["name"])
			else:
				self.cppRegisterOut += "\t\t{\"%s_%s\", %s_%s_%s},\n" % (c["name"], method["name"], self.libName, c["name"], method["name"])
				self.wrappersHeaderBody += "\tstatic int %s_%s_%s(lua_State *L) {\n" % (self.libName, c["name"], method["name"])

				# if this is not a static method, get the class pointer being passed
				if method["isStatic"] == False:
					self.wrappersHeaderBody += "\t\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
					self.wrappersHeaderBody += "\t\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (c["name"], c["name"])
					idx = 2

			paramlist = []
			lparamlist = []
			for param in method["parameters"]:
				luatype = "LUA_TUSERDATA"
				checkfunc = "lua_isuserdata"
				if param["type"].find("*") > -1:
					luafunc = "(%s) *((PolyBase**)lua_touserdata" % (param["type"].replace("Polygon", "Polycode::Polygon").replace("Rectangle", "Polycode::Rectangle"))
				elif param["type"].find("&") > -1:
					luafunc = "*(%s*) *((PolyBase**)lua_touserdata" % (param["type"].replace("const", "").replace("&", "").replace("Polygon", "Polycode::Polygon").replace("Rectangle", "Polycode::Rectangle"))
				else:
					luafunc = "*(%s*) *((PolyBase**)lua_touserdata" % (param["type"].replace("Polygon", "Polycode::Polygon").replace("Rectangle", "Polycode::Rectangle"))
				lend = ".__ptr"
				luafuncsuffix = ")"
				if param["type"] == "int":
					luafunc = "lua_tointeger"
					luatype = "LUA_TNUMBER"
					checkfunc = "lua_isnumber"
					luafuncsuffix = ""
					lend = ""
				if param["type"] == "PolyKEY":
					luafunc = "(PolyKEY)lua_tointeger"
					luatype = "LUA_TNUMBER"
					checkfunc = "lua_isnumber"
					luafuncsuffix = ""
					lend = ""
				if param["type"] == "bool":
					luafunc = "lua_toboolean"
					luatype = "LUA_TBOOLEAN"
					checkfunc = "lua_isboolean"
					luafuncsuffix = " != 0"
					lend = ""
				if param["type"] == "Number":
					luatype = "LUA_TNUMBER"
					luafunc = "lua_tonumber"
					checkfunc = "lua_isnumber"
					luafuncsuffix = ""
					lend = ""
				if param["type"] == "String":
					luatype = "LUA_TSTRING"
					luafunc = "lua_tostring"
					checkfunc = "lua_isstring"
					luafuncsuffix = ""
					lend = ""
				
				param["type"] = param["type"].replace("Polygon", "Polycode::Polygon").replace("Rectangle", "Polycode::Rectangle")

				if "defaultValue" in param:
					if checkfunc != "lua_isuserdata" or (checkfunc == "lua_isuserdata" and param["defaultValue"] == "NULL"):
						#param["defaultValue"] = param["defaultValue"].replace(" 0f", ".0f")
						param["defaultValue"] = param["defaultValue"].replace(": :", "::")
						#param["defaultValue"] = param["defaultValue"].replace("0 ", "0.")
						param["defaultValue"] = re.sub(r'([0-9]+) ([0-9])+', r'\1.\2', param["defaultValue"])

						self.wrappersHeaderBody += "\t\t%s %s;\n" % (param["type"], param["name"])
						self.wrappersHeaderBody += "\t\tif(%s(L, %d)) {\n" % (checkfunc, idx)
						self.wrappersHeaderBody += "\t\t\t%s = %s(L, %d)%s;\n" % (param["name"], luafunc, idx, luafuncsuffix)
						self.wrappersHeaderBody += "\t\t} else {\n"
						self.wrappersHeaderBody += "\t\t\t%s = %s;\n" % (param["name"], param["defaultValue"])
						self.wrappersHeaderBody += "\t\t}\n"
					else:
						self.wrappersHeaderBody += "\t\tluaL_checktype(L, %d, %s);\n" % (idx, luatype);
						if param["type"] == "String":
							self.wrappersHeaderBody += "\t\t%s %s = String(%s(L, %d));\n" % (param["type"], param["name"], luafunc, idx)
						else:
							self.wrappersHeaderBody += "\t\t%s %s = %s(L, %d)%s;\n" % (param["type"], param["name"], luafunc, idx,luafuncsuffix)
				else:
					self.wrappersHeaderBody += "\t\tluaL_checktype(L, %d, %s);\n" % (idx, luatype);
					if param["type"] == "String":
						self.wrappersHeaderBody += "\t\t%s %s = String(%s(L, %d));\n" % (param["type"], param["name"], luafunc, idx)
					else:
						self.wrappersHeaderBody += "\t\t%s %s = %s(L, %d)%s;\n" % (param["type"], param["name"], luafunc, idx, luafuncsuffix)
				paramlist.append(param["name"])
				lparamlist.append(param["name"]+lend)
				idx = idx +1 # Param parse success-- mark the increased stack

			# Generate C++-side method call / generate return value
			if method["name"] == c["name"]: # If constructor
				if c["name"] == "EventHandler": # See LuaEventHandler above
					self.wrappersHeaderBody += "\t\tLuaEventHandler *inst = new LuaEventHandler();\n"
					self.wrappersHeaderBody += "\t\tinst->wrapperIndex = luaL_ref(L, LUA_REGISTRYINDEX );\n"
					self.wrappersHeaderBody += "\t\tinst->L = L;\n"
				else:
					self.wrappersHeaderBody += "\t\t%s *inst = new %s(%s);\n" % (c["name"], c["name"], ", ".join(paramlist))
				
				self.wrappersHeaderBody += "\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
				self.wrappersHeaderBody += "\t\t*userdataPtr = (PolyBase*)inst;\n"
				self.wrappersHeaderBody += "\t\tluaL_getmetatable(L, \"%s.%s\");\n" % (self.libName, c["name"])
				self.wrappersHeaderBody += "\t\tlua_setmetatable(L, -2);\n"
				self.wrappersHeaderBody += "\t\treturn 1;\n"
			else: #If non-constructor
				if method["isStatic"] == False:
					call = "inst->%s(%s)" % (method["name"], ", ".join(paramlist))
				else:
					call = "%s::%s(%s)" % (c["name"], method["name"], ", ".join(paramlist))

				if self.isVectorType(method["type"]):
					vectorReturnClass = self.getVectorType(method["type"])
					if vectorReturnClass.find("&") == -1 and vectorReturnClass.find("*") > -1: #FIXME: return references to std::vectors and basic types
						self.wrappersHeaderBody += "\t\tstd::vector<%s> retVector = %s;\n" % (vectorReturnClass,call)
						self.wrappersHeaderBody += "\t\tlua_newtable(L);\n"
						self.wrappersHeaderBody += "\t\tfor(int i=0; i < retVector.size(); i++) {\n"
						self.wrappersHeaderBody += "\t\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
						self.wrappersHeaderBody += "\t\t\t*userdataPtr = (PolyBase*)retVector[i];\n"
						self.wrappersHeaderBody += "\t\t\tlua_rawseti(L, -2, i+1);\n"
						self.wrappersHeaderBody += "\t\t}\n"
						self.wrappersHeaderBody += "\t\treturn 1;\n"
					else:
						self.wrappersHeaderBody += "\t\treturn 0;\n"
							
				# else If void-typed:
				elif method["type"] == "void" or method["type"] == "static void" or method["type"] == "virtual void" or method["type"] == "inline void":
					self.wrappersHeaderBody += "\t\t%s;\n" % (call)
					self.wrappersHeaderBody += "\t\treturn 0;\n" # 0 arguments returned
				else: # If there is a return value:
					# What type is the return value? Default to pointer
					outfunc = "this_shouldnt_happen"
					retFunc = ""
					if method["type"] == "Number" or  method["type"] == "inline Number":
						outfunc = "lua_pushnumber"
					if method["type"] == "String" or method["type"] == "static String": # TODO: Path for STL strings?
						outfunc = "lua_pushstring"
						retFunc = ".c_str()"
					if method["type"] == "int" or method["type"] == "unsigned int" or method["type"] == "static int" or  method["type"] == "size_t" or method["type"] == "static size_t" or method["type"] == "long" or method["type"] == "unsigned int" or method["type"] == "static long" or method["type"] == "short" or method["type"] == "PolyKEY" or method["type"] == "wchar_t":
						outfunc = "lua_pushinteger"
					if method["type"] == "bool" or method["type"] == "static bool" or method["type"] == "virtual bool":
						outfunc = "lua_pushboolean"

					if method["type"].find("*") > -1: # Returned var is definitely a pointer.
						self.wrappersHeaderBody += "\t\tPolyBase *ptrRetVal = (PolyBase*)%s%s;\n" % (call, retFunc)
						self.wrappersHeaderBody += "\t\tif(ptrRetVal == NULL) {\n"
						self.wrappersHeaderBody += "\t\t\tlua_pushnil(L);\n"
						self.wrappersHeaderBody += "\t\t} else {\n"
						self.wrappersHeaderBody += "\t\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
						self.wrappersHeaderBody += "\t\t\t*userdataPtr = ptrRetVal;\n"
						self.wrappersHeaderBody += "\t\t}\n"
					elif self.isBasicType(method["type"])  == True:
						self.wrappersHeaderBody += "\t\t%s(L, %s%s);\n" % (outfunc, call, retFunc)
					else: # Some static object is being returned. Convert it to a pointer, then return that.
						className = method["type"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "")
						if className == "Polygon": # Deal with potential windows.h conflict
							className = "Polycode::Polygon"
						if className == "Rectangle":
							className = "Polycode::Rectangle"
						if className == "Polycode : : Rectangle":
							className = "Polycode::Rectangle"
						self.wrappersHeaderBody += "\t\t%s *retInst = new %s();\n" % (className, className)
						self.wrappersHeaderBody += "\t\t*retInst = %s;\n" % (call)
						self.wrappersHeaderBody += "\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
						self.wrappersHeaderBody += "\t\tluaL_getmetatable(L, \"%s.%s\");\n" % (self.libName, className)
						self.wrappersHeaderBody += "\t\tlua_setmetatable(L, -2);\n"
						self.wrappersHeaderBody += "\t\t*userdataPtr = (PolyBase*)retInst;\n"
					self.wrappersHeaderBody += "\t\treturn 1;\n"
			self.wrappersHeaderBody += "\t}\n"
	
	# ----------------------------------------------------
	# Create Lua API for all class methods
	# ----------------------------------------------------

	def generateLuaMethods(self, c):
		for method in c["methods"]:
			paramlist = []
			lparamlist = []
			for param in method["parameters"]:
				paramlist.append(param["name"])
				if not self.isBasicType(param["type"]):
					lparamlist.append("%s.__ptr" % param["name"])
				else:
					lparamlist.append(param["name"])
			if method["name"] == c["name"]: # Constructor
				self.luaClassBindingOut += "function %s:%s(...)\n" % (c["name"], c["name"])
				self.luaClassBindingOut += "\tlocal arg = {...}\n"
				if "parent" in c:
					self.luaClassBindingOut += "\tif type(arg[1]) == \"table\" and count(arg) == 1 then\n"
					self.luaClassBindingOut += "\t\tif \"\"..arg[1].__classname == \"%s\" then\n" % (c["parent"])
					self.luaClassBindingOut += "\t\t\tself.__ptr = arg[1].__ptr\n"
					self.luaClassBindingOut += "\t\t\treturn\n"
					self.luaClassBindingOut += "\t\tend\n"
					self.luaClassBindingOut += "\tend\n"
				self.luaClassBindingOut += "\tfor k,v in pairs(arg) do\n"
				self.luaClassBindingOut += "\t\tif type(v) == \"table\" then\n"
				self.luaClassBindingOut += "\t\t\tif v.__ptr ~= nil then\n"
				self.luaClassBindingOut += "\t\t\t\targ[k] = v.__ptr\n"
				self.luaClassBindingOut += "\t\t\tend\n"
				self.luaClassBindingOut += "\t\tend\n"
				self.luaClassBindingOut += "\tend\n"
				self.luaClassBindingOut += "\tif self.__ptr == nil and arg[1] ~= \"__skip_ptr__\" then\n"
				if c["name"] == "EventHandler": # See LuaEventHandler above
					self.luaClassBindingOut += "\t\tself.__ptr = %s.%s(self)\n" % (self.libName, c["name"])
				else:
					self.luaClassBindingOut += "\t\tself.__ptr = %s.%s(unpack(arg))\n" % (self.libName, c["name"])
				self.luaClassBindingOut += "\tend\n"
				self.luaClassBindingOut += "end\n\n"
			else: # Non-constructors.						
				if method["type"].find("static ") == -1: # Non-static method
					self.luaClassBindingOut += "function %s:%s(%s)\n" % (c["name"], method["name"], ", ".join(paramlist))						
					if len(lparamlist):
						self.luaClassBindingOut += "\tlocal retVal = %s.%s_%s(self.__ptr, %s)\n" % (self.libName, c["name"], method["name"], ", ".join(lparamlist))
					else:
						self.luaClassBindingOut += "\tlocal retVal =  %s.%s_%s(self.__ptr)\n" % (self.libName, c["name"], method["name"])
				else: # Static method
					self.luaClassBindingOut += "function %s.%s(%s)\n" % (c["name"], method["name"], ", ".join(paramlist))
					if len(lparamlist):
						self.luaClassBindingOut += "\tlocal retVal = %s.%s_%s(%s)\n" % (self.libName, c["name"], method["name"], ", ".join(lparamlist))
					else:
						self.luaClassBindingOut += "\tlocal retVal =  %s.%s_%s()\n" % (self.libName, c["name"], method["name"])
				if method["type"] != "void":
					if self.isBasicType(method["type"]):
						self.luaClassBindingOut += "\treturn retVal\n"
					else:
						if self.isVectorType(method["type"])  == True:
							className = self.getVectorType(method["type"]).replace("*", "")
							self.luaClassBindingOut += self.template_returnPtrLookupArray("\t",self.template_quote(className),"retVal")
						else:
							className = method["type"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "").replace("*","").replace(" ", "")
							self.luaClassBindingOut += self.template_returnPtrLookup("\t",self.template_quote(className),"retVal")
				self.luaClassBindingOut += "end\n\n"

	# ----------------------------------------------------
	# Write out final files 
	# ----------------------------------------------------

	def finalize(self):
		with open(self.config.get('lua', 'WrapperHeaderTemplate'), 'r') as f:
			out = f.read().replace("%HEADERS%", self.wrappersHeaderList)
			out = out.replace("%BODY%", self.wrappersHeaderBody)
			fout = open(self.config.get('lua', 'WrapperHeaderTarget'), "w")
			fout.write(out)
			fout.close()

		with open(self.config.get('lua', 'WrapperMainHeaderTemplate'), 'r') as f:
			out = f.read().replace("%BODY%", "int _PolyExport luaopen_%s(lua_State *L);" % self.libName)
			fout = open(self.config.get('lua', 'WrapperMainHeaderTarget'), "w")
			fout.write(out)
			fout.close()

		self.cppRegisterOut += "\t\t{NULL, NULL}\n"
		self.cppRegisterOut += "\t};\n"
		self.cppRegisterOut += "\tlua_newtable(L);\n"
		self.cppRegisterOut += "\tluaL_setfuncs (L,%sLib,0);\n" % (self.libName)
		self.cppRegisterOut += "\tlua_setglobal(L,\"%s\");" % (self.libName)
		self.cppRegisterOut += self.cppLoaderOut
		self.cppRegisterOut += "\treturn 1;\n"
		self.cppRegisterOut += "}"

		with open(self.config.get('lua', 'WrapperSourceTemplate'), 'r') as f:
			out = f.read().replace("%BODY%", self.cppRegisterOut)
			fout = open(self.config.get('lua', 'WrapperSourceTarget'), "w")
			fout.write(out)
			fout.close()

		fout = open("%s/%s.lua" % (self.config.get('lua', 'LuaApiDirectory'), self.libName), "w")
		fout.write(self.luaIndexOut)
		fout.close()

		pattern = '*.lua'
		curDir = os.path.dirname(os.path.realpath(__file__))
		os.chdir(self.config.get('lua', 'LuaApiDirectory'))
		with ZipFile("lua_%s.pak" % (self.libName), 'w') as myzip:
			for root, dirs, files in os.walk("."):
				for filename in fnmatch.filter(files, pattern):
					myzip.write(os.path.join(root, filename))
		os.chdir(curDir)

	# ----------------------------------------------------
	# Utility methods
	# ----------------------------------------------------

	def isVectorType(self, t):
		if t.find("<") > -1 and t.find("vector") > -1:
			return True
		else:
			return False
	
	def getVectorType(self, t):
		return t.replace("std::", "").replace("vector<", "").replace(">","").replace(" ", "")

	def isBasicType(self, t):
		basicTypes = ["int", "Number", "String", "PolyKEY", "bool"]
		if t in basicTypes:
			return True
		else:
			return False

	def template_returnPtrLookupArray(self, prefix, className, ptr):
		out = "%sif %s == nil then return nil end\n" % (prefix, ptr)
		out += "%sfor i=1,count(%s) do\n" % (prefix, ptr)
		out += "%s\tlocal __c  = _G[%s](\"__skip_ptr__\")\n" % (prefix, className.replace("*", ""))
		out += "%s\t__c.__ptr = %s[i]\n" % (prefix, ptr)
		out += "%s\t%s[i] = __c\n" % (prefix, ptr)
		out += "%send\n" % (prefix)
		out += "%sreturn %s\n" % (prefix,ptr)
		return out

	def template_returnPtrLookup(self, prefix, className, ptr):
		out = "%sif %s == nil then return nil end\n" % (prefix, ptr)
		out += "%slocal __c = _G[%s](\"__skip_ptr__\")\n" % (prefix, className.replace("*", ""))
		out += "%s__c.__ptr = %s\n" % (prefix, ptr)
		out += "%sreturn __c\n" % (prefix)
		return out

	def template_quote(self, str):
		return "\"%s\"" % str;

