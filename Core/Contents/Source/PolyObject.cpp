
#include "PolyObject.h"


using namespace Polycode;

Object::Object() {
	
}

Object::~Object() {
	
}

void Object::saveToXML(String fileName) {
	TiXmlDocument doc;  	
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl ); 
 
	TiXmlElement * rootElement = createElementFromObjectEntry(&root);
	doc.LinkEndChild(rootElement);  	
	
	doc.SaveFile(fileName.c_str()); 
}


TiXmlElement *Object::createElementFromObjectEntry(ObjectEntry *entry) {
	TiXmlElement *newElement = new TiXmlElement(entry->name.c_str());  
	
	for(int i=0; i < entry->children.size(); i++) {
		ObjectEntry *childEntry = entry->children[i];
		
//		printf("Parsing %s (type: %d)\n", childEntry->name.c_str(), childEntry->type);
		
		switch(childEntry->type) {
			case ObjectEntry::BOOL_ENTRY:
				if(childEntry->boolVal)
					newElement->SetAttribute(childEntry->name.c_str(), "true");
				else
					newElement->SetAttribute(childEntry->name.c_str(), "false");
			break;
			case ObjectEntry::FLOAT_ENTRY:
				newElement->SetAttribute(childEntry->name.c_str(), String::NumberToString(childEntry->NumberVal).c_str());								
			break;
			case ObjectEntry::INT_ENTRY:				
				newElement->SetAttribute(childEntry->name.c_str(), childEntry->intVal);												
			break;
			case ObjectEntry::STRING_ENTRY: 
			{
				TiXmlElement *childElement = new TiXmlElement(childEntry->name.c_str());  
				childElement->LinkEndChild( new TiXmlText(childEntry->stringVal.c_str()));
				newElement->LinkEndChild(childElement);								
			}
				break;				
			default:
			{
				TiXmlElement *childElement = createElementFromObjectEntry(entry->children[i]);
				newElement->LinkEndChild(childElement);				
			}
			break;
		}
	}
	
	return newElement;
}

bool Object::loadFromXML(String fileName) {

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
	entry->name = element->Value();
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
		newEntry->name = pAttrib->Name();
		
		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS) {
			if(newEntry->stringVal.find(".") != -1 && pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) {
				newEntry->NumberVal = dval;
				newEntry->intVal = dval;				
				newEntry->type = ObjectEntry::FLOAT_ENTRY;				
			} else {
				newEntry->intVal = ival;
				newEntry->NumberVal = (Number)ival;				
				newEntry->type = ObjectEntry::INT_ENTRY;
			}
		}

		
		if(newEntry->stringVal == "true") {
			newEntry->boolVal = true;
			newEntry->type = ObjectEntry::BOOL_ENTRY;
		}
		if(newEntry->stringVal == "false") {
			newEntry->boolVal = false;
			newEntry->type = ObjectEntry::BOOL_ENTRY;
		}
		
		entry->children.push_back(newEntry);
	
		i++;
		pAttrib=pAttrib->Next();
	}	

	// check if has a value
	if(element->GetText()) {
		entry->stringVal = element->GetText();
		entry->type = ObjectEntry::STRING_ENTRY;
		
		entry->intVal = atoi(entry->stringVal.c_str());
		entry->NumberVal = atof(entry->stringVal.c_str());
		
		if(entry->stringVal == "true") {
			entry->boolVal = true;
			entry->type = ObjectEntry::BOOL_ENTRY;
		}
		if(entry->stringVal == "false") {
			entry->boolVal = false;
			entry->type = ObjectEntry::BOOL_ENTRY;
		}
		
		return;
	}
		
	// then through the children	
	TiXmlNode* pChild;	

	String lastName = "";
	int count = 0;
	for (pChild = element->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		ObjectEntry *newEntry = new ObjectEntry();		
		createFromXMLElement(pChild->ToElement(), newEntry);
		entry->children.push_back(newEntry);		
		if(entry->name == lastName) {
			entry->type = ObjectEntry::ARRAY_ENTRY;
		}
		lastName = entry->name;			
		count++;
	}
	
	entry->length = count;

}