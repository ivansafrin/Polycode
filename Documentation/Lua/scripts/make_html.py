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
	header_f = open("local_header.html", 'r')
	globalHeaderMain = header_f.read()
	globalHeader = globalHeaderMain
	footer_f = open("local_footer.html", 'r')
	globalFooter = footer_f.read()

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
		html += "\t\t\t\t\t\t<h3 class=\"class_methods_title\">Static Functions</h3>\n"
	else:
		html += "\t\t\t\t\t\t<h3 class=\"class_methods_title\">Functions</h3>\n"
	html += "\t\t\t\t\t\t<div class=\"well\">\n"
	for subitem in item.getElementsByTagName('method'):
		if static == True and subitem.hasAttribute("static") == False:
			continue
		if static == False and subitem.hasAttribute("static") == True:
			continue
		paramList = ""
		paramIndex = 0
		if len(subitem.getElementsByTagName('param')) > 0:
			for param in subitem.getElementsByTagName('param'):
				if paramIndex != 0:
					paramList += ", "
				paramList += "<span class=\"inline_param\">%s</span> " % (param.attributes["name"].value)
				paramIndex = paramIndex + 1
		if static == True:
			html += "\t\t\t\t\t\t\t\t<h4 style=\"margin-top: 40px\"><span class=\"badge\">%s</span> %s.%s (%s)</h4>\n" % (subitem.attributes["return_type"].value, className, subitem.attributes["name"].value, paramList)
		else:
			html += "\t\t\t\t\t\t\t\t<h4 style=\"margin-top: 40px\"><span class=\"badge\">%s</span> %s (%s)</h4>\n" % (subitem.attributes["return_type"].value, subitem.attributes["name"].value, paramList)

		desc = subitem.getElementsByTagName('desc')
		descText = "No description."
		if len(desc) > 0:
			descText = desc[0].childNodes[0].data
		html += "\t\t\t\t\t\t\t\t<p>%s</p>\n" % (descText)
		
		if len(subitem.getElementsByTagName('param')) > 0:
			for param in subitem.getElementsByTagName('param'):
				desc = param.getElementsByTagName('desc')
				descText = "No description."
				if len(desc) > 0:
					if len(desc[0].childNodes) > 0:
						descText = desc[0].childNodes[0].data
				html += "\t\t\t\t\t\t\t\t\t<p><span class=\"badge\">%s</span> %s - %s</p>\n" % ( param.attributes["type"].value, param.attributes["name"].value, descText)

	html += "\t\t\t\t\t\t</div>\n"
	html += "\t\t\t\t\t</div>\n"
	return html


def makePage(item, classList, classListPlain, moduleName):
	html = globalHeader
	html += classList

	html += "\t<div class=\"col-md-9\">"

	if item.hasAttribute("extends"):
		extendModulePrefix = moduleName
		if item.attributes["extends"].value not in classListPlain:
			extendModulePrefix = "Polycode"
		html += "\t\t\t\t\t<h1>%s <span class=\"class_extends\"> (extends</span> <span class=\"class_extends_class\"><a href=\"../%s/%s.html\">%s</a>)</span></h1>\n" % (item.attributes["name"].value, extendModulePrefix, item.attributes["extends"].value, item.attributes["extends"].value)
	else:	
		html += "\t\t\t\t\t<h1 class=\"class_name\">%s</h1>\n" % (item.attributes["name"].value)

	desc = item.getElementsByTagName('desc')
	descText = "No description."
	if len(desc) > 0:
		descText = desc[0].childNodes[0].data
	html += "\t\t\t\t\t<p class=\"lead\">%s</p>\n" % descText

	classNotes = item.getElementsByTagName('class_notes')
	for nn in classNotes:
		html += "\t\t\t\t\t<div class=\"class_desc\">%s</div>\n" % nn.childNodes[0].data

	if len(item.getElementsByTagName('static_member')) > 0:
		html += "\t\t\t\t\t<div class=\"class_properties\">\n"
		html += "\t\t\t\t\t\t<h3 style=\"\">Static Properties</h3>\n"
		html += "\t\t\t\t\t\t<div class=\"well\">\n"
		for subitem in item.getElementsByTagName('static_member'):
			html += "\t\t\t\t\t\t\t\t<h5 style=\"margin-top: 25px\">%s.%s = %s</h5>\n" % (item.attributes["name"].value, subitem.attributes["name"].value, subitem.attributes["value"].value)
			desc = subitem.getElementsByTagName('desc')
			descText = "No description."
			if len(desc) > 0:
				descText = desc[0].childNodes[0].data
			html += "\t\t\t\t\t\t\t\t<p><span class=\"badge\">%s</span>  %s</p>\n" % (subitem.attributes["type"].value, descText)
		html += "\t\t\t\t\t\t</div>\n"
		html += "\t\t\t\t\t</div>\n"

	if len(item.getElementsByTagName('member')) > 0:
		html += "\t\t\t\t\t<div class=\"class_properties\">\n"
		html += "\t\t\t\t\t\t<h3>Properties</h3>\n"
		html += "\t\t\t\t\t\t<div class=\"well\">\n"
		for subitem in item.getElementsByTagName('member'):
			html += "\t\t\t\t\t\t\t\t<h5 style=\"margin-top: 25px\">%s</h5>\n" % (subitem.attributes["name"].value)
			desc = subitem.getElementsByTagName('desc')
			descText = "No description."
			if len(desc) > 0:
				descText = desc[0].childNodes[0].data
			html += "\t\t\t\t\t\t\t\t<p><span class=\"badge\">%s</span>  %s</p>\n" % (subitem.attributes["type"].value, descText)
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
	classList += "\t<div class=\"col-md-3\">"
	classList += "\t<ul class=\"list-group\">\n"


	classListPlain = []
	for item in dom.documentElement.getElementsByTagName('class'):
		classList += "<a href=\"%s.html\" class=\"list-group-item\">%s</a>" % (item.attributes["name"].value, item.attributes["name"].value)
		classListPlain.append(item.attributes["name"].value)
	classList += "\t\t\t</ul>\n"
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
indexhtml += "\t<div class=\"col-md-3\">"
indexhtml += "\t<ul class=\"list-group\">\n"

for fname in dirList:
	if len(fname.split(".")) > 1:
		if fname.split(".")[1] == "xml":
			moduleName = fname.split(".")[0]
			makeHTML("../xml/%s" % (fname), moduleName)
			indexhtml += "<a href=\"%s/index.html\" class=\"list-group-item\">%s</a>" % (moduleName, moduleName)

indexhtml += "\t</ul>\n"
indexhtml += "\t</div>\n"

if siteDocs == True:
	f = open("../site_html/index.html", 'w')
else:
	f = open("../html/index.html", 'w')

f.write(indexhtml)
f.close()
indexhtml += globalFooter
