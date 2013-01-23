import os
from xml.dom.minidom import parse

globalHeaderMain = ""

globalHeaderMain += "<html>\n"
globalHeaderMain += "\t<head>\n"
globalHeaderMain += "\t\t<title>Polycode Documentation</title>\n"
globalHeaderMain += "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"css/docs.css\" />\n"
globalHeaderMain += "\t\t<script type=\"text/javascript\" src=\"js/docs.js\"></script>"
globalHeaderMain += "\t</head>\n"
globalHeaderMain += "\t<body>\n"
globalHeaderMain += "\t\t<div id=\"global_header\"></div>\n"
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
globalHeader += "\t\t<div id=\"global_header\"></div>\n"
globalHeader += "\t\t<div id=\"content\">\n"


globalFooter += "\t\t</div>\n"
globalFooter += "\t</body>\n"
globalFooter += "\t</html>\n"

def makePage(item, classList):
	html = globalHeader
	html += classList

	html += "\t\t\t\t<div class=\"class_main\">\n"
	
	html += "\t\t\t\t\t<div class=\"class_name\">%s</div>\n" % (item.attributes["name"].value)
	desc = item.getElementsByTagName('desc')
	descText = "No description."
	if len(desc) > 0:
		descText = desc[0].childNodes[0].data
	html += "\t\t\t\t\t<div class=\"class_desc\">%s</div>\n" % descText

	html += "\t\t\t\t\t<div class=\"class_properies\">\n"
	html += "\t\t\t\t\t\t<div class=\"class_properies_title\">Properties</div>\n"
	html += "\t\t\t\t\t\t<div class=\"class_properies_list\">\n"
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

	html += "\t\t\t\t\t<div class=\"class_methods\">\n"
	html += "\t\t\t\t\t\t<div class=\"class_methods_title\">Functions</div>\n"
	html += "\t\t\t\t\t\t<div class=\"class_methods_list\">\n"
	for subitem in item.getElementsByTagName('method'):
		html += "\t\t\t\t\t\t\t<div class=\"class_method\">\n"
		paramList = ""
		paramIndex = 0
		if len(subitem.getElementsByTagName('param')) > 0:
			for param in subitem.getElementsByTagName('param'):
				if paramIndex != 0:
					paramList += ", "
				paramList += " <span class=\"inline_type\">%s</span> <span class=\"inline_param\">%s</span> " % (param.attributes["type"].value, param.attributes["name"].value)
				paramIndex = paramIndex + 1
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
				desc = subitem.getElementsByTagName('desc')
				descText = "No description."
				if len(desc) > 0:
					descText = desc[0].childNodes[0].data
				html += "\t\t\t\t\t\t\t\t\t<div class=\"class_method_param_desc\">%s</div>\n" % (descText)
				html += "\t\t\t\t\t\t\t\t</div>\n"

			html += "\t\t\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t\t\t</div>\n"

	html += "\t\t\t\t\t\t</div>\n"
	html += "\t\t\t\t\t</div>\n"

	html += "\t\t\t\t</div>\n"
	return html

def makeHTML(fileName, moduleName):
	print ("Parsing %s\n" % fileName)

	sourceXML = open(fileName)
	dom = parse(sourceXML)
	sourceXML.close()

	classList = ""
	classList += "\t\t\t<div id=\"class_list\">\n"
	for item in dom.documentElement.getElementsByTagName('class'):
		classList += "\t\t\t\t<div class=\"class_entry\"><a href=\"%s.html\">%s</a></div>\n" % (item.attributes["name"].value, item.attributes["name"].value)
	classList += "\t\t\t</div>\n"
	classList += "\n"

	directory = "../html/%s" % (moduleName)
	if not os.path.exists(directory):
		os.makedirs(directory)	

	html = globalHeader
	html += classList
	html += globalFooter
	f = open("../html/%s/index.html" % (moduleName), 'w')
	f.write(html)
	f.close()

	for item in dom.documentElement.getElementsByTagName('class'):
		f = open("../html/%s/%s.html" % (moduleName, item.attributes["name"].value), 'w')
		html = makePage(item, classList)
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

f = open("../html/index.html", 'w')
f.write(indexhtml)
f.close()
indexhtml += globalFooter
