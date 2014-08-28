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
#include "PolyCoreServices.h"
#include "PolyPluginManager.h"
#include "PolyResourceManager.h"
#include "PolyLogger.h"

using namespace Polycode;

Plugin::Plugin(const String& name) : Resource(Resource::RESOURCE_PLUGIN) {
	Services()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_PLUGIN, name);
}

Plugin::Plugin(ObjectEntry *entry) : Resource(Resource::RESOURCE_PLUGIN) {
	loadPluginFromEntry(entry);
}

Plugin::~Plugin() {}

Plugin* Plugin::loadPluginFromEntry(ObjectEntry* entry){	
	if ((*entry)["name"])
		this->setResourceName((*entry)["name"]->stringVal);
	
	if ((*entry)["fileext"])
		this->ext = (*entry)["fileext"]->stringVal;
	
	if ((*entry)["sheet"] && (*(*entry)["sheet"])["props"])
		this->sheetEntry = (*entry)["sheet"];

	if ((*entry)["type"])
		this->pluginType = (*entry)["type"]->intVal;
	
	ObjectEntry* props = (*entry)["props"];
	if (props) {
		for (int k = 0; k < props->length; k++) {
			ObjectEntry* propEntry = props->children[k];
			if (!propEntry)
				continue;

			Prop *prop = new Prop(propEntry);
			this->addProp(prop);
		}
	}
	Logger::log("Adding plugin: [%s]\n", this->getResourceName().c_str());
	return this;
}

unsigned int Plugin::getNumProps() const {
	return props.size();
}

void Plugin::addProp(Prop *prop) {
	props.push_back(prop);
}

void Plugin::removeProp(Prop *propToRemove) {
	for (int i = 0; i<props.size(); i++) {
		if (props[i] == propToRemove) {
			props.erase(props.begin() + i);
			return;
		}
	}
}

std::vector<Prop*> Plugin::getProps() const {
	return props;
}

Prop::Prop(const String& name, const int type){
	this->type = type;
	this->name = name;
}

Prop::Prop(ObjectEntry *entry) {
	loadPropFromEntry(entry);
}

Prop::~Prop(){}

Prop* Prop::loadPropFromEntry(ObjectEntry* entry){
	int type = (*entry)["type"]->intVal;
	if (!type)
		return NULL;

	if (!(*entry)["name"])
		return NULL;
	String name = (*entry)["name"]->stringVal;

	this->type = type;
	this->name = name;

	if (type == 4){
		int l = 0;
		for (int i = 0; i < entry->children.size(); i++) {
			if (entry->children[i]->name == "prop") {
				children.push_back(new Prop(entry->children[i]));
				l++;
			}
		}
		this->length = l;
	}
	return this;
}