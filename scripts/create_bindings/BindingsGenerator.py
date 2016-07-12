import CppHeaderParser
import ConfigParser
import io
import os
import re
from LuaBindingsGenerator import *
from JSBindingsGenerator import *

class BindingsGenerator(object):

	def __init__(self, configFile):
		self.config = ConfigParser.RawConfigParser(allow_no_value=True)
		self.config.read(configFile)
		self.targetDir = self.config.get('global', 'TargetDirectory')
		self.ignoreFiles = self.config.get('global', 'IgnoreFiles')

		self.symbolsToStrip = self.config.get('global', 'StripSymbols').replace(" ", "").split(",")
		self.ignoreClasses = self.config.get('global', 'IgnoreClasses').replace(" ", "").split(",")
		self.ignoreMethods = self.config.get('global', 'IgnoreMethods').replace(" ", "").split(",")

		self.engines = {LuaBindingsGenerator(self.config), JSBindingsGenerator(self.config)}

	# ----------------------------------------------------
	# Utility methods
	# ----------------------------------------------------

	def error(self, msg):
		print("\033[91mERROR: %s" % (msg))
		print("\033[0m")

	# ----------------------------------------------------
	# Interface methods called in bindings engines
	# ----------------------------------------------------

	def processTargetFile(self, targetFile):
		for e in self.engines:
			e.processTargetFile(targetFile)

	def processClass(self, c):
		for e in self.engines:
			e.processClass(c)

	def finalize(self):
		for e in self.engines:
			e.finalize()

	# ----------------------------------------------------
	# Clean up doxygen stuff out of comment docs
	# ----------------------------------------------------

	def cleanDocs(self, docs):
		return docs.replace("/*", "").replace("*/", "").replace("*", "").replace("\n", "").replace("\r", "").replace("::", ".").replace("\t", "")
	
	# ----------------------------------------------------
	# Clean and reduce types to standard identifiers
	# ----------------------------------------------------
	def typeFilter(self, ty):
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
		ty = ty.replace("unsigned int", "int")
		ty = ty.replace("unsigned short", "int")
		ty = ty.replace("unsigned long", "int")
		ty = ty.replace("long", "int")
		ty = ty.replace("float", "Number")
		ty = ty.replace("double", "Number")
		ty = ty.replace(" ", "") # Not very safe!
		return ty

	# ----------------------------------------------------
	# Clean and reduce types to standard identifiers
	# ----------------------------------------------------
	def cleanTypeFilter(self, ty):
		ty = ty.replace("shared_ptr", "")
		ty = ty.replace("<", "")
		ty = ty.replace(">", "")
		ty = ty.replace("*", "")
		return ty

	# ----------------------------------------------------
	# Parse and clean properties from a class
	# ----------------------------------------------------
	def parseClassProperties(self, c):
		properties = []
		for pp in c["properties"]["public"]:
			classPP = {}
			classPP["name"] = pp["name"]
			pp["type"] = pp["type"].replace("Polycode::", "")
			pp["type"] = pp["type"].replace("std::", "")
			classPP["type"] = self.typeFilter(pp["type"])
			classPP["cleanType"] = self.cleanTypeFilter(classPP["type"])
			if pp["type"].find("POLYIGNORE") != -1:
				continue
			if pp["name"] == "" or pp["array"] == 1:
				continue
			if "::union" in pp["name"]:
				continue
			if "void" in pp["type"]:
				continue
			if "<" in pp["type"]:
				continue
			if pp["type"].replace("*", "") in self.ignoreClasses:
				continue

			if pp["type"].find("static ") != -1:
				classPP["isStatic"] = True
				if "defaltValue" in pp: #this is misspelled in parser library
					classPP["defaultValue"] = pp["defaltValue"]
				if 'doxygen' in pp:
					classPP["doc"] = self.cleanDocs(pp['doxygen'])
				if classPP["type"].find("*") == -1:
					properties.append(classPP)
			else:
				classPP["isStatic"] = False
				if pp["type"].find("vector") == -1 and pp["name"] != "setScale" and pp["name"] != "setPosition" and pp["name"] != "BUFFER_CACHE_PRECISION" and not pp["name"].isdigit():
					if classPP["type"].find("*") == -1: #do not add raw pointer accessors
						properties.append(classPP)
		return properties

	# ----------------------------------------------------
	# Parse and clean methods
	# ----------------------------------------------------
	def parseClassMethods(self, c):
		methods = []
		parsedMethods = []
		for pm in c["methods"]["public"]:
			method = {}
			method["name"] = pm["name"]

			if pm["rtnType"].find("static ") == -1:
				method["isStatic"] = False
			else:
				method["isStatic"] = True

			method["type"] = self.typeFilter(pm["rtnType"])
			method["cleanType"] = self.cleanTypeFilter(method["type"])
			if pm["name"] in parsedMethods or pm["name"].find("operator") > -1 or pm["rtnType"].find("POLYIGNORE") > -1 or pm["name"] in self.ignoreMethods :
				continue
			#ignore destructors
			if pm["name"] == "~"+c["name"]:
				continue
			method["parameters"] = []
			hasPointerParam = False
			for param in pm["parameters"]:
				mParam = {}
				if not "name" in param:
					continue
				if not "type" in param:
					continue
				if param["type"] == "0":
					continue
				mParam["name"] = param["name"]
				mParam["type"] = self.typeFilter(param["type"])
				mParam["cleanType"] = self.cleanTypeFilter(mParam["type"])
				if "defaltValue" in param:
					mParam["defaultValue"] = param["defaltValue"]
				method["parameters"].append(mParam)
				if mParam["type"].find("*") > -1:
					hasPointerParam = True
			if method["type"].find("*") == -1 and hasPointerParam == False: #do not add raw pointer return methods or methods that take raw pointers
				methods.append(method)
			parsedMethods.append(pm["name"])
		return methods

	# ----------------------------------------------------
	# Parse and clean data from a class
	# ----------------------------------------------------
	def parseClassData(self, c, ckey):
		classData = {}
		classData["name"] = ckey
		if len(c["inherits"]) > 0:
			if c["inherits"][0]["class"] not in self.ignoreClasses:
				classData["parent"] = c["inherits"][0]["class"]
		if 'doxygen' in c:
			classData["doc"] = self.cleanDocs(c['doxygen'])
		properties = self.parseClassProperties(c)
		classData["properties"] = []
		classData["staticProperties"] = []
		for p in properties:
			if p["isStatic"] == True:
				classData["staticProperties"].append(p)
			else:
				classData["properties"].append(p)
		classData["methods"] = self.parseClassMethods(c)
		return classData

	# ----------------------------------------------------
	# Parse files and create bindings
	# ----------------------------------------------------
	def createBindings(self):
		print("\nPolycode bindings generator v0.1\n")
		print("\033[93mGenerating bindings...")
		print("\033[93mParsing files from \033[92m[%s]" % (self.targetDir))
		
		if not os.path.isdir(self.targetDir):
			self.error("Target directory not valid!")
			return
		
		files = os.listdir(self.targetDir)
		filteredFiles = []
		for fileName in files:
			fileName = "%s/%s" % (self.targetDir, fileName)
			if os.path.isdir(fileName):
				continue
			head, tail = os.path.split(fileName)
			ignore = self.ignoreFiles.replace(" ", "").split(",")
			if tail.split(".")[1] == "h" and tail.split(".")[0] not in ignore:
				filteredFiles.append(fileName)
				self.processTargetFile(tail)

		for fileName in filteredFiles:
			try:
				f = open(fileName)
				contents = f.read()
				for s in self.symbolsToStrip:
					contents = contents.replace(s, "")

				cppHeader = CppHeaderParser.CppHeader(contents, "string")
				for ckey in cppHeader.classes: 
					if ckey in self.ignoreClasses:
						continue
					if "::union" in ckey:
						continue
					print("\033[93mParsing class \033[0m[\033[92m%s\033[0m]" % ckey)
					c = cppHeader.classes[ckey]
					classData = self.parseClassData(c, ckey)
					self.processClass(classData)
				
			except CppHeaderParser.CppParseError as e:
				self.error(e)
				return

		self.finalize()
