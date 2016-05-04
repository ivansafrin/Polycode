import ConfigParser
import io
import os
import re

class LuaBindingsGenerator(object):

		def __init__(self, config):
			self.config = config
			self.wrappersHeaderList = ""
			self.wrappersHeaderBody = ""
			self.cppRegisterOut = ""
			self.disableGC = self.config.get('lua', 'DisableGarbageCollection').replace(" ", "").split(",")
			self.libName = self.config.get('global', 'LibraryName')

		def processTargetFile(self, targetFile):
			self.wrappersHeaderList += "#include \"%s/%s\"\n" % (self.config.get('global', 'HeaderIncludeDirectory'), targetFile)

		def processClass(self, c):
			for method in c["methods"]:
				idx = 1
				if method["name"] == c["name"]:
					self.cppRegisterOut += "\t\t{\"%s\", %s_%s},\n" % (c["name"], self.libName, c["name"])
					self.wrappersHeaderBody += "\tstatic int %s_%s(lua_State *L) {\n" % (self.libName, c["name"])
				else:
					self.cppRegisterOut += "\t\t{\"%s_%s\", %s_%s_%s},\n" % (c["name"], method["name"], self.libName, c["name"], method["name"])
					self.wrappersHeaderBody += "\tstatic int %s_%s_%s(lua_State *L) {\n" % (self.libName, c["name"], method["name"])

					# if this is not a static method, get the class pointer being passed
					if method["type"].find("static ") == -1:
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
					if param["type"] == "int" or param["type"] == "unsigned int" or param["type"] == "short":
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

					if "defaltValue" in param:
						if checkfunc != "lua_isuserdata" or (checkfunc == "lua_isuserdata" and param["defaltValue"] == "NULL"):
							#param["defaltValue"] = param["defaltValue"].replace(" 0f", ".0f")
							param["defaltValue"] = param["defaltValue"].replace(": :", "::")
							#param["defaltValue"] = param["defaltValue"].replace("0 ", "0.")
							param["defaltValue"] = re.sub(r'([0-9]+) ([0-9])+', r'\1.\2', param["defaltValue"])

							self.wrappersHeaderBody += "\t\t%s %s;\n" % (param["type"], param["name"])
							self.wrappersHeaderBody += "\t\tif(%s(L, %d)) {\n" % (checkfunc, idx)
							self.wrappersHeaderBody += "\t\t\t%s = %s(L, %d)%s;\n" % (param["name"], luafunc, idx, luafuncsuffix)
							self.wrappersHeaderBody += "\t\t} else {\n"
							self.wrappersHeaderBody += "\t\t\t%s = %s;\n" % (param["name"], param["defaltValue"])
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
					if method["type"].find("static ") == -1: # If non-static
						call = "inst->%s(%s)" % (method["name"], ", ".join(paramlist))
					else: # If static (FIXME: Why doesn't this work?)
						call = "%s::%s(%s)" % (c["name"], method["name"], ", ".join(paramlist))

					#check if returning a template
					if method["type"].find("<") > -1:
						#if returning a vector, convert to lua table
						if method["type"].find("std::vector") > -1:
							vectorReturnClass = method["type"].replace("std::vector<", "").replace(">","").replace(" ", "")
							if vectorReturnClass.find("&") == -1 and vectorReturnClass.find("*") > -1: #FIXME: return references to std::vectors and basic types
								vectorReturn = True
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
						basicType = True
						voidRet = True
						vectorReturn = False
						self.wrappersHeaderBody += "\t\treturn 0;\n" # 0 arguments returned
					else: # If there is a return value:
						# What type is the return value? Default to pointer
						outfunc = "this_shouldnt_happen"
						retFunc = ""
						basicType = False
						vectorReturn = False
						if method["type"] == "Number" or  method["type"] == "inline Number":
							outfunc = "lua_pushnumber"
							basicType = True
						if method["type"] == "String" or method["type"] == "static String": # TODO: Path for STL strings?
							outfunc = "lua_pushstring"
							basicType = True
							retFunc = ".c_str()"
						if method["type"] == "int" or method["type"] == "unsigned int" or method["type"] == "static int" or  method["type"] == "size_t" or method["type"] == "static size_t" or method["type"] == "long" or method["type"] == "unsigned int" or method["type"] == "static long" or method["type"] == "short" or method["type"] == "PolyKEY" or method["type"] == "wchar_t":
							outfunc = "lua_pushinteger"
							basicType = True
						if method["type"] == "bool" or method["type"] == "static bool" or method["type"] == "virtual bool":
							outfunc = "lua_pushboolean"
							basicType = True

						if method["type"].find("*") > -1: # Returned var is definitely a pointer.
							self.wrappersHeaderBody += "\t\tPolyBase *ptrRetVal = (PolyBase*)%s%s;\n" % (call, retFunc)
							self.wrappersHeaderBody += "\t\tif(ptrRetVal == NULL) {\n"
							self.wrappersHeaderBody += "\t\t\tlua_pushnil(L);\n"
							self.wrappersHeaderBody += "\t\t} else {\n"
							self.wrappersHeaderBody += "\t\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
							self.wrappersHeaderBody += "\t\t\t*userdataPtr = ptrRetVal;\n"
							self.wrappersHeaderBody += "\t\t}\n"
						elif basicType == True: # Returned var has been flagged as a recognized primitive type
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

		def finalize(self):
			with open(self.config.get('lua', 'WrapperHeaderTemplate'), 'r') as f:
				out = f.read().replace("%HEADERS%", self.wrappersHeaderList)
				out = out.replace("%BODY%", self.wrappersHeaderBody)
				fout = open(self.config.get('lua', 'WrapperHeaderTarget'), "w")
				fout.write(out)
				fout.close()
