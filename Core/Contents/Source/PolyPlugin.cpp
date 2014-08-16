/*
Copyright (C) 2014 by Joachim Meyer

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

#include "PolyPlugin.h"
#include "PolyObject.h"

using namespace Polycode;

Plugin::Plugin(const String& name) : Resource(Resource::RESOURCE_PLUGIN) {
	this->name = name;
	
}

Plugin::~Plugin() {}

//void Plugin::loadPluginFromFile(const String& fileName) {
//	Object loadFile;
//	if (!loadFile.loadFromBinary(fileName))
//		if (!loadFile.loadFromXML(fileName))
//			return;
//	
//	ObjectEntry plugin = loadFile.root;
//
//}


Plugin* Plugin::loadPluginFromEntry(ObjectEntry* entry){
	
	this->setResourceName((*entry)["name"]->stringVal);
	ObjectEntry* props = (*entry)["props"];
	if (!props)
		return NULL;

	for (int k = 0; k < props->length; k++){
		ObjectEntry* propEntry = props->children[k];
		if (!propEntry)
			continue;
		
		Prop *prop;
		prop->loadPropFromEntry(propEntry);

		this->addProp(prop);
	}
}

//Prop::Prop(int val){
//	this->intVal = val;
//	this->type = PROP_INT;
//}
//
//Prop::Prop(Number val) {
//	this->numberVal = val;
//	this->type = PROP_NUMBER;
//}
//
//Prop::Prop(bool val) {
//	this->boolVal = val;
//	this->type = PROP_BOOL;
//}
//
//Prop::Prop(PolyBase *val) {
//	this->classVal = val;
//	this->type = PROP_CLASS;
//}

Prop::Prop(int type, String name){
	this->type = type;
	this->name = name;
}

Prop::~Prop(){}

Prop* Prop::loadPropFromEntry(ObjectEntry* entry){
	int type = (*entry)["type"]->intVal;
	if (!type)
		return NULL;

	if (!(*entry)["name"])
		return NULL;
	String name = (*entry)["name"]->stringVal;

	Prop(type, name);

	/*switch (type){
	case Prop::PROP_NUMBER:
	prop = new Prop(propEntry->NumberVal);
	break;
	case Prop::PROP_INT:
	prop = new Prop(propEntry->intVal);
	break;
	case Prop::PROP_BOOL:
	prop = new Prop(propEntry->NumberVal);
	break;
	case Prop::PROP_CLASS:
	prop = new Prop(&propEntry->stringVal);
	break;
	default:
	continue;
	}*/

	if (type == 4){
		int i = 0;
		while (i < entry->length){
			children.push_back(loadPropFromEntry((*entry->children[i])["prop"]));
			i++;
		}
		this->length = i;
	}
	return this;
}