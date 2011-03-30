import sys
import CppHeaderParser
import os

out = ""
sout = ""

lfout = ""

sout += "#include \"PolycodeLUA.h\"\n"
sout += "#include \"PolycodeLUAWrappers.h\"\n\n"

sout += "int luaopen_Polycode(lua_State *L) {\n"
sout += "\tstatic const struct luaL_reg polycodeLib [] = {"

out += "#pragma once\n\n"
out += "#include <Polycode.h>\n\n"
out += "#include <PolyGLRenderer.h>\n\n"

out += "extern \"C\" {\n\n"
out += "#include <stdio.h>\n"
out += "#include \"lua.h\"\n"
out += "#include \"lualib.h\"\n"
out += "#include \"lauxlib.h\"\n\n"


files = os.listdir("../../../Core/Contents/Include")
for fileName in files:
	ignore = ["PolyCocoaCore", "PolyAGLCore", "PolyGLES1Renderer", "PolyGLRenderer", "tinyxml", "tinystr", "PolyiPhoneCore", "PolyGLES1Texture", "PolyGLTexture", "PolyGLVertexBuffer", "PolyRenderer", "PolyThreaded", "PolyTexture", "PolyShader", "PolyScene"]
	if fileName.split(".")[1] == "h" and fileName.split(".")[0] not in ignore:
		headerFile = "../../../Core/Contents/Include/%s" % fileName
		print "Parsing %s" % fileName
		try:
			f = open(headerFile)
			contents = f.read().replace("_PolyExport", "")
			cppHeader = CppHeaderParser.CppHeader(contents, "string")
			ignore_classes = ["ParticleEmitter", "PolycodeShaderModule", "Core", "Object", "Shader", "Texture", "Scene", "Threaded", "Renderer", "ShaderBinding"]
			for ckey in cppHeader.classes:
				c = cppHeader.classes[ckey]
				lout = ""
				inherits = False
				if len(c["inherits"]) > 0:
					if c["inherits"][0]["class"] not in ignore_classes:
						lout += "require \"Polycode/%s\"\n\n" % (c["inherits"][0]["class"])
						lout += "class \"%s\" (%s)\n\n" % (ckey, c["inherits"][0]["class"])
						inherits = True
				if inherits == False:
					lout += "class \"%s\"\n\n" % ckey
		
				if len(c["methods"]["public"]) < 2 or ckey in ignore_classes:
					continue

				if ckey == "OSFileEntry":
					print c["methods"]["public"]
				parsed_methods = []
				ignore_methods = ["readByte32", "readByte16", "getCustomEntitiesByType"]
				for pm in c["methods"]["public"]:
					if pm["name"] in parsed_methods or pm["name"].find("operator") > -1 or pm["name"] in ignore_methods:
						continue 

					if pm["name"] == "~"+ckey:
						out += ""
					else:
						if pm["name"] == ckey:
							sout += "\t\t{\"%s\", Polycore_%s},\n" % (ckey, ckey)
							out += "static int Polycore_%s(lua_State *L) {\n" % (ckey)
							idx = 1
						else: 
							sout += "\t\t{\"%s_%s\", Polycore_%s_%s},\n" % (ckey, pm["name"], ckey, pm["name"])
							out += "static int Polycore_%s_%s(lua_State *L) {\n" % (ckey, pm["name"])
							out += "\tluaL_checktype(L, 1, LUA_TLIGHTUSERDATA);\n"
							out += "\t%s *inst = (%s*)lua_topointer(L, 1);\n" % (ckey.replace("Polygon", "Polycode::Polygon"), ckey.replace("Polygon", "Polycode::Polygon"))
							idx = 2
						paramlist = []
						lparamlist = []
						for param in pm["parameters"]:
							if not param.has_key("type"):
								continue
							if param["type"] == "0":
								continue

							param["name"] = param["name"].replace("end", "_end").replace("repeat", "_repeat")
							if"type" in param:
								luatype = "LUA_TLIGHTUSERDATA"
								if param["type"].find("*") > -1:
									luafunc = "(%s)lua_topointer" % (param["type"].replace("Polygon", "Polycode::Polygon"))
								elif param["type"].find("&") > -1:
									luafunc = "*(%s*)lua_topointer" % (param["type"].replace("const", "").replace("&", "").replace("Polygon", "Polycode::Polygon"))
								else:
									luafunc = "*(%s*)lua_topointer" % (param["type"])
								lend = ".__ptr"
								if param["type"] == "int" or param["type"] == "unsigned int":
									luafunc = "lua_tointeger"
									luatype = "LUA_TNUMBER"
									lend = ""
								if param["type"] == "bool":
									luafunc = "lua_toboolean"
									luatype = "LUA_TBOOLEAN"
									lend = ""
								if param["type"] == "Number":
									luatype = "LUA_TNUMBER"
									luafunc = "lua_tonumber"
									lend = ""
								if param["type"] == "String":
									luatype = "LUA_TSTRING"
									luafunc = "lua_tostring"
									lend = ""
								
								param["type"] = param["type"].replace("Polygon", "Polycode::Polygon")

								out += "\tluaL_checktype(L, %d, %s);\n" % (idx, luatype);
								out += "\t%s %s = %s(L, %d);\n" % (param["type"], param["name"], luafunc, idx)
								paramlist.append(param["name"])
							
								lparamlist.append(param["name"]+lend)
								idx = idx +1
					
						if pm["name"] == ckey:
							out += "\t%s *inst = new %s(%s);\n" % (ckey.replace("Polygon", "Polycode::Polygon"), ckey.replace("Polygon", "Polycode::Polygon"), ", ".join(paramlist))
							out += "\tlua_pushlightuserdata(L, (void*)inst);\n"
							out += "\treturn 1;\n"
						else:
							call = "inst->%s(%s)" % (pm["name"], ", ".join(paramlist))
							if pm["rtnType"] == "void" or pm["rtnType"] == "static void" or pm["rtnType"] == "virtual void" or pm["rtnType"] == "inline void":
								out += "\t%s;\n" % (call)
								out += "\treturn 0;\n"
							else:
								outfunc = "lua_pushlightuserdata"
								basicType = False
								retFunc = ""
								if pm["rtnType"] == "Number" or  pm["rtnType"] == "inline Number":
									outfunc = "lua_pushnumber"
									basicType = True
								if pm["rtnType"] == "String" or pm["rtnType"] == "static String":
									outfunc = "lua_pushstring"
									basicType = True
									retFunc = ".c_str()"
								if pm["rtnType"] == "int" or pm["rtnType"] == "static int" or  pm["rtnType"] == "size_t" or pm["rtnType"] == "static size_t" or pm["rtnType"] == "long" or pm["rtnType"] == "unsigned int" or pm["rtnType"] == "static long":
									outfunc = "lua_pushinteger"
									basicType = True
								if pm["rtnType"] == "bool" or pm["rtnType"] == "static bool" or pm["rtnType"] == "virtual bool":
									outfunc = "lua_pushboolean"
									basicType = True

								if pm["rtnType"].find("*") > -1:
									out += "\t%s(L, (void*)%s%s);\n" % (outfunc, call, retFunc)
								elif basicType == True:
									out += "\t%s(L, %s%s);\n" % (outfunc, call, retFunc)
								else:
									className = pm["rtnType"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "")
									if className == "Polygon":
										className = "Polycode::Polygon"
									out += "\t%s *retInst = new %s();\n" % (className, className)
									out += "\t*retInst = %s;\n" % (call)
									out += "\t%s(L, retInst);\n" % (outfunc)
								out += "\treturn 1;\n"
						out += "}\n\n"
							
						if pm["name"] == ckey:
							lout += "function %s:%s(%s)\n" % (ckey, ckey, ", ".join(paramlist))
							lout += "\tif self.__ptr == nil then\n"
							lout += "\t\tself.__ptr = Polycore.%s(%s)\n" % (ckey, ", ".join(paramlist))
							lout += "\tend\n"
							lout += "end\n\n"
						else:
							lout += "function %s:%s(%s)\n" % (ckey, pm["name"], ", ".join(paramlist))
							if len(lparamlist):
								lout += "\treturn Polycore.%s_%s(self.__ptr, %s)\n" % (ckey, pm["name"], ", ".join(lparamlist))
							else:
								lout += "\treturn Polycore.%s_%s(self.__ptr)\n" % (ckey, pm["name"])
							lout += "end\n\n"

					parsed_methods.append(pm["name"])
				lfout += "require \"Polycode/%s\"\n" % ckey
				fout = open("../../Contents/LUA/API/Polycode/%s.lua" % ckey, "w")
				fout.write(lout)
		except CppHeaderParser.CppParseError,  e:
			print e
			sys.exit(1)
		
out += "}"

sout += "\t\t{NULL, NULL}\n"
sout += "\t};\n"
sout += "\tluaL_openlib(L, \"Polycore\", polycodeLib, 0);\n"
sout += "\treturn 1;\n"
sout += "}"


fout = open("../../Contents/LUA/API/Polycode.lua", "w")
fout.write(lfout)

fout = open("../../Contents/LUA/Include/PolycodeLUAWrappers.h", "w")
fout.write(out)

fout = open("../../Contents/LUA/Source/PolycodeLUA.cpp", "w")
fout.write(sout)

#print cppHeader

