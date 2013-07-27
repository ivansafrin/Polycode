import os
import sys
from xml.dom.minidom import parse

siteDocs = False

if len(sys.argv) > 1:
	if sys.argv[1] == "site":
		siteDocs = True

globalHeaderMain = ""

if siteDocs == True:
	header_f = open("site_header.html", 'r')
	globalHeaderMain = header_f.read()
	globalHeader = globalHeaderMain
	footer_f = open("site_footer.html", 'r')
	globalFooter = footer_f.read()
	
else:
	globalHeaderMain += "<html>\n"
	globalHeaderMain += "\t<head>\n"
	globalHeaderMain += "\t\t<title>Polycode Documentation</title>\n"
	globalHeaderMain += "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"css/docs.css\" />\n"
	globalHeaderMain += "\t\t<link href='http://fonts.googleapis.com/css?family=Roboto:400,300' rel='stylesheet' type='text/css'>\n"
	globalHeaderMain += "\t\t<script type=\"text/javascript\" src=\"js/docs.js\"></script>"
	globalHeaderMain += "\t</head>\n"
	globalHeaderMain += "\t<body>\n"
	globalHeaderMain += "\t\t<div id=\"global_header\"><a href=\"index.html\"><img border=\"0\" src=\"images/docs_header.png\"/></a></div>\n"
	globalHeaderMain += "\t\t<div id=\"content\">\n"

	globalHeader = ""
	globalFooter = ""

	globalHeader += "<html>\n"
	globalHeader += "\t<head>\n"
	globalHeader += "\t\t<title>Polycode Documentation</title>\n"
	globalHeader += "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"../css/docs.css\" />\n"
	globalHeader += "\t\t<script type=\"text/javascript\" src=\"js/docs.js\"></script>"
	globalHeader += "\t</head>\n"
	globalHeader += "\t<body>\n"
	globalHeader += "\t\t<div id=\"global_header\"><a href=\"../index.html\"><img border=\"0\" src=\"../images/docs_header.png\"/></a></div>\n"
	globalHeader += "\t\t<div id=\"content\">\n"


	globalFooter += "\t\t</div>\n"
	globalFooter += "\t</body>\n"
	globalFooter += "\t</html>\n"

def createMethods(className, item, static):

	numStatic = 0
	numRegular = 0
	for subitem in item.getElementsByTagName('method'):
		if subitem.hasAttribute("static") == True:
			numStatic = numStatic + 1
		else:
			numRegular = numRegular + 1

	if static == True and numStatic == 0:
		return ""
	if static == False and numRegular == 0:
		return ""

	html = ""
	html += "\t\t\t\t\t<div class=\"class_methods\">\n"
	if static == True:
		html += "\t\t\t\t\t\t<div class=\"class_methods_title\">Static Functions</div>\n"
	else:
		html += "\t\t\t\t\t\t<div class=\"class_methods_title\">Functions</div>\n"
	html += "\t\t\t\t\t\t<div class=\"class_methods_list\">\n"
	for subitem in item.getElementsByTagName('method'):
		if static == True and subitem.hasAttribute("static") == False:
			continue
		if static == False and subitem.hasAttribute("static") == True:
			continue
		html += "\t\t\t\t\t\t\t<div class=\"class_method\">\n"
		paramList = ""
		paramIndex = 0
		if len(subitem.getElementsByTagName('param')) > 0:
			for param in subitem.getElementsByTagName('param'):
				if paramIndex != 0:
					paramList += ", "
				paramList += " <span class=\"inline_type\">%s</span> <span class=\"inline_param\">%s</span> " % (param.attributes["type"].value, param.attributes["name"].value)
				paramIndex = paramIndex + 1
		if static == True:
			html += "\t\t\t\t\t\t\t\t<div class=\"class_method_name\">%s.%s (%s) </div>\n" % (className, subitem.attributes["name"].value, paramList)
		else:
			html += "\t\t\t\t\t\t\t\t<div class=\"class_method_name\">%s (%s) </div>\n" % (subitem.attributes["name"].value, paramList)

		html += "\t\t\t\t\t\t\t\t<div class=\"class_method_type\">%s</div>\n" % (subitem.attributes["return_type"].value)
		desc = subitem.getElementsByTagName('desc')
		descText = "No description."
		if len(desc) > 0:
			descText = desc[0].childNodes[0].data
		html += "\t\t\t\t\t\t\t\t<div class=\"class_method_desc\">%s</div>\n" % (descText)
		
		if len(subitem.getElementsByTagName('param')) > 0:
			html += "\t\t\t\t\t\t\t\t<div class=\"class_method_params\">\n"
			html += "\t\t\t\t\t\t\t\t<div class=\"class_method_params_title\">Parameters</div>\n"
			for param in subitem.getElementsByTagName('param'):
				html += "\t\t\t\t\t\t\t\t<div class=\"class_method_param\">\n"
				html += "\t\t\t\t\t\t\t\t\t<div class=\"class_method_param_name\">%s</div>\n" % (param.attributes["name"].value)
				html += "\t\t\t\t\t\t\t\t\t<div class=\"class_method_param_type\">%s</div>\n" % (param.attributes["type"].value)
				desc = param.getElementsByTagName('desc')
				descText = "No description."
				if len(desc) > 0:
					if len(desc[0].childNodes) > 0:
						descText = desc[0].childNodes[0].data
				html += "\t\t\t\t\t\t\t\t\t<div class=\"class_method_param_desc\">%s</div>\n" % (descText)
				html += "\t\t\t\t\t\t\t\t</div>\n"

			html += "\t\t\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t\t\t</div>\n"

	html += "\t\t\t\t\t\t</div>\n"
	html += "\t\t\t\t\t</div>\n"
	return html


def makePage(item, classList, classListPlain, moduleName):
	html = globalHeader
	html += classList

	html += "\t\t\t\t<div class=\"class_main\">\n"
	
	if item.hasAttribute("extends"):
		extendModulePrefix = moduleName
		if item.attributes["extends"].value not in classListPlain:
			extendModulePrefix = "Polycode"
		html += "\t\t\t\t\t<div class=\"class_name\">%s <span class=\"class_extends\">extends</span> <span class=\"class_extends_class\"><a href=\"../%s/%s.html\">%s</a></span></div>\n" % (item.attributes["name"].value, extendModulePrefix, item.attributes["extends"].value, item.attributes["extends"].value)
	else:	
		html += "\t\t\t\t\t<div class=\"class_name\">%s</div>\n" % (item.attributes["name"].value)

	desc = item.getElementsByTagName('desc')
	descText = "No description."
	if len(desc) > 0:
		descText = desc[0].childNodes[0].data
	html += "\t\t\t\t\t<div class=\"class_desc\">%s</div>\n" % descText

	classNotes = item.getElementsByTagName('class_notes')
	for nn in classNotes:
		html += "\t\t\t\t\t<div class=\"class_desc\">%s</div>\n" % nn.childNodes[0].data

	if len(item.getElementsByTagName('static_member')) > 0:
		html += "\t\t\t\t\t<div class=\"class_properties\">\n"
		html += "\t\t\t\t\t\t<div class=\"class_properties_title\">Static Properties</div>\n"
		html += "\t\t\t\t\t\t<div class=\"class_properties_list\">\n"
		for subitem in item.getElementsByTagName('static_member'):
			html += "\t\t\t\t\t\t\t<div class=\"class_property\">\n"
			html += "\t\t\t\t\t\t\t\t<div class=\"class_property_name\">%s.%s <span class=\"static_value\">= %s</span></div>\n" % (item.attributes["name"].value, subitem.attributes["name"].value, subitem.attributes["value"].value)
			html += "\t\t\t\t\t\t\t\t<div class=\"class_property_type\">%s</div>\n" % (subitem.attributes["type"].value)
			desc = subitem.getElementsByTagName('desc')
			descText = "No description."
			if len(desc) > 0:
				descText = desc[0].childNodes[0].data
			html += "\t\t\t\t\t\t\t\t<div class=\"class_property_desc\">%s</div>\n" % (descText)
			html += "\t\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t</div>\n"

	if len(item.getElementsByTagName('member')) > 0:
		html += "\t\t\t\t\t<div class=\"class_properties\">\n"
		html += "\t\t\t\t\t\t<div class=\"class_properties_title\">Properties</div>\n"
		html += "\t\t\t\t\t\t<div class=\"class_properties_list\">\n"
		for subitem in item.getElementsByTagName('member'):
			html += "\t\t\t\t\t\t\t<div class=\"class_property\">\n"
			html += "\t\t\t\t\t\t\t\t<div class=\"class_property_name\">%s</div>\n" % (subitem.attributes["name"].value)
			html += "\t\t\t\t\t\t\t\t<div class=\"class_property_type\">%s</div>\n" % (subitem.attributes["type"].value)
			desc = subitem.getElementsByTagName('desc')
			descText = "No description."
			if len(desc) > 0:
				descText = desc[0].childNodes[0].data
			html += "\t\t\t\t\t\t\t\t<div class=\"class_property_desc\">%s</div>\n" % (descText)
			html += "\t\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t</div>\n"

	html += createMethods(item.attributes["name"].value, item, True)
	html += createMethods(item.attributes["name"].value, item, False)


	html += "\t\t\t\t</div>\n"
	return html

def makeHTML(fileName, moduleName):
	print ("Parsing %s\n" % fileName)

	sourceXML = open(fileName)
	dom = parse(sourceXML)
	sourceXML.close()

	classList = ""
	classList += "\t\t\t<div id=\"class_list\">\n"
	classListPlain = []
	for item in dom.documentElement.getElementsByTagName('class'):
		classList += "\t\t\t\t<div class=\"class_entry\"><a href=\"%s.html\">%s</a></div>\n" % (item.attributes["name"].value, item.attributes["name"].value)
		classListPlain.append(item.attributes["name"].value)
	classList += "\t\t\t</div>\n"
	classList += "\n"

	if siteDocs == True:
		directory = "../site_html/%s" % (moduleName)
	else:
		directory = "../html/%s" % (moduleName)
	if not os.path.exists(directory):
		os.makedirs(directory)	

	html = globalHeader
	html += classList
	html += globalFooter
	if siteDocs == True:
		f = open("../site_html/%s/index.html" % (moduleName), 'w')
	else:
		f = open("../html/%s/index.html" % (moduleName), 'w')
	f.write(html)
	f.close()

	for item in dom.documentElement.getElementsByTagName('class'):
		if siteDocs == True:
			f = open("../site_html/%s/%s.html" % (moduleName, item.attributes["name"].value), 'w')
		else:
			f = open("../html/%s/%s.html" % (moduleName, item.attributes["name"].value), 'w')
		html = makePage(item, classList, classListPlain, moduleName)
		f.write(html)
		f.close()

dirList = os.listdir("../xml")

indexhtml = globalHeaderMain
indexhtml += "\t<div id=\"module_links\">\n"

for fname in dirList:
	if len(fname.split(".")) > 1:
		if fname.split(".")[1] == "xml":
			moduleName = fname.split(".")[0]
			makeHTML("../xml/%s" % (fname), moduleName)
			indexhtml += "\t\t\t<div class=\"module_link\"><a href=\"%s/index.html\">%s</a></div>\n" % (moduleName, moduleName)

indexhtml += "\t</div>\n"

if siteDocs == True:
	f = open("../site_html/index.html", 'w')
else:
	f = open("../html/index.html", 'w')

f.write(indexhtml)
f.close()
indexhtml += globalFooter
