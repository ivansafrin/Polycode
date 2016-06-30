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

class JSBindingsGenerator(object):
	
	def __init__(self, config):
		self.config = config
		self.libName = self.config.get('global', 'LibraryName')
		self.jsClassOut = ""
		self.jsIndexOut = ""
		self.wrappersHeaderList = ""
		self.wrappersHeaderBody = ""
		self.cppRegisterOut = ""
		self.inheritInModule = self.config.get('global', 'InheritInModule').replace(" ", "").split(",")
		self.disableGC = self.config.get('global', 'DisableGarbageCollection').replace(" ", "").split(",")
		self.cppRegisterOut += "int jsopen_%s(duk_context *ctx) {\n" % (self.libName)
		self.cppRegisterOut += "\tconst duk_function_list_entry %s_funcs[] = {\n" % (self.libName)
		mkdir_p("%s/%s" % (self.config.get('js', 'JSApiDirectory'), self.libName))
		self.ignoreMethods = self.config.get('global', 'IgnoreMethods').replace(" ", "").split(",")

	def processTargetFile(self, targetFile):
		self.wrappersHeaderList += "#include \"%s/%s\"\n" % (self.config.get('global', 'HeaderIncludeDirectory'), targetFile)

	def processClass(self, c):

		inherits = False
		parentClass = ""
		if "parent" in c:
			if c["parent"] in self.inheritInModule: # Parent class is in this module
				self.jsClassOut += "require('%s/%s')\n\n" % (self.config.get('global', 'LibraryName'), c["parent"])
			else: 
				self.jsClassOut += "require('%s/%s')\n\n" % (self.config.get('global', 'DefaultModule'), c["parent"])

			parentClass = c["parent"]
			inherits = True

		constructor = None
		for method in c["methods"]:
			if method["name"] == c["name"]:
				constructor = method

		params = ""
		paramList  = []
		if constructor:
			params = ",".join(str(p["name"]) for p in constructor["parameters"])
			paramList = constructor["parameters"]

		self.jsClassOut += "function %s(%s) {\n" % (c["name"], params)
		if c["name"] not in self.ignoreMethods:
			self.jsClassOut += "\tif(arguments[0] != \"__skip_ptr__\") {\n"
			self.jsClassOut += "\t\tthis.__ptr = %s.%s(%s)\n" % (self.libName, c["name"], params)
			self.jsClassOut += "\t}\n"
			self.cppRegisterOut += "\t\t\t{\"%s\", %s_%s, %d},\n" % (c["name"], self.libName, c["name"], len(paramList))

			self.wrappersHeaderBody += "\tduk_ret_t %s_%s(duk_context *context) {\n" % (self.libName, c["name"])

			idx = 0
			for p in paramList:
				if "*" in p["type"]:
					outfunc = "(%s)duk_to_pointer" % (p["type"])
					outtype = "%s" % p["type"]
				else:
					outfunc = "*(%s*)duk_to_pointer" % (p["type"])
					outtype = "%s" % p["type"]
				if p["type"] == "int":
					outfunc = "duk_to_int"
					outtype = "int"
				if p["type"] == "PolyKEY":
					outfunc = "(PolyKEY)duk_to_int"
					outtype = "PolyKEY"
				if p["type"] == "Number":
					outfunc = "duk_to_number"
					outtype = "Number"
				if p["type"] == "bool":
					outfunc = "duk_to_boolean"
					outtype = "bool"
				if p["type"] == "String":
					outfunc = "duk_to_string"
					outtype = "String"
				self.wrappersHeaderBody += "\t\t%s %s = %s(context, %d);\n" % (outtype, p["name"], outfunc, idx)
				idx += 1

			self.wrappersHeaderBody += "\t\t%s *inst = new %s(%s);\n" % (c["name"], c["name"], params)
					
			self.wrappersHeaderBody += "\t\tduk_push_pointer(context, (void*)inst);\n"
			self.wrappersHeaderBody += "\t\treturn 1;\n"
			self.wrappersHeaderBody += "\t}\n\n"


		self.makeJSProperties(c)
		self.jsClassOut += "}\n\n"

		self.makeJSStaticProps(c)
		self.jsClassOut += "\n"

		if inherits:
			self.jsClassOut += "%s.prototype = Object.create(%s.prototype)\n\n" % (c["name"], parentClass)

		self.makeJSPropAccessors(c)

		if c["name"] not in self.disableGC:
			self.jsClassOut += "Duktape.fin(%s.prototype, function (x) {\n" % (c["name"])
			self.jsClassOut += "\tif (x === %s.prototype) {\n" % (c["name"])
			self.jsClassOut += "\t\treturn;\n"
			self.jsClassOut += "\t}\n"
			self.jsClassOut += "\t%s.%s__delete(x.__ptr)\n" % (self.libName, c["name"])
			self.jsClassOut += "})\n"

		self.cppRegisterOut += "\t\t\t{\"%s__delete\", %s_%s__delete, 1},\n" % (c["name"], self.libName, c["name"])

		self.wrappersHeaderBody += "\tduk_ret_t %s_%s__delete(duk_context *context) {\n" % (self.libName, c["name"])
		self.wrappersHeaderBody += "\t\t%s *inst = (%s*)duk_to_pointer(context, 0);\n" % (c["name"], c["name"])
		self.wrappersHeaderBody += "\t\tdelete inst;\n"
		self.wrappersHeaderBody += "\t\treturn 0;\n"
		self.wrappersHeaderBody += "\t}\n\n"

		self.makeJSMethods(c)
		self.writeClass(c)
		self.jsIndexOut += "require('%s/%s')\n" % (self.libName, c["name"])

	def makeJSStaticProps(self, c):
		if len(c["staticProperties"]) > 0:
			for pp in c["staticProperties"]:
				if "defaultValue" in pp:
					self.jsClassOut += "%s.%s = %s\n" % (c["name"], pp["name"], pp["defaultValue"])

	def makeJSPropAccessors(self, c):
		if len(c["properties"]) > 0:
			for pp in c["properties"]:
				self.jsClassOut += "%s.prototype.__get_%s = function() {\n" % (c["name"], pp["name"])

				self.cppRegisterOut += "\t\t\t{\"%s__get_%s\", %s_%s__get_%s, 1},\n" % (c["name"], pp["name"], self.libName, c["name"], pp["name"])

				self.wrappersHeaderBody += "\tduk_ret_t %s_%s__get_%s(duk_context *context) {\n" % (self.libName, c["name"], pp["name"])
				self.wrappersHeaderBody += "\t\t%s *inst = (%s*)duk_to_pointer(context, 0);\n" % (c["name"], c["name"])

				outfunc = "this_shouldnt_happen"
				retFunc = ""
				if pp["type"] == "Number":
					outfunc = "duk_push_number"
				if pp["type"] == "String":
					outfunc = "duk_push_string"
					retFunc = ".c_str()"
				if pp["type"] == "int" or pp["type"] == "PolyKEY":
					outfunc = "duk_push_int"
				if pp["type"] == "bool":
					outfunc = "duk_push_boolean"

				if pp["type"].find("*") > -1: # Returned var is definitely a pointer.
					self.wrappersHeaderBody += "\t\tPolyBase *ptrRetVal = (PolyBase*)inst->%s%s;\n" % (pp["name"], retFunc)
					self.wrappersHeaderBody += "\t\tduk_push_pointer(context, (void*)ptrRetVal);\n"
					self.jsClassOut += "\tvar retVal = new %s()\n\tretVal.__ptr = " % (pp["cleanType"])
					self.jsClassOut += "\t%s.%s__get_%s(this.__ptr)\n" % (self.libName, c["name"], pp["name"]) 
					self.jsClassOut += "\treturn retVal\n"
					self.jsClassOut += "}\n\n"
				elif self.isBasicType(pp["type"])  == True:
					self.wrappersHeaderBody += "\t\t%s(context, inst->%s%s);\n" % (outfunc, pp["name"], retFunc);
					self.jsClassOut += "\treturn %s.%s__get_%s(this.__ptr)\n" % (self.libName, c["name"], pp["name"])
					self.jsClassOut += "}\n\n"
				else: 
					className = pp["type"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "")
					if className == "Polygon": # Deal with potential windows.h conflict
						className = "Polycode::Polygon"
					if className == "Rectangle":
						className = "Polycode::Rectangle"
					if className == "Polycode : : Rectangle":
						className = "Polycode::Rectangle"
					self.wrappersHeaderBody += "\t\t%s *retInst = new %s();\n" % (className, className)
					self.wrappersHeaderBody += "\t\t*retInst = inst->%s%s;\n" % (pp["name"], retFunc)
					self.wrappersHeaderBody += "\t\tduk_push_pointer(context, (void*)retInst);\n"
					self.jsClassOut += "\tvar retVal = new %s()\n\tretVal.__ptr = " % (pp["cleanType"])
					self.jsClassOut += "\t%s.%s__get_%s(this.__ptr)\n" % (self.libName, c["name"], pp["name"]) 
					self.jsClassOut += "\treturn retVal\n"
					self.jsClassOut += "}\n\n"

				self.wrappersHeaderBody += "\t\treturn 1;\n"
				self.wrappersHeaderBody += "\t}\n\n"


				self.jsClassOut += "%s.prototype.__set_%s = function(val) {\n" % (c["name"], pp["name"])
				
				if self.isBasicType(pp["type"]):
					self.jsClassOut += "\t%s.%s__set_%s(this.__ptr, val)\n" % (self.libName, c["name"], pp["name"])
				else:
					self.jsClassOut += "\t%s.%s__set_%s(this.__ptr, val.__ptr)\n" % (self.libName, c["name"], pp["name"])
				self.jsClassOut += "}\n\n"
				
				self.cppRegisterOut += "\t\t\t{\"%s__set_%s\", %s_%s__set_%s, 2},\n" % (c["name"], pp["name"], self.libName, c["name"], pp["name"])

				self.wrappersHeaderBody += "\tduk_ret_t %s_%s__set_%s(duk_context *context) {\n" % (self.libName, c["name"], pp["name"])
				self.wrappersHeaderBody += "\t\t%s *inst = (%s*)duk_to_pointer(context, 0);\n" % (c["name"], c["name"])

	
				outfunc = "this_shouldnt_happen"

				if "*" in pp["type"]:
					outfunc = "(%s)duk_to_pointer" % (pp["type"])
				else:
					outfunc = "*(%s*)duk_to_pointer" % (pp["type"])
				if pp["type"] == "int":
					outfunc = "duk_to_int"
				if pp["type"] == "PolyKEY":
					outfunc = "(PolyKEY)duk_to_int"
				if pp["type"] == "Number":
					outfunc = "duk_to_number"
				if pp["type"] == "bool":
					outfunc = "duk_to_boolean"
				if pp["type"] == "String":
					outfunc = "duk_to_string"
				self.wrappersHeaderBody += "\t\tinst->%s = %s(context, 1);\n" % (pp["name"], outfunc)
				self.wrappersHeaderBody += "\t\treturn 0;\n"
				self.wrappersHeaderBody += "\t}\n\n"

	def makeJSProperties(self, c):
		if len(c["properties"]) > 0:
			self.jsClassOut += "\tObject.defineProperties(this, {\n"
			idx = 0
			for pp in c["properties"]:
				self.jsClassOut += "\t\t'%s': { enumerable: true, configurable: true, get: %s.prototype.__get_%s, set: %s.prototype.__set_%s}" % (pp["name"], c["name"], pp["name"], c["name"], pp["name"])
				if idx < len(c["properties"])-1:
					self.jsClassOut += ","
				self.jsClassOut += "\n"

				idx += 1
			self.jsClassOut += "\t})\n"

	def makeJSMethods(self, c):
		for method in c["methods"]:
			if method["name"] != c["name"]:
				self.jsClassOut += "\n%s.prototype.%s = function(" % (c["name"], method["name"])
				params = ",".join(str(p["name"]) for p in method["parameters"])
				self.jsClassOut += params
				self.jsClassOut += ") {\n"
				self.cppRegisterOut += "\t\t\t{\"%s_%s\", %s_%s_%s, %d},\n" % (c["name"], method["name"], self.libName, c["name"], method["name"], len(method["parameters"]) + 1)
				self.wrappersHeaderBody += "\tduk_ret_t %s_%s_%s(duk_context *context) {\n" % (self.libName, c["name"], method["name"])

				if not method["isStatic"]:
					self.wrappersHeaderBody += "\t\t%s *inst = (%s*)duk_to_pointer(context, 0);\n" % (c["name"], c["name"])

				idx = 1
				if method["isStatic"]:
					idx = 0
				for p in method["parameters"]:
					if "*" in p["type"]:
						outfunc = "(%s)duk_to_pointer" % (p["type"])
						outtype = "%s" % p["type"]
					else:
						outfunc = "*(%s*)duk_to_pointer" % (p["type"])
						outtype = "%s" % p["type"]
					if p["type"] == "int":
						outfunc = "duk_to_int"
						outtype = "int"
					if p["type"] == "PolyKEY":
						outfunc = "(PolyKEY)duk_to_int"
						outtype = "PolyKEY"
					if p["type"] == "Number":
						outfunc = "duk_to_number"
						outtype = "Number"
					if p["type"] == "bool":
						outfunc = "duk_to_boolean"
						outtype = "bool"
					if p["type"] == "String":
						outfunc = "duk_to_string"
						outtype = "String"
					self.wrappersHeaderBody += "\t\t%s %s = %s(context, %d);\n" % (outtype, p["name"], outfunc, idx)
					idx += 1

				jsRet = ""
				finalOut = ""
				if self.isVectorType(method["type"]):
					self.wrappersHeaderBody += "\t\treturn 0;\n"
				elif method["type"] == "void" or method["type"] == "static void" or method["type"] == "virtual void" or method["type"] == "inline void" or method["type"] == "void*":
					if method["isStatic"]:
						self.wrappersHeaderBody += "\t\t%s::%s(%s);\n" % (c["name"], method["name"], params)
					else:
						self.wrappersHeaderBody += "\t\tinst->%s(%s);\n" % (method["name"], params)
					self.wrappersHeaderBody += "\t\treturn 0;\n"
				else:
					outfunc = "this_shouldnt_happen"
					retFunc = ""
					if method["type"] == "Number" or  method["type"] == "inline Number":
						outfunc = "duk_push_number"
					if method["type"] == "String" or method["type"] == "static String": # TODO: Path for STL strings?
						outfunc = "duk_push_string"
						retFunc = ".c_str()"
					if method["type"] == "int" or method["type"] == "unsigned int" or method["type"] == "static int" or  method["type"] == "size_t" or method["type"] == "static size_t" or method["type"] == "long" or method["type"] == "unsigned int" or method["type"] == "static long" or method["type"] == "short" or method["type"] == "PolyKEY" or method["type"] == "wchar_t":
						outfunc = "duk_push_int"
					if method["type"] == "bool" or method["type"] == "static bool" or method["type"] == "virtual bool":
						outfunc = "duk_push_boolean"
					
					if method["type"].find("*") > -1: # Returned var is definitely a pointer.
						if method["isStatic"]:
							self.wrappersHeaderBody += "\t\tPolyBase *ptrRetVal = (PolyBase*)%s::%s(%s)%s;\n" % (c["name"], method["name"], params, retFunc)
						else:
							self.wrappersHeaderBody += "\t\tPolyBase *ptrRetVal = (PolyBase*)inst->%s(%s)%s;\n" % (method["name"], params, retFunc)
						self.wrappersHeaderBody += "\t\tduk_push_pointer(context, (void*)ptrRetVal);\n"
						jsRet = "var retVal = new %s()\n\tretVal.__ptr = " % (method["cleanType"])
						finalOut = "\treturn retVal\n"
					elif self.isBasicType(method["type"])  == True:
						if method["isStatic"]:
							self.wrappersHeaderBody += "\t\t%s(context, %s::%s(%s)%s);\n" % (outfunc, c["name"], method["name"], params, retFunc);
						else:
							self.wrappersHeaderBody += "\t\t%s(context, inst->%s(%s)%s);\n" % (outfunc, method["name"], params, retFunc);
						jsRet = "return "
					else: 
						className = method["type"].replace("const", "").replace("&", "").replace("inline", "").replace("virtual", "").replace("static", "")
						if className == "Polygon": # Deal with potential windows.h conflict
							className = "Polycode::Polygon"
						if className == "Rectangle":
							className = "Polycode::Rectangle"
						if className == "Polycode : : Rectangle":
							className = "Polycode::Rectangle"
						self.wrappersHeaderBody += "\t\t%s *retInst = new %s();\n" % (className, className)
						if method["isStatic"]:
							self.wrappersHeaderBody += "\t\t*retInst = %s::%s(%s)%s;\n" % (c["name"], method["name"], params, retFunc)
						else:
							self.wrappersHeaderBody += "\t\t*retInst = inst->%s(%s)%s;\n" % (method["name"], params, retFunc)
						self.wrappersHeaderBody += "\t\tduk_push_pointer(context, (void*)retInst);\n"
						jsRet = "var retVal = new %s()\n\tretVal.__ptr = " % (method["cleanType"])
						finalOut = "\treturn retVal\n"
					self.wrappersHeaderBody += "\t\treturn 1;\n"

				self.wrappersHeaderBody += "\t}\n\n"

				if len(params) > 0:
					jsParams = ""
					jidx = 0
					for jp in method["parameters"]:
						if jp["type"].find("*") > -1:
							jsParams += "%s.__ptr" % jp["name"]
						else:
							jsParams += jp["name"]
						jidx += 1
						if jidx < len(method["parameters"]):
							jsParams += ", "
					if method["isStatic"]:
						self.jsClassOut += "\t%s%s.%s_%s(%s)\n" % (jsRet, self.libName, c["name"], method["name"], jsParams)
					else:
						self.jsClassOut += "\t%s%s.%s_%s(this.__ptr, %s)\n" % (jsRet, self.libName, c["name"], method["name"], jsParams)
				else:
					if method["isStatic"]:
						self.jsClassOut += "\t%s%s.%s_%s()\n" % (jsRet, self.libName, c["name"], method["name"])
					else:
						self.jsClassOut += "\t%s%s.%s_%s(this.__ptr)\n" % (jsRet, self.libName, c["name"], method["name"])
				self.jsClassOut += finalOut
				self.jsClassOut += "}\n"
	
	def isBasicType(self, t):
		basicTypes = ["int", "Number", "String", "PolyKEY", "bool"]
		if t in basicTypes:
			return True
		else:
			return False
	
	def isVectorType(self, t):
		if t.find("<") > -1 and t.find("vector") > -1:
			return True
		else:
			return False

	def finalize(self):
		fout = open("%s/%s.js" % (self.config.get('js', 'JSApiDirectory'), self.libName), "w")
		fout.write(self.jsIndexOut)
		self.jsClassOut = ""
	
		with open(self.config.get('js', 'WrapperHeaderTemplate'), 'r') as f:
			out = f.read().replace("%HEADERS%", self.wrappersHeaderList)
			out = out.replace("%BODY%", self.wrappersHeaderBody)
			fout = open(self.config.get('js', 'WrapperHeaderTarget'), "w")
			fout.write(out)
			fout.close()

		with open(self.config.get('js', 'WrapperMainHeaderTemplate'), 'r') as f:
			out = f.read().replace("%BODY%", "int _PolyExport jsopen_%s(duk_context *ctx);" % self.libName)
			fout = open(self.config.get('js', 'WrapperMainHeaderTarget'), "w")
			fout.write(out)
			fout.close()

		self.cppRegisterOut += "\t\t\t{NULL, NULL, 0}\n"
		self.cppRegisterOut += "\t};\n"
		self.cppRegisterOut += "\tduk_push_global_object(ctx);\n"
		self.cppRegisterOut += "\tduk_push_object(ctx);\n"
		self.cppRegisterOut += "\tduk_put_function_list(ctx, -1, %s_funcs);\n" % (self.libName)
		self.cppRegisterOut += "\tduk_put_prop_string(ctx, -2, \"%s\");\n" % (self.libName)
		self.cppRegisterOut += "\tduk_pop(ctx);\n"
		self.cppRegisterOut += "\treturn 1;\n"
		self.cppRegisterOut += "}\n"

		with open(self.config.get('js', 'WrapperSourceTemplate'), 'r') as f:
			out = f.read().replace("%BODY%", self.cppRegisterOut)
			fout = open(self.config.get('js', 'WrapperSourceTarget'), "w")
			fout.write(out)
			fout.close()
	
		curDir = os.path.dirname(os.path.realpath(__file__))
		pattern = '*.js'
		os.chdir(self.config.get('js', 'JSApiDirectory'))
		with ZipFile("js_%s.pak" % (self.libName), 'w') as myzip:
			for root, dirs, files in os.walk("."):
				for filename in fnmatch.filter(files, pattern):
					myzip.write(os.path.join(root, filename))
		os.chdir(curDir)

	def writeClass(self, c):
		fout = open("%s/%s/%s.js" % (self.config.get('js', 'JSApiDirectory'), self.libName, c["name"]), "w")
		fout.write(self.jsClassOut)
		self.jsClassOut = ""

