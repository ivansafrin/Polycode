/*
 *  PolyConfig.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 4/15/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyConfig.h"

using namespace Polycode;

Config::Config() {
	
}

Config::~Config() {
	
}

void Config::loadConfig(String configNamespace, String fileName) {
	TiXmlDocument doc(fileName.c_str());
	
	Logger::log("Loading config: %s\n", fileName.c_str());
	
	if(!doc.LoadFile()) {
		Logger::log("Error loading config file...\n");
		Logger::log("Error: %s\n", doc.ErrorDesc());
		return;
	}
	
	TiXmlElement *rootElement = doc.RootElement();
	
	TiXmlNode *pChild;
	ConfigEntry *entry;
	for(pChild = rootElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		entry = getEntry(configNamespace, pChild->Value());
		entry->stringVal = pChild->ToElement()->GetText();		
		entry->numVal = atof(pChild->ToElement()->GetText());
		entry->isString = true;
		entry->configNamespace = configNamespace;
	}
	
}

void Config::saveConfig(String configNamespace, String fileName) {

	TiXmlDocument doc;  
	TiXmlElement* node;  
	
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  

	TiXmlElement * root = new TiXmlElement( "PolyConfig" );  
	doc.LinkEndChild( root );  
		
	
	for(int i=0; i < entries.size(); i++) {
		if(entries[i]->configNamespace == configNamespace) {
			node = new TiXmlElement(entries[i]->key.c_str());  
			if(entries[i]->isString)
				node->LinkEndChild( new	TiXmlText(entries[i]->stringVal.c_str()));  
			else
				node->LinkEndChild( new	TiXmlText(String::NumberToString(entries[i]->numVal).c_str()));  						
			root->LinkEndChild( node);		
		}
	}
	doc.SaveFile(fileName.c_str());  	
}

ConfigEntry *Config::getEntry(String configNamespace, String key) {
	
	for(int i=0; i < entries.size(); i++) {
		ConfigEntry *entry = entries[i];
		if(entry->key == key && entry->configNamespace == configNamespace) {
			return entry;
		}
	}
	ConfigEntry *newEntry = new ConfigEntry();
	newEntry->key = key;
	newEntry->isString = false;
	newEntry->numVal = 0;
	newEntry->configNamespace = configNamespace;
	entries.push_back(newEntry);
	return newEntry;
}

void Config::setStringValue(String configNamespace, String key, String value) {
	getEntry(configNamespace, key)->stringVal = value;
	getEntry(configNamespace, key)->isString = true;	
}

void Config::setNumericValue(String configNamespace, String key, Number value) {
	getEntry(configNamespace, key)->numVal = value;	
	getEntry(configNamespace, key)->isString = false;		
}


Number Config::getNumericValue(String configNamespace, String key) {
	return getEntry(configNamespace, key)->numVal;
}

String Config::getStringValue(String configNamespace, String key) {
	return getEntry(configNamespace, key)->stringVal;	
}


