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
#include "polycode/core/PolyConfig.h"
#include "tinyxml.h"

using namespace Polycode;

Config::Config(Core *core) : core(core) {
	
}

Config::~Config() {
	
}

void Config::loadConfig(const String& configNamespace, const String& fileName) {
	TiXmlDocument doc(fileName.c_str());
	
	Logger::log("Loading config: %s\n", fileName.c_str());
	
	if(!doc.LoadFile(core)) {
		Logger::log("Error loading config file...\n");
		Logger::log("Error: %s\n", doc.ErrorDesc());
		return;
	}
	
	TiXmlElement *rootElement = doc.RootElement();
	
	TiXmlNode *pChild;
	ConfigEntry *entry;
	for(pChild = rootElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		TiXmlElement *pChildElement = pChild->ToElement();
		if (!pChildElement) continue; // Skip comment nodes
		
		entry = getEntryOrAdd(configNamespace, pChild->Value());
		entry->stringVal = pChildElement->GetText();		
		entry->numVal = atof(pChildElement->GetText());
		entry->isString = true;
		entry->configNamespace = configNamespace;
	}
	
}

void Config::saveConfig(const String& configNamespace, const String& fileName) const {

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
				node->LinkEndChild( new TiXmlText(entries[i]->stringVal.c_str()));	
			else
				node->LinkEndChild( new TiXmlText(String::NumberToString(entries[i]->numVal).c_str()));							
			root->LinkEndChild( node);		
		}
	}
	doc.SaveFile(core, fileName.c_str());
}

ConfigEntry *Config::getEntry(const String& configNamespace, const String& key) const {
	for(int i=0; i < entries.size(); i++) {
		ConfigEntry *entry = entries[i];
		if(entry->key == key && entry->configNamespace == configNamespace) {
			return entry;
		}
	}
	return NULL;
}

ConfigEntry *Config::getEntryOrAdd(const String& configNamespace, const String& key) {
	ConfigEntry *entry = getEntry(configNamespace, key);
	if(!entry) {
		entry = new ConfigEntry();
		entry->key = key;
		entry->isString = false;
		entry->numVal = 0;
		entry->configNamespace = configNamespace;
		entries.push_back(entry);
	}
	return entry;
}

void Config::setStringValue(const String& configNamespace, const String& key, const String& value) {
	getEntryOrAdd(configNamespace, key)->stringVal = value;
	getEntryOrAdd(configNamespace, key)->isString = true;
}

void Config::setNumericValue(const String& configNamespace, const String& key, Number value) {
	getEntryOrAdd(configNamespace, key)->numVal = value;
	getEntryOrAdd(configNamespace, key)->isString = false;
}

Number Config::getNumericValue(const String& configNamespace, const String& key) const {
	ConfigEntry *ret = getEntry(configNamespace, key);
	if(ret) {
		return ret->numVal;
	} else {
		return 0.0;
	}
}

const String& Config::getStringValue(const String& configNamespace, const String& key) const {
	ConfigEntry *ret = getEntry(configNamespace, key);
	if(ret) {
		return ret->stringVal;
	} else {
		return "undefined";
	}
}

void Config::setBoolValue(const String& configNamespace, const String& key, bool value) {
	getEntryOrAdd(configNamespace, key)->stringVal = (!value ? "false" : "true");
	getEntryOrAdd(configNamespace, key)->isString = true;
}

bool Config::getBoolValue(const String& configNamespace, const String& key) const {
	
	ConfigEntry *ret = getEntry(configNamespace, key);
	if(ret) {
		const String& str = ret->stringVal;
		if (str == "true" || str == "1") {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
