import CppHeaderParser
import ConfigParser
import io
import os
import re
from LuaBindingsGenerator import *

class BindingsGenerator(object):

	def __init__(self, engines, configFile):
		self.config = ConfigParser.RawConfigParser(allow_no_value=True)
		self.config.read(configFile)
		self.targetDir = self.config.get('global', 'TargetDirectory')
		self.ignoreFiles = self.config.get('global', 'IgnoreFiles')

		self.symbolsToStrip = self.config.get('global', 'StripSymbols').replace(" ", "").split(",")
		self.ignoreClasses = self.config.get('global', 'IgnoreClasses').replace(" ", "").split(",")
		self.ignoreMethods = self.config.get('global', 'IgnoreMethods').replace(" ", "").split(",")

		self.engines = {LuaBindingsGenerator(self.config)}

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
		ty = ty.replace("unsigned", "int")
		ty = ty.replace("long", "int")
		ty = ty.replace("float", "Number")
		ty = ty.replace("double", "Number")
		ty = ty.replace(" ", "") # Not very safe!
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
			if pp["type"].find("POLYIGNORE") != -1:
				continue
			if pp["type"].find("static ") != -1:
				if "defaltValue" in pp: #this is misspelled in parser library
					classPP["defaultValue"] = pp["defaltValue"]
				if 'doxygen' in pp:
					classPP["doc"] = self.cleanDocs(pp['doxygen'])
				properties.append(classPP)
			else:
				if pp["type"].find("vector") == -1 and pp["name"] != "setScale" and pp["name"] != "setPosition" and pp["name"] != "BUFFER_CACHE_PRECISION" and not pp["name"].isdigit():
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
			method["type"] = self.typeFilter(pm["rtnType"])
			if pm["name"] in parsedMethods or pm["name"].find("operator") > -1 or pm["rtnType"].find("POLYIGNORE") > -1 or pm["name"] in self.ignoreMethods :
				continue
			#ignore destructors
			if pm["name"] == "~"+c["name"]:
				continue
			method["parameters"] = []
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
				if "defaltValue" in param:
					mParam["defaultValue"] = param["defaltValue"]
				method["parameters"].append(mParam)
			parsedMethods.append(pm["name"])
			methods.append(method)
		return methods

	# ----------------------------------------------------
	# Parse and clean data from a class
	# ----------------------------------------------------
	def parseClassData(self, c, ckey):
		classData = {}
		classData["name"] = ckey
		if len(c["inherits"]) > 0:
			classData["parent"] = c["inherits"][0]["class"]
		if 'doxygen' in c:
			classData["doc"] = self.cleanDocs(c['doxygen'])
		classData["properties"] = self.parseClassProperties(c)
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
					print("\033[93mParsing class \033[0m[\033[92m%s\033[0m]" % ckey)
					c = cppHeader.classes[ckey]
					classData = self.parseClassData(c, ckey)
					self.processClass(classData)
				
			except CppHeaderParser.CppParseError as e:
				self.error(e)
				return

		self.finalize()
