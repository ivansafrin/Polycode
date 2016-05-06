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
		self.cppRegisterOut += "int jsopen_%s(duk_context *ctx) {\n" % (self.libName)
		self.cppRegisterOut += "\tconst duk_function_list_entry %s_funcs[] = {\n" % (self.libName)
		mkdir_p("%s/%s" % (self.config.get('js', 'JSApiDirectory'), self.libName))

	def processTargetFile(self, targetFile):
		print("dummy")

	def processClass(self, c):
		self.jsClassOut += "function %s() {\n" % c["name"]
		self.jsClassOut += "}\n"

		self.makeJSMethods(c)
		self.writeClass(c)
		self.jsIndexOut += "require('%s/%s')\n" % (self.libName, c["name"])

	def makeJSMethods(self, c):
		for method in c["methods"]:
			if method["isStatic"] == False and method["name"] != c["name"]:
				self.jsClassOut += "\n%s.prototype.%s = function(" % (c["name"], method["name"])
				params = ",".join(str(p["name"]) for p in method["parameters"])
				self.jsClassOut += params
				self.jsClassOut += ") {\n"
				if len(params) > 0:
					self.jsClassOut += "\t%s.%s_%s(this.__ptr, %s)\n" % (self.libName, c["name"], method["name"], params)
				else:
					self.jsClassOut += "\t%s.%s_%s(this.__ptr)\n" % (self.libName, c["name"], method["name"])
				self.cppRegisterOut += "\t\t\t{\"%s_%s\", %s_%s_%s, %d},\n" % (c["name"], method["name"], self.libName, c["name"], method["name"], len(method["parameters"]))
				self.wrappersHeaderBody += "\tduk_ret_t %s_%s_%s(duk_context *context) {\n" % (self.libName, c["name"], method["name"])
				self.wrappersHeaderBody += "\t\t%s *inst = (%s*)duk_to_pointer(context, -1);\n" % (c["name"], c["name"])

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

				self.wrappersHeaderBody += "\t\tinst->%s(%s);\n" % (method["name"], params)
				self.wrappersHeaderBody += "\t\treturn 0;\n"
				self.wrappersHeaderBody += "\t}\n\n"
				self.jsClassOut += "}\n"

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
	
		#pattern = '*.js'
		#os.chdir(self.config.get('js', 'JSApiDirectory'))
		#with ZipFile("js_%s.pak" % (self.libName), 'w') as myzip:
		#	for root, dirs, files in os.walk("."):
		#		for filename in fnmatch.filter(files, pattern):
		#			myzip.write(os.path.join(root, filename))

	def writeClass(self, c):
		fout = open("%s/%s/%s.js" % (self.config.get('js', 'JSApiDirectory'), self.libName, c["name"]), "w")
		fout.write(self.jsClassOut)
		self.jsClassOut = ""

