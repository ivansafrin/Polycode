import sys
import CppHeaderParser
import os
import errno
import re
from zipfile import *
import fnmatch
import re

def mkdir_p(path): # Same effect as mkdir -p, create dir and all necessary parent dirs
	try:
		os.makedirs(path)
	except OSError as e:
		if e.errno == errno.EEXIST: # Dir already exists; not really an error
			pass
		else: raise

def template_returnPtrLookupArray(prefix, className, ptr):
	out = "%sif %s == nil then return nil end\n" % (prefix, ptr)
	out += "%sfor i=1,count(%s) do\n" % (prefix, ptr)
	out += "%s\tlocal __c  = _G[%s](\"__skip_ptr__\")\n" % (prefix, className.replace("*", ""))
	out += "%s\t__c.__ptr = %s[i]\n" % (prefix, ptr)
	out += "%s\t%s[i] = __c\n" % (prefix, ptr)
	out += "%send\n" % (prefix)
	out += "%sreturn %s\n" % (prefix,ptr)
	return out

# Note we expect className to be a valid string
def template_returnPtrLookup(prefix, className, ptr):
	out = "%sif %s == nil then return nil end\n" % (prefix, ptr)
	out += "%slocal __c = _G[%s](\"__skip_ptr__\")\n" % (prefix, className.replace("*", ""))
	out += "%s__c.__ptr = %s\n" % (prefix, ptr)
	out += "%sreturn __c\n" % (prefix)
	return out
	
def template_quote(str):
	return "\"%s\"" % str;

def cleanDocs(docs):
	return docs.replace("/*", "").replace("*/", "").replace("*", "").replace("\n", "").replace("\r", "").replace("::", ".").replace("\t", "")

def toLuaType(t):
	return t.replace("void", "nil").replace("int", "Integer").replace("bool", "Boolean").replace("*", "")

# FIXME: Some "unsigned int *" functions are still being generated on the polycode API?
def typeFilter(ty):
	ty = ty.replace("Polycode::", "")
	ty = ty.replace("std::", "")
	ty = ty.replace("const", "")
	ty = ty.replace("inline", "")
	ty = ty.replace("static", "")
	ty = ty.replace("virtual", "")
	ty = ty.replace("&", "")
	ty = re.sub(r'^.*\sint\s*$', 'int', ty) # eg "unsigned int"
	ty = re.sub(r'^.*\schar\s*$', 'char', ty) # eg "unsigned int"
	ty = re.sub(r'^.*\slong\s*$', 'int', ty)
	ty = re.sub(r'^.*\swchar_t\s*$', 'int', ty)
	ty = re.sub(r'^.*\sshort\s*$', 'int', ty)
	ty = re.sub(r'^.*\sfloat\s*$', 'Number', ty)
	ty = re.sub(r'^.*\sdouble\s*$', 'Number', ty) # eg "long double"
	ty = ty.replace("unsigned", "int")
	ty = ty.replace("long", "int")
	ty = ty.replace("float", "Number")
	ty = ty.replace("double", "Number")
	ty = ty.replace(" ", "") # Not very safe!
	return ty

def createLUABindings(inputPath, prefix, mainInclude, libSmallName, libName, apiPath, apiClassPath, includePath, sourcePath, luaDocPath, inheritInModuleFiles):
	wrappersHeaderOut = "" # Def: Global C++ *LUAWrappers.h
	cppRegisterOut = "" # Def: Global C++ *LUA.cpp
	cppLoaderOut = "" # Def: Global C++ *LUA.cpp
	luaDocOut = ""	

	luaIndexOut = "" # Def: Global Lua everything-gets-required-from-this-file file
	
	# Header boilerplate for wrappersHeaderOut and cppRegisterOut
	cppRegisterOut += "#include \"%sLUA.h\"\n" % (prefix)
	cppRegisterOut += "#include \"%sLUAWrappers.h\"\n" % (prefix)
	cppRegisterOut += "#include \"PolyCoreServices.h\"\n\n"
	cppRegisterOut += "using namespace Polycode;\n\n"
	cppRegisterOut += "int luaopen_%s(lua_State *L) {\n" % (prefix)

	if prefix != "Polycode" and prefix != "Physics2D" and prefix != "Physics3D" and prefix != "UI":
		cppRegisterOut += "CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));\n"
		cppRegisterOut += "CoreServices::setInstance(inst);\n"
	cppRegisterOut += "\tstatic const struct luaL_reg %sLib [] = {" % (libSmallName)
	
	wrappersHeaderOut += "#pragma once\n\n"

	wrappersHeaderOut += "extern \"C\" {\n\n"
	wrappersHeaderOut += "#include <stdio.h>\n"
	wrappersHeaderOut += "#include \"lua.h\"\n"
	wrappersHeaderOut += "#include \"lualib.h\"\n"
	wrappersHeaderOut += "#include \"lauxlib.h\"\n"
	wrappersHeaderOut += "#undef near\n"
	wrappersHeaderOut += "#undef far\n"
	wrappersHeaderOut += "} // extern \"C\" \n\n"

	luaDocOut += "<?xml version=\"1.0\" ?>\n"
	luaDocOut += "<docs>\n"
	luaDocOut += "<classes>\n"


	# Get list of headers to create bindings from
	inputPathIsDir = os.path.isdir(inputPath)
	if inputPathIsDir:
		files = os.listdir(inputPath)
	else:
		files = []
		with open(inputPath) as f:
			for line in f.readlines():
				files.append(line.strip()) # Strip whitespace, path/
	filteredFiles = []
	for fileName in files:
		if inputPathIsDir:
			fileName = "%s/%s" % (inputPath, fileName)
		if os.path.isdir(fileName):
			continue
		head, tail = os.path.split(fileName)
		ignore = ["PolyTween", "PolyTweenManager", "PolyGLSLProgram", "PolyGLSLShader", "PolyGLSLShaderModule", "PolyWinCore", "PolyCocoaCore", "PolyAGLCore", "PolySDLCore", "Poly_iPhone", "PolyGLES1Renderer", "PolyGLRenderer", "tinyxml", "tinystr", "OpenGLCubemap", "PolyiPhoneCore", "PolyGLES1Texture", "PolyGLTexture", "PolyGLVertexBuffer", "PolyThreaded", "PolyGLHeaders", "GLee", "PolyPeer", "PolySocket", "PolyClient", "PolyServer", "PolyServerWorld", "OSFILE", "OSFileEntry", "OSBasics", "PolyLogger", "PolyFontGlyphSheet"]
		if tail.split(".")[1] == "h" and tail.split(".")[0] not in ignore:
			filteredFiles.append(fileName)
			wrappersHeaderOut += "#include \"%s\"\n" % (tail)

	wrappersHeaderOut += "\nusing namespace std;\n\n"
	wrappersHeaderOut += "\nnamespace Polycode {\n\n"
	

	# list of classes that don't get the garbage collection in their meta table

	disable_gc = ["Entity","SceneLabel", "SceneMesh", "Scene", "Texture", "Image", "Camera", "SceneParticleEmitter", "Mesh", "Vertex", "Polygon", "Polycode::Polygon", "Material", "ScenePrimitive", "SceneLine", "SceneLight", "SceneSound", "SceneImage", "SceneEntity", "SceneEntityInstance", "SceneSprite"]

	# Special case: If we are building the Polycode library itself, inject the LuaEventHandler class.
	# Note: so that event callbacks can work, any object inheriting from EventHandler will secretly
	# be modified to actually inherit from LuaEventHandler instead.
	if prefix == "Polycode":
		wrappersHeaderOut += "class LuaEventHandler : public EventHandler {\n"
		wrappersHeaderOut += "public:\n"
		wrappersHeaderOut += "	LuaEventHandler() : EventHandler() {}\n"
		wrappersHeaderOut += "	void handleEvent(Event *e) {\n"
		wrappersHeaderOut += "		lua_getfield (L, LUA_GLOBALSINDEX, \"__customError\");\n"
		wrappersHeaderOut += "		int errH = lua_gettop(L);\n"
		wrappersHeaderOut += "		lua_getfield(L, LUA_GLOBALSINDEX, \"__handleEvent\");\n"
		wrappersHeaderOut += "		lua_rawgeti( L, LUA_REGISTRYINDEX, wrapperIndex );\n"
		wrappersHeaderOut += "		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
		wrappersHeaderOut += "		*userdataPtr = (PolyBase*)e;\n"
		wrappersHeaderOut += "		lua_pcall(L, 2, 0, errH);\n"
		wrappersHeaderOut += "		lua_settop(L, 0);\n"
		wrappersHeaderOut += "	}\n"
		wrappersHeaderOut += "	int wrapperIndex;\n"
		wrappersHeaderOut += "	lua_State *L;\n"
		wrappersHeaderOut += "};\n\n"
	
	# Iterate, process each input file
	for fileName in filteredFiles:
		# "Package owned" classes that ship with Polycode
		inheritInModule = ["PhysicsGenericConstraint", "PhysicsHingeConstraint", "PhysicsPointToPointConstraint", "PhysicsConstraint", "PhysicsEntity", "CollisionScene", "CollisionEntity", "UIElement", "UIWindow", "UIMenuItem", "UIImage", "UIRect"]
		
		# A file or comma-separated list of files can be given to specify classes which are "package owned"
		# and should not be inherited out of Polycode/. The files should contain one class name per line,
		# and the class name may be prefixed with a path (which will be ignored).
		if inheritInModuleFiles:
			for moduleFileName in inheritInModuleFiles.split(","):
				with open(moduleFileName) as f:
					for line in f.readlines():
						inheritInModule.append(line.strip().split("/",1)[-1]) # Strip whitespace, path/
		
		print("Parsing %s" % fileName)
		try: # One input file parse.
			f = open(fileName) # Def: Input file handle
			contents = f.read().replace("_PolyExport", "") # Def: Input file contents, strip out "_PolyExport"
			cppHeader = CppHeaderParser.CppHeader(contents, "string") # Def: Input file contents, parsed structure
			ignore_classes = ["PolycodeShaderModule", "Object", "Threaded", "OpenGLCubemap", "PolyBase", "Matrix4::union "]

			# Iterate, check each class in this file.
			for ckey in cppHeader.classes: 
				print(">> Parsing class %s" % ckey)
				c = cppHeader.classes[ckey] # Def: The class structure

				luaClassBindingOut = "" # Def: The local lua file to generate for this class.
				inherits = False
				parentClass = ""
				if len(c["inherits"]) > 0: # Does this class have parents?
					if c["inherits"][0]["class"] not in ignore_classes:

						if c["inherits"][0]["class"] in inheritInModule: # Parent class is in this module
							luaClassBindingOut += "require \"%s/%s\"\n\n" % (prefix, c["inherits"][0]["class"])
						else: # Parent class is in Polycore
							luaClassBindingOut += "require \"Polycode/%s\"\n\n" % (c["inherits"][0]["class"])

						luaClassBindingOut += "class \"%s\" (%s)\n\n" % (ckey, c["inherits"][0]["class"])
						parentClass = c["inherits"][0]["class"]
						inherits = True
				if inherits == False: # Class does not have parents
					luaClassBindingOut += "class \"%s\"\n\n" % ckey

				if ckey in ignore_classes:
					print("INGORING class %s" % ckey)
					continue

				#if len(c["methods"]["public"]) < 2: # Used to, this was a continue.
				#	print("Warning: Lua-binding class with less than two methods")
				#	continue # FIXME: Remove this, move any non-compileable classes into ignore_classes

				extendString = ""
				if len(c["inherits"]) > 0:
					if c["inherits"][0]["class"] != "PolyBase":
						extendString = " extends=\"%s\"" % (c["inherits"][0]["class"])
				
				luaDocOut += "\t<class name=\"%s\"%s>\n" % (ckey, extendString)

				if 'doxygen' in c:
					luaDocOut += "\t\t<desc><![CDATA[%s]]></desc>\n" % (cleanDocs(c['doxygen']))

				if ckey in disable_gc:
					luaDocOut += "\t\t<class_notes>NOTE: %s instances are not automatically garbage collected.</class_notes>\n" % (ckey)
				
				parsed_methods = [] # Def: List of discovered methods
				ignore_methods = ["readByte32", "readByte16", "getCustomEntitiesByType", "Core", "Renderer", "Shader", "Texture", "handleEvent", "secondaryHandler", "getSTLString", "readInt"]
				luaClassBindingOut += "\n\n"

				luaDocOut += "\t\t<static_members>\n"
				classProperties = [] # Def: List of found property structures ("properties" meaning "data members")
				for pp in c["properties"]["public"]:
					pp["type"] = pp["type"].replace("Polycode::", "")
					pp["type"] = pp["type"].replace("std::", "")
					if pp["type"].find("POLYIGNORE") != -1:
						continue
					if pp["type"].find("static ") != -1: # If static. FIXME: Static doesn't work?
						if "defaltValue" in pp: # FIXME: defaltValue is misspelled.
							defaltValue = pp["defaltValue"]
							
							# The "Default Value" is more or less a literal C++ string. This causes a problem:
							# Frequently we say static const int A = 1; static const int B = A + 1.
							# Put in a one-off hack to ensure namespacing works in this special case.
							if re.match(r'\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\+', defaltValue):
								defaltValue = "%s.%s" % (ckey, defaltValue)
							
							luaClassBindingOut += "%s.%s = %s\n" % (ckey, pp["name"], defaltValue)
							luaDocOut += "\t\t\t<static_member name=\"%s\" type=\"%s\" value=\"%s\">\n" % (pp["name"],  toLuaType(typeFilter(pp["type"])), pp["defaltValue"])
							if 'doxygen' in pp:
								luaDocOut += "\t\t\t\t<desc><![CDATA[%s]]></desc>\n" % (cleanDocs(pp['doxygen']))
							luaDocOut += "\t\t\t</static_member>\n"
					else: # FIXME: Nonstatic method ? variable ?? found.
						#there are some bugs in the class parser that cause it to return junk
						if pp["type"].find("vector") == -1 and pp["name"] != "setScale" and pp["name"] != "setPosition" and pp["name"] != "BUFFER_CACHE_PRECISION" and not pp["name"].isdigit():
							classProperties.append(pp)

				luaDocOut += "\t\t</static_members>\n"


				# Iterate over properties, creating getters
				pidx = 0 # Def: Count of properties processed so far

				# TODO: Remove or generalize ParticleEmitter special casing. These lines are marked with #SPEC

				luaDocOut += "\t\t<members>\n"

				numGetVars = 0
				if len(classProperties) > 0: # If there are properties, add index lookup to the metatable
					luaClassBindingOut += "function %s:__getvar(name)\n" % ckey
					# Iterate over property structures, creating if/else clauses for each.
					# TODO: Could a table be more appropriate for 
					for pp in classProperties:
						if pp["name"] == "" or pp["array"] == 1:
							continue

						numGetVars = numGetVars + 1

						pp["type"] = typeFilter(pp["type"])
						if pidx == 0:
							luaClassBindingOut += "\tif name == \"%s\" then\n" % (pp["name"])
						else:
							luaClassBindingOut += "\telseif name == \"%s\" then\n" % (pp["name"])

						# Generate Lua side of binding:

						# If type is a primitive such as Number/String/int/bool
						if pp["type"] == "PolyKEY" or pp["type"] == "Number" or  pp["type"] == "String" or pp["type"] == "int" or pp["type"] == "bool":
							luaClassBindingOut += "\t\treturn %s.%s_get_%s(self.__ptr)\n" % (libName, ckey, pp["name"])
							
						# If type is a particle emitter, specifically #SPEC
						elif (ckey == "ScreenParticleEmitter" or ckey == "SceneParticleEmitter") and pp["name"] == "emitter":
							luaClassBindingOut += "\t\tlocal ret = %s(\"__skip_ptr__\")\n" % (pp["type"])
							luaClassBindingOut += "\t\tret.__ptr = self.__ptr\n"
							luaClassBindingOut += "\t\treturn ret\n"
							
						# If type is a class
						else:
							luaClassBindingOut += "\t\tlocal retVal = %s.%s_get_%s(self.__ptr)\n" % (libName, ckey, pp["name"])
							luaClassBindingOut += template_returnPtrLookup("\t\t", template_quote(pp["type"]), "retVal")

						
						luaDocOut += "\t\t\t<member name=\"%s\" type=\"%s\">\n" % (pp["name"],  toLuaType(typeFilter(pp["type"])))
						if 'doxygen' in pp:
							luaDocOut += "\t\t\t\t<desc><![CDATA[%s]]></desc>\n" % (cleanDocs(pp['doxygen']))
						
						luaDocOut += "\t\t\t</member>\n"

						# Generate C++ side of binding:
						if not ((ckey == "ScreenParticleEmitter" or ckey == "SceneParticleEmitter") and pp["name"] == "emitter"): #SPEC
							cppRegisterOut += "\t\t{\"%s_get_%s\", %s_%s_get_%s},\n" % (ckey, pp["name"], libName, ckey, pp["name"])
							wrappersHeaderOut += "static int %s_%s_get_%s(lua_State *L) {\n" % (libName, ckey, pp["name"])
							wrappersHeaderOut += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
							wrappersHeaderOut += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (ckey, ckey)

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
								wrappersHeaderOut += "\t%s(L, inst->%s%s);\n" % (outfunc, pp["name"], retFunc)
							else:
								if pp["type"].find("*") != -1:
									wrappersHeaderOut += "\tif(!inst->%s%s) {\n" % (pp["name"], retFunc)
									wrappersHeaderOut += "\t\tlua_pushnil(L);\n"
									wrappersHeaderOut += "\t} else {\n"
									wrappersHeaderOut += "\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
									wrappersHeaderOut += "\t\t*userdataPtr = (PolyBase*)inst->%s%s;\n" % (pp["name"], retFunc)
									wrappersHeaderOut += "\t}\n"
								else:
									wrappersHeaderOut += "\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
									wrappersHeaderOut += "\t*userdataPtr = (PolyBase*)&inst->%s%s;\n" % (pp["name"], retFunc)
							wrappersHeaderOut += "\treturn 1;\n"
							wrappersHeaderOut += "}\n\n"
						
						# Success
						pidx = pidx + 1
					if numGetVars != 0:
						luaClassBindingOut += "\tend\n"
					if inherits:
						luaClassBindingOut += "\tif %s[\"__getvar\"] ~= nil then\n" % (parentClass)
						luaClassBindingOut += "\t\treturn %s.__getvar(self, name)\n" % (parentClass)
						luaClassBindingOut += "\tend\n"
					luaClassBindingOut += "end\n"

				luaDocOut += "\t\t</members>\n"

				luaClassBindingOut += "\n\n"
				
				# Iterate over properties again, creating setters
				pidx = 0 # Def: Count of 
				if len(classProperties) > 0: # If there are properties, add index setter to the metatable
					luaClassBindingOut += "function %s:__setvar(name,value)\n" % ckey
					for pp in classProperties:
						if pp["name"] == "" or pp["array"] == 1:
							continue
						pp["type"] = typeFilter(pp["type"])
						
						# If type is a primitive: Create lua and C++ sides at the same time.
						if pp["type"] == "Number" or  pp["type"] == "String" or pp["type"] == "int" or pp["type"] == "bool" or pp["type"] == "PolyKEY":
							if pidx == 0:
								luaClassBindingOut += "\tif name == \"%s\" then\n" % (pp["name"])
							else:
								luaClassBindingOut += "\telseif name == \"%s\" then\n" % (pp["name"])
							luaClassBindingOut += "\t\t%s.%s_set_%s(self.__ptr, value)\n" % (libName, ckey, pp["name"])
							luaClassBindingOut += "\t\treturn true\n"

							cppRegisterOut += "\t\t{\"%s_set_%s\", %s_%s_set_%s},\n" % (ckey, pp["name"], libName, ckey, pp["name"])
							wrappersHeaderOut += "static int %s_%s_set_%s(lua_State *L) {\n" % (libName, ckey, pp["name"])
							wrappersHeaderOut += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
							wrappersHeaderOut += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (ckey, ckey)

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

							wrappersHeaderOut += "\t%s param = %s(L, 2)%s;\n" % (pp["type"], outfunc, outfuncsuffix)
							wrappersHeaderOut += "\tinst->%s = param;\n" % (pp["name"])

							wrappersHeaderOut += "\treturn 0;\n"
							wrappersHeaderOut += "}\n\n"
							pidx = pidx + 1 # Success
						else:
							if pp["type"].find("*") == -1 and pp["type"].find("static") == -1:
								if pidx == 0:
									luaClassBindingOut += "\tif name == \"%s\" then\n" % (pp["name"])
								else:
									luaClassBindingOut += "\telseif name == \"%s\" then\n" % (pp["name"])
								luaClassBindingOut += "\t\t%s.%s_set_%s(self.__ptr, value.__ptr)\n" % (libName, ckey, pp["name"])
								luaClassBindingOut += "\t\treturn true\n"
							
								cppRegisterOut += "\t\t{\"%s_set_%s\", %s_%s_set_%s},\n" % (ckey, pp["name"], libName, ckey, pp["name"])
								wrappersHeaderOut += "static int %s_%s_set_%s(lua_State *L) {\n" % (libName, ckey, pp["name"])
								wrappersHeaderOut += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
								wrappersHeaderOut += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (ckey, ckey)
								wrappersHeaderOut += "\tluaL_checktype(L, 2, LUA_TUSERDATA);\n"
								wrappersHeaderOut += "\t%s *argInst = (%s*) *((PolyBase**)lua_touserdata(L, 2));\n" % (typeFilter(pp["type"]), typeFilter(pp["type"]))
								wrappersHeaderOut += "\tinst->%s = *argInst;\n" % (pp["name"])
								wrappersHeaderOut += "\treturn 0;\n"
								wrappersHeaderOut += "}\n\n"
								pidx = pidx + 1 # Success
							
						# Notice: Setters for object types are not created.
					if pidx != 0:
						luaClassBindingOut += "\tend\n"
					if inherits:
						luaClassBindingOut += "\tif %s[\"__setvar\"] ~= nil then\n" % (parentClass)
						luaClassBindingOut += "\t\treturn %s.__setvar(self, name, value)\n" % (parentClass)
						luaClassBindingOut += "\telse\n"
						luaClassBindingOut += "\t\treturn false\n"
						luaClassBindingOut += "\tend\n"
					else:
						luaClassBindingOut += "\treturn false\n"
					luaClassBindingOut += "end\n"

				# Iterate over methods
				luaClassBindingOut += "\n\n"
				
				luaDocOut += "\t\t<methods>\n"

				for pm in c["methods"]["public"]:
					# Skip argument-overloaded methods and operators.
					# TODO: Instead of skipping arguemnt overloads, have special behavior.
					# TODO: Instead of skipping operators, add to metatable.
					if pm["name"] in parsed_methods or pm["name"].find("operator") > -1 or pm["rtnType"].find("POLYIGNORE") > -1 or pm["name"] in ignore_methods:
						continue

					# Skip destructors and methods which return templates.
					# TODO: Special-case certain kind of vector<>s?
					if pm["name"] == "~"+ckey or pm["name"] == "CoreServices":
						continue
					
					staticString = ""
					if pm["rtnType"].find("static ") != -1:
						staticString = " static=\"true\""
					
					if pm["rtnType"].find("std::vector") > -1:
						vectorReturnClass = pm["rtnType"].replace("std::vector<", "").replace(">","").replace(" ", "")
						luaDocOut += "\t\t\t<method name=\"%s\" return_array=\"true\" return_type=\"%s\"%s>\n" % (pm["name"],  toLuaType(typeFilter(vectorReturnClass).replace("*", "")), staticString)
					else:
						luaDocOut += "\t\t\t<method name=\"%s\" return_type=\"%s\"%s>\n" % (pm["name"],  toLuaType(typeFilter(pm["rtnType"].replace("*", ""))), staticString)

					docs = None
					if 'doxygen' in pm:
						if pm['doxygen'].find("@return") > -1:
							docs = cleanDocs(pm['doxygen']).split("@return")[0].split("@param")
						else:
							docs = cleanDocs(pm['doxygen']).split("@param")
						luaDocOut += "\t\t\t\t<desc><![CDATA[%s]]></desc>\n" % (docs[0])
						
					if len(pm["parameters"]) > 0:
						luaDocOut += "\t\t\t\t<params>\n"
						
						paramIndex = 0
						for param in pm["parameters"]:
							if "name" in param:
								if not "type" in param:
									continue
								if param["type"] == "0":
									continue
								if param["type"].find("vector<") != -1:
									vectorClass = param["type"].replace("std::vector<", "").replace(">","").replace(" ", "")
									luaDocOut += "\t\t\t\t\t<param name=\"%s\" param_array=\"true\" type=\"%s\">\n" % (param["name"], toLuaType(vectorClass.replace("*","")))
								else:
									luaDocOut += "\t\t\t\t\t<param name=\"%s\" type=\"%s\">\n" % (param["name"], toLuaType(typeFilter(param["type"]).replace("*","")))
								if docs != None:
									if len(docs) > paramIndex+1:
										cdoc = docs[paramIndex+1].split()
										cdoc.pop(0)
										luaDocOut += "\t\t\t\t\t\t<desc><![CDATA[%s]]></desc>\n" % (" ".join(cdoc).replace("\n", ""))
								luaDocOut += "\t\t\t\t\t</param>\n"
								paramIndex = paramIndex + 1
						luaDocOut += "\t\t\t\t</params>\n"
								
						
					luaDocOut += "\t\t\t</method>\n"

					basicType = False
					voidRet = False
					vectorReturn = False
					vectorReturnClass = ""
					# Def: True if method takes a lua_State* as argument (i.e.: no preprocessing by us)
					rawMethod = len(pm["parameters"]) > 0 and pm["parameters"][0].get("type","").find("lua_State") > -1

					# Basic setup, C++ side: Add function to registry and start building wrapper function.
					if pm["name"] == ckey: # It's a constructor
						cppRegisterOut += "\t\t{\"%s\", %s_%s},\n" % (ckey, libName, ckey)
						wrappersHeaderOut += "static int %s_%s(lua_State *L) {\n" % (libName, ckey)
						idx = 1 # Def: Current stack depth (TODO: Figure out, is this correct?)
					else: # It's not a constructor
						cppRegisterOut += "\t\t{\"%s_%s\", %s_%s_%s},\n" % (ckey, pm["name"], libName, ckey, pm["name"])
						wrappersHeaderOut += "static int %s_%s_%s(lua_State *L) {\n" % (libName, ckey, pm["name"])

						# Skip static methods (TODO: Figure out, why is this being done here?). # FIXME
						if pm["rtnType"].find("static ") == -1:
							wrappersHeaderOut += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
							wrappersHeaderOut += "\t%s *inst = (%s*) *((PolyBase**)lua_touserdata(L, 1));\n" % (ckey, ckey)
							idx = 2
						else:
							idx = 1
					
					if rawMethod:
						wrappersHeaderOut += "\treturn inst->%s(L);\n" % (pm["name"])
					else:	
						# Generate C++ side parameter pushing
						paramlist = []
						lparamlist = []
						for param in pm["parameters"]:
							if not "type" in param:
								continue
							if param["type"] == "0":
								continue
								
							param["type"] = typeFilter(param["type"])

							param["name"] = param["name"].replace("end", "_end").replace("repeat", "_repeat")
							if"type" in param:
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
								if param["type"] == "Number" or param["type"] == "float" or param["type"] == "double":
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

										wrappersHeaderOut += "\t%s %s;\n" % (param["type"], param["name"])
										wrappersHeaderOut += "\tif(%s(L, %d)) {\n" % (checkfunc, idx)
										wrappersHeaderOut += "\t\t%s = %s(L, %d)%s;\n" % (param["name"], luafunc, idx, luafuncsuffix)
										wrappersHeaderOut += "\t} else {\n"
										wrappersHeaderOut += "\t\t%s = %s;\n" % (param["name"], param["defaltValue"])
										wrappersHeaderOut += "\t}\n"
									else:
										wrappersHeaderOut += "\tluaL_checktype(L, %d, %s);\n" % (idx, luatype);
										if param["type"] == "String":
											wrappersHeaderOut += "\t%s %s = String(%s(L, %d));\n" % (param["type"], param["name"], luafunc, idx)
										else:
											wrappersHeaderOut += "\t%s %s = %s(L, %d)%s;\n" % (param["type"], param["name"], luafunc, idx,luafuncsuffix)
								else:
									wrappersHeaderOut += "\tluaL_checktype(L, %d, %s);\n" % (idx, luatype);
									if param["type"] == "String":
										wrappersHeaderOut += "\t%s %s = String(%s(L, %d));\n" % (param["type"], param["name"], luafunc, idx)
									else:
										wrappersHeaderOut += "\t%s %s = %s(L, %d)%s;\n" % (param["type"], param["name"], luafunc, idx, luafuncsuffix)
								paramlist.append(param["name"])

								lparamlist.append(param["name"]+lend)
								idx = idx +1 # Param parse success-- mark the increased stack

						# Generate C++-side method call / generate return value
						if pm["name"] == ckey: # If constructor
							if ckey == "EventHandler": # See LuaEventHandler above
								wrappersHeaderOut += "\tLuaEventHandler *inst = new LuaEventHandler();\n"
								wrappersHeaderOut += "\tinst->wrapperIndex = luaL_ref(L, LUA_REGISTRYINDEX );\n"
								wrappersHeaderOut += "\tinst->L = L;\n"
							else:
								wrappersHeaderOut += "\t%s *inst = new %s(%s);\n" % (ckey, ckey, ", ".join(paramlist))
							
							wrappersHeaderOut += "\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
							wrappersHeaderOut += "\t*userdataPtr = (PolyBase*)inst;\n"
							wrappersHeaderOut += "\tluaL_getmetatable(L, \"%s.%s\");\n" % (libName, ckey)
							wrappersHeaderOut += "\tlua_setmetatable(L, -2);\n"
							wrappersHeaderOut += "\treturn 1;\n"
						else: #If non-constructor
							if pm["rtnType"].find("static ") == -1: # If non-static
								call = "inst->%s(%s)" % (pm["name"], ", ".join(paramlist))
							else: # If static (FIXME: Why doesn't this work?)
								call = "%s::%s(%s)" % (ckey, pm["name"], ", ".join(paramlist))

							#check if returning a template
							if pm["rtnType"].find("<") > -1:
								#if returning a vector, convert to lua table
								if pm["rtnType"].find("std::vector") > -1:
									vectorReturnClass = pm["rtnType"].replace("std::vector<", "").replace(">","").replace(" ", "")
									if vectorReturnClass.find("&") == -1 and vectorReturnClass.find("*") > -1: #FIXME: return references to std::vectors and basic types
										vectorReturn = True
										wrappersHeaderOut += "\tstd::vector<%s> retVector = %s;\n" % (vectorReturnClass,call)
										wrappersHeaderOut += "\tlua_newtable(L);\n"
										wrappersHeaderOut += "\tfor(int i=0; i < retVector.size(); i++) {\n"
										wrappersHeaderOut += "\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
										wrappersHeaderOut += "\t\t*userdataPtr = (PolyBase*)retVector[i];\n"
										wrappersHeaderOut += "\t\tlua_rawseti(L, -2, i+1);\n"
										wrappersHeaderOut += "\t}\n"
										wrappersHeaderOut += "\treturn 1;\n"
									else:
										wrappersHeaderOut += "\treturn 0;\n"
										
							# else If void-typed:
							elif pm["rtnType"] == "void" or pm["rtnType"] == "static void" or pm["rtnType"] == "virtual void" or pm["rtnType"] == "inline void":
								wrappersHeaderOut += "\t%s;\n" % (call)
								basicType = True
								voidRet = True
								vectorReturn = False
								wrappersHeaderOut += "\treturn 0;\n" # 0 arguments returned
							else: # If there is a return value:
								# What type is the return value? Default to pointer
								outfunc = "this_shouldnt_happen"
								retFunc = ""
								basicType = False
								vectorReturn = False
								if pm["rtnType"] == "Number" or  pm["rtnType"] == "inline Number":
									outfunc = "lua_pushnumber"
									basicType = True
								if pm["rtnType"] == "String" or pm["rtnType"] == "static String": # TODO: Path for STL strings?
									outfunc = "lua_pushstring"
									basicType = True
									retFunc = ".c_str()"
								if pm["rtnType"] == "int" or pm["rtnType"] == "unsigned int" or pm["rtnType"] == "static int" or  pm["rtnType"] == "size_t" or pm["rtnType"] == "static size_t" or pm["rtnType"] == "long" or pm["rtnType"] == "unsigned int" or pm["rtnType"] == "static long" or pm["rtnType"] == "short" or pm["rtnType"] == "PolyKEY" or pm["rtnType"] == "wchar_t":
									outfunc = "lua_pushinteger"
									basicType = True
								if pm["rtnType"] == "bool" or pm["rtnType"] == "static bool" or pm["rtnType"] == "virtual bool":
									outfunc = "lua_pushboolean"
									basicType = True

								if pm["rtnType"].find("*") > -1: # Returned var is definitely a pointer.
									wrappersHeaderOut += "\tPolyBase *ptrRetVal = (PolyBase*)%s%s;\n" % (call, retFunc)
									wrappersHeaderOut += "\tif(ptrRetVal == NULL) {\n"
									wrappersHeaderOut += "\t\tlua_pushnil(L);\n"
									wrappersHeaderOut += "\t} else {\n"
									wrappersHeaderOut += "\t\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
									wrappersHeaderOut += "\t\t*userdataPtr = ptrRetVal;\n"
									wrappersHeaderOut += "\t}\n"
								elif basicType == True: # Returned var has been flagged as a recognized primitive type
									wrappersHeaderOut += "\t%s(L, %s%s);\n" % (outfunc, call, retFunc)
								else: # Some static object is being returned. Convert it to a pointer, then return that.
									className = pm["rtnType"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "")
									if className == "Polygon": # Deal with potential windows.h conflict
										className = "Polycode::Polygon"
									if className == "Rectangle":
										className = "Polycode::Rectangle"
									if className == "Polycode : : Rectangle":
										className = "Polycode::Rectangle"
									wrappersHeaderOut += "\t%s *retInst = new %s();\n" % (className, className)
									wrappersHeaderOut += "\t*retInst = %s;\n" % (call)
									wrappersHeaderOut += "\tPolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));\n"
									wrappersHeaderOut += "\tluaL_getmetatable(L, \"%s.%s\");\n" % (libName, className)
									wrappersHeaderOut += "\tlua_setmetatable(L, -2);\n"
									wrappersHeaderOut += "\t*userdataPtr = (PolyBase*)retInst;\n"
								wrappersHeaderOut += "\treturn 1;\n"
					wrappersHeaderOut += "}\n\n" # Close out C++ generation

					# Now generate the Lua side method.
					if rawMethod:
						luaClassBindingOut += "function %s:%s(...)\n" % (ckey, pm["name"])
						luaClassBindingOut += "\treturn %s.%s_%s(self.__ptr, ...)\n" % (libName, ckey, pm["name"])
						luaClassBindingOut += "end\n"
					elif pm["name"] == ckey: # Constructors
						luaClassBindingOut += "function %s:%s(...)\n" % (ckey, ckey)
						luaClassBindingOut += "\tlocal arg = {...}\n"
						if inherits:
							luaClassBindingOut += "\tif type(arg[1]) == \"table\" and count(arg) == 1 then\n"
							luaClassBindingOut += "\t\tif \"\"..arg[1].__classname == \"%s\" then\n" % (c["inherits"][0]["class"])
							luaClassBindingOut += "\t\t\tself.__ptr = arg[1].__ptr\n"
							luaClassBindingOut += "\t\t\treturn\n"
							luaClassBindingOut += "\t\tend\n"
							luaClassBindingOut += "\tend\n"
						luaClassBindingOut += "\tfor k,v in pairs(arg) do\n"
						luaClassBindingOut += "\t\tif type(v) == \"table\" then\n"
						luaClassBindingOut += "\t\t\tif v.__ptr ~= nil then\n"
						luaClassBindingOut += "\t\t\t\targ[k] = v.__ptr\n"
						luaClassBindingOut += "\t\t\tend\n"
						luaClassBindingOut += "\t\tend\n"
						luaClassBindingOut += "\tend\n"
						luaClassBindingOut += "\tif self.__ptr == nil and arg[1] ~= \"__skip_ptr__\" then\n"
						if ckey == "EventHandler": # See LuaEventHandler above
							luaClassBindingOut += "\t\tself.__ptr = %s.%s(self)\n" % (libName, ckey)
						else:
							luaClassBindingOut += "\t\tself.__ptr = %s.%s(unpack(arg))\n" % (libName, ckey)
						luaClassBindingOut += "\tend\n"
						luaClassBindingOut += "end\n\n"
					else: # Non-constructors.						
						if pm["rtnType"].find("static ") == -1: # Non-static method
							luaClassBindingOut += "function %s:%s(%s)\n" % (ckey, pm["name"], ", ".join(paramlist))						
							if len(lparamlist):
								luaClassBindingOut += "\tlocal retVal = %s.%s_%s(self.__ptr, %s)\n" % (libName, ckey, pm["name"], ", ".join(lparamlist))
							else:
								luaClassBindingOut += "\tlocal retVal =  %s.%s_%s(self.__ptr)\n" % (libName, ckey, pm["name"])
						else: # Static method
							luaClassBindingOut += "function %s.%s(%s)\n" % (ckey, pm["name"], ", ".join(paramlist))
							if len(lparamlist):
								luaClassBindingOut += "\tlocal retVal = %s.%s_%s(%s)\n" % (libName, ckey, pm["name"], ", ".join(lparamlist))
							else:
								luaClassBindingOut += "\tlocal retVal =  %s.%s_%s()\n" % (libName, ckey, pm["name"])

						if not voidRet: # Was there a return value?
							if basicType == True: # Yes, a primitive
								luaClassBindingOut += "\treturn retVal\n"
							else: # Yes, a pointer was returned
								if vectorReturn == True:
									className = vectorReturnClass.replace("*", "")
									luaClassBindingOut += template_returnPtrLookupArray("\t",template_quote(className),"retVal")
								else:
									className = pm["rtnType"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "").replace("*","").replace(" ", "")
									luaClassBindingOut += template_returnPtrLookup("\t",template_quote(className),"retVal")
						luaClassBindingOut += "end\n\n" # Close out Lua generation

					parsed_methods.append(pm["name"]) # Method parse success

				luaDocOut += "\t\t</methods>\n"

				# With methods out of the way, do some final cleanup:
				
				# user pointer metatable creation in C++
				cppLoaderOut += "\n\tluaL_newmetatable(L, \"%s.%s\");\n" % (libName, ckey)
				if ckey not in disable_gc:
					cppLoaderOut += "\tlua_pushstring(L, \"__gc\");\n"
					cppLoaderOut += "\tlua_pushcfunction(L, %s_delete_%s);\n" % (libName, ckey)
					cppLoaderOut += "\tlua_settable(L, -3);\n"
				cppLoaderOut +="\tlua_pop(L, 1);\n"

				# Delete method (C++ side)
				cppRegisterOut += "\t\t{\"delete_%s\", %s_delete_%s},\n" % (ckey, libName, ckey)
				wrappersHeaderOut += "static int %s_delete_%s(lua_State *L) {\n" % (libName, ckey)
				wrappersHeaderOut += "\tluaL_checktype(L, 1, LUA_TUSERDATA);\n"
				wrappersHeaderOut += "\tPolyBase **inst = (PolyBase**)lua_touserdata(L, 1);\n"
				wrappersHeaderOut += "\tdelete ((%s*) *inst);\n" % (ckey)
				wrappersHeaderOut += "\t*inst = NULL;\n"
				wrappersHeaderOut += "\treturn 0;\n"
				wrappersHeaderOut += "}\n\n"

				# Delete method (Lua side)
				luaClassBindingOut += "function %s:__delete()\n" % (ckey)
				luaClassBindingOut += "\tif self then %s.delete_%s(self.__ptr) end\n" % (libName, ckey)
				luaClassBindingOut += "end\n"
					
				# Add class to lua index file
				luaIndexOut += "require \"%s/%s\"\n" % (prefix, ckey)
				# Write lua file
				mkdir_p(apiClassPath)
				if ckey != "EventDispatcher":
					fout = open("%s/%s.lua" % (apiClassPath, ckey), "w")
					fout.write(luaClassBindingOut)

				luaDocOut += "\t</class>\n"
	
		except CppHeaderParser.CppParseError as e: # One input file parse; failed.
			print(e)
			sys.exit(1)

	luaDocOut += "</classes>\n"
	luaDocOut += "</docs>\n"

	# Footer boilerplate for wrappersHeaderOut and cppRegisterOut.
	wrappersHeaderOut += "} // namespace Polycode\n"
	
	cppRegisterOut += "\t\t{NULL, NULL}\n"
	cppRegisterOut += "\t};\n"
	cppRegisterOut += "\tluaL_openlib(L, \"%s\", %sLib, 0);\n" % (libName, libSmallName)
	cppRegisterOut += cppLoaderOut
	cppRegisterOut += "\treturn 1;\n"
	cppRegisterOut += "}"
	
	
	cppRegisterHeaderOut = "" # Def: Global C++ *LUA.h
	cppRegisterHeaderOut += "#pragma once\n"
	cppRegisterHeaderOut += "#include <%s>\n" % (mainInclude)
	cppRegisterHeaderOut += "extern \"C\" {\n"
	cppRegisterHeaderOut += "#include <stdio.h>\n"
	cppRegisterHeaderOut += "#include \"lua.h\"\n"
	cppRegisterHeaderOut += "#include \"lualib.h\"\n"
	cppRegisterHeaderOut += "#include \"lauxlib.h\"\n"
	cppRegisterHeaderOut += "int _PolyExport luaopen_%s(lua_State *L);\n" % (prefix)
	cppRegisterHeaderOut += "}\n"
	
	# Write out global files
	mkdir_p(includePath)
	mkdir_p(apiPath)
	mkdir_p(sourcePath)

	fout = open("%s/%sLUA.h" % (includePath, prefix), "w")
	fout.write(cppRegisterHeaderOut)

	if luaDocPath is None:
		luaDocPath = "../../../Documentation/Lua/xml"
	if luaDocPath != "-":
		fout = open("%s/%s.xml" % (luaDocPath, prefix), "w")
		fout.write(luaDocOut)

	fout = open("%s/%s.lua" % (apiPath, prefix), "w")
	fout.write(luaIndexOut)
	
	fout = open("%s/%sLUAWrappers.h" % (includePath, prefix), "w")
	fout.write(wrappersHeaderOut)
	
	fout = open("%s/%sLUA.cpp" % (sourcePath, prefix), "w")
	fout.write(cppRegisterOut)
	
	# Create .pak zip archive
	pattern = '*.lua'
	os.chdir(apiPath)
	if libName == "Polycore":
		with ZipFile("api.pak", 'w') as myzip:
			for root, dirs, files in os.walk("."):
				for filename in fnmatch.filter(files, pattern):
					myzip.write(os.path.join(root, filename))
	else:
		with ZipFile("%s.pak" % (libName), 'w') as myzip:
			for root, dirs, files in os.walk("."):
				for filename in fnmatch.filter(files, pattern):
					myzip.write(os.path.join(root, filename))

if len(sys.argv) < 10:
	print ("Usage:\n%s [input path] [prefix] [main include] [lib small name] [lib name] [api path] [api class-path] [include path] [source path] [lua doc path (optional) (or - for omit)] [inherit-in-module-file path (optional)]" % (sys.argv[0]))
	sys.exit(1)
else:
	createLUABindings(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8], sys.argv[9], sys.argv[10] if len(sys.argv)>10 else None, sys.argv[11] if len(sys.argv)>11 else None)
