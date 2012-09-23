/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
 
#include "PolyObject.h"
#include "tinyxml.h"
#include <sstream>

using namespace Polycode;

void ObjectEntry::Clear() {
	for(int i=0; i < children.size(); i++) {
		children[i]->Clear();
		delete children[i];
	}
	children.clear();
}

String ObjectEntry::getTypedName() const {
	const String _name = name.size() > 0 ? name : String("nil");
	if (type == ObjectEntry::ARRAY_ENTRY)
		return String("polyarray:") + _name;
	if (type == ObjectEntry::STRING_ENTRY && stringVal.size() == 0)
		return String("polystring:") + _name;
	
	// TODO: In interest of consistency, make sure that STRING_ENTRYs stay STRING_ENTRYs (etc) if they're ambiguous (i.e. contain numbers)
	
	return _name;
}	
	
void ObjectEntry::setTypedName(const String &str) {
	size_t firstColon = str.find(":");
	// Note: This will split up a:b:c as having type "a" and name "b:c". Is this appropriate?
	if (firstColon == -1) {
		name = str;
	} else { // There was a namespace
		name = str.substr(firstColon+1);
		
		String sty = str.substr(0,firstColon);
		if (sty == "polyfloat")
			type = ObjectEntry::FLOAT_ENTRY;
		else if (sty == "polyint")
			type = ObjectEntry::INT_ENTRY;
		else if (sty == "polybool")
			type = ObjectEntry::BOOL_ENTRY;
		else if (sty == "polyarray")
			type = ObjectEntry::ARRAY_ENTRY;
		else if (sty == "polystring")
			type = ObjectEntry::STRING_ENTRY;
		else if (sty == "polycontainer")
			type = ObjectEntry::CONTAINER_ENTRY;
			
	}
	if (name == "nil")
		name.contents.clear();
	
}

Object::Object() {
	
}

Object::~Object() {
	
}

void Object::saveToXML(const String& fileName) {
	TiXmlDocument doc;  	
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl ); 
 
	TiXmlElement * rootElement = createElementFromObjectEntry(&root);
	doc.LinkEndChild(rootElement);  	
	
	doc.SaveFile(fileName.c_str()); 
}


TiXmlElement *Object::createElementFromObjectEntry(ObjectEntry *entry) {
	TiXmlElement *newElement = new TiXmlElement(entry->getTypedName().c_str());
	
	switch(entry->type) {
		case ObjectEntry::BOOL_ENTRY: {
			newElement->LinkEndChild(new TiXmlText( entry->boolVal ? "true" : "false" ));
		} break;
		case ObjectEntry::FLOAT_ENTRY: case ObjectEntry::INT_ENTRY: {
			std::ostringstream o;
			if (entry->type == ObjectEntry::FLOAT_ENTRY)
				o << entry->NumberVal;
			else
				o << entry->intVal;
			newElement->LinkEndChild(new TiXmlText( o.str().c_str() ));
		} break;
		case ObjectEntry::STRING_ENTRY: {
			newElement->LinkEndChild(new TiXmlText( entry->stringVal.c_str() ));
		} break;
		default: { // Some sort of container.
			for(int i=0; i < entry->children.size(); i++) {
				ObjectEntry *childEntry = entry->children[i];
				bool needLinkChild = entry->type == ObjectEntry::ARRAY_ENTRY;
				
		//		printf("Parsing %s (type: %d)\n", childEntry->name.c_str(), childEntry->type);
				
				if (!needLinkChild) {
					const String &childTypedName = childEntry->getTypedName();
					switch(childEntry->type) {
						case ObjectEntry::BOOL_ENTRY:
							if(childEntry->boolVal)
								newElement->SetAttribute(childTypedName.c_str(), "true");
							else
								newElement->SetAttribute(childTypedName.c_str(), "false");
						break;
						case ObjectEntry::FLOAT_ENTRY: {
							std::ostringstream o; // Avoid NumberToString, it truncates
							o << childEntry->NumberVal;
							newElement->SetAttribute(childTypedName.c_str(), o.str().c_str());
						} break;
						case ObjectEntry::INT_ENTRY:				
							newElement->SetAttribute(childTypedName.c_str(), childEntry->intVal);												
						break;
						case ObjectEntry::STRING_ENTRY: 
						{
							TiXmlElement *childElement = new TiXmlElement(childTypedName.c_str());  
							childElement->LinkEndChild( new TiXmlText(childEntry->stringVal.c_str()));
							newElement->LinkEndChild(childElement);								
						} break;
						default:
							needLinkChild = true;
						break;
					}
				}
				
				if (needLinkChild) {
					TiXmlElement *childElement = createElementFromObjectEntry(childEntry);
					newElement->LinkEndChild(childElement);
				}
			}
		} break;
	}
	
	return newElement;
}

bool Object::loadFromXMLString(const String &xmlString) {

	if(xmlString.length() < 2) {
		return false;
	}

	TiXmlDocument doc;
	doc.Parse((const char*)xmlString.c_str(), 0, TIXML_ENCODING_UTF8);

	if(doc.Error()) {
		Logger::log("Error loading xml string: %s\n", doc.ErrorDesc());
		return false;
	}
	
	TiXmlElement *rootElement = doc.RootElement();
	createFromXMLElement(rootElement, &root);
	return true;	
}
		
bool Object::loadFromXML(const String& fileName) {

	TiXmlDocument doc(fileName.c_str());
	doc.LoadFile();

	if(doc.Error()) {
		Logger::log("Error loading xml file: %s\n", doc.ErrorDesc());
		return false;
	}
	
	TiXmlElement *rootElement = doc.RootElement();
	createFromXMLElement(rootElement, &root);
	return true;	
}


void Object::createFromXMLElement(TiXmlElement *element, ObjectEntry *entry) {
	entry->type = ObjectEntry::CONTAINER_ENTRY;
	
	int ival;
	double dval;	
	
	// run through the attributes
	TiXmlAttribute* pAttrib=element->FirstAttribute();
	int i=0;
	while (pAttrib)
	{
		ObjectEntry *newEntry = new ObjectEntry();
		newEntry->type = ObjectEntry::STRING_ENTRY;		
		newEntry->stringVal = pAttrib->Value();
		
		if (newEntry->stringVal.find(".") == -1 && pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS) {
			newEntry->intVal = ival;
			newEntry->NumberVal = (Number)ival;
			newEntry->type = ObjectEntry::INT_ENTRY;
		} else if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) {
			newEntry->NumberVal = dval;
			newEntry->intVal = dval;
			newEntry->type = ObjectEntry::FLOAT_ENTRY;
		}
		
		if(newEntry->stringVal == "true") {
			newEntry->boolVal = true;
			newEntry->intVal = 1;
			newEntry->NumberVal = 1;
			newEntry->type = ObjectEntry::BOOL_ENTRY;
		}
		if(newEntry->stringVal == "false") {
			newEntry->boolVal = false;
			newEntry->intVal = 0;
			newEntry->NumberVal = 0;
			newEntry->type = ObjectEntry::BOOL_ENTRY;
		}
	
		newEntry->setTypedName(pAttrib->Name()); // Set name last because we might override type
		
		entry->children.push_back(newEntry);
	
		i++;
		pAttrib=pAttrib->Next();
	}	

	// check if has a value
	if(element->GetText()) {
		entry->stringVal = element->GetText();
		entry->type = ObjectEntry::STRING_ENTRY;
		
		const char *rawVal = entry->stringVal.c_str();
		char *endResult = NULL; const char *success = rawVal + entry->stringVal.size();
		entry->intVal = strtol(rawVal, &endResult, 10);
		if (endResult == success) { // If integer part exhausts string
			entry->type = ObjectEntry::INT_ENTRY;
			entry->NumberVal = entry->intVal;
			entry->boolVal = entry->intVal;
		} else {
			entry->NumberVal = strtod(rawVal, &endResult);
			entry->intVal = entry->NumberVal;
			entry->boolVal = entry->NumberVal;
			if (endResult == success) {
				entry->type = ObjectEntry::FLOAT_ENTRY;
			}
		}
		
		if(entry->stringVal == "true") {
			entry->boolVal = true;
			entry->type = ObjectEntry::BOOL_ENTRY;
		}
		if(entry->stringVal == "false") {
			entry->boolVal = false;
			entry->type = ObjectEntry::BOOL_ENTRY;
		}
	} else {
		// then through the children	
		TiXmlNode* pChild;	

		String lastName = "";
		int count = 0;
		for (pChild = element->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
			TiXmlElement *pChildElement = pChild->ToElement();
			if (!pChildElement) continue; // Skip comment nodes
			
			ObjectEntry *newEntry = new ObjectEntry();
			createFromXMLElement(pChildElement, newEntry);
			entry->children.push_back(newEntry);		
			if(newEntry->name == lastName) { // Keys cannot repeat in a CONTAINER
				entry->type = ObjectEntry::ARRAY_ENTRY;
			}
			lastName = newEntry->name;			
			count++;
		}
		
		entry->length = count;
	}

	entry->setTypedName(element->Value()); // Set name last because we might override type
}
