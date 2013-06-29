/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "PolycodeProject.h"

PolycodeProject::PolycodeProject(String name, String path, String file) {

	printf("CREATING PROJECT %s %s\n", name.c_str(), path.c_str());

	projectName = name;
	projectFolder = path;
	projectFile = file;

	loadProjectFromFile();

}

bool PolycodeProject::loadProjectFromFile() {

	if(!configFile.loadFromXML(projectFile)) {
		return false;
	}

	if(!configFile.root.readString("entryPoint", &(data.entryPoint))) {
		data.entryPoint = "Source/Main.lua";
		configFile.root.addChild("entryPoint", "Source/Main.lua");
	}

	if(!configFile.root.readInt("defaultWidth", &(data.defaultWidth))) {
		data.defaultWidth = 640;
		configFile.root.addChild("defaultWidth", 640);
	}

	if(!configFile.root.readInt("defaultHeight", &(data.defaultHeight))) {
		data.defaultHeight = 480;
		configFile.root.addChild("defaultHeight", 480);
	}

	if(!configFile.root.readString("textureFiltering", &(data.filteringMode))) {
		data.filteringMode = "linear";
		configFile.root.addChild("textureFiltering", String("linear"));	
	}


	if(!configFile.root.readBool("vSync", &(data.vSync))) {
		data.vSync = false;
		configFile.root.addChild("vSync", false);
	}


	if(!configFile.root.readInt("antiAliasingLevel", &(data.aaLevel))) {
		data.aaLevel = 0;
		configFile.root.addChild("antiAliasingLevel", 0);
	}


	if(!configFile.root.readInt("anisotropyLevel", &(data.anisotropy))) {
		data.anisotropy = 0;
		configFile.root.addChild("anisotropyLevel", 0);
	}

	if(!configFile.root.readInt("frameRate", &(data.frameRate))) {
		data.frameRate = 60;
		configFile.root.addChild("frameRate", 60);
	}

	data.modules.clear();
	if(configFile.root["modules"]) {
		for(int i=0; i < configFile.root["modules"]->length; i++) {
			ObjectEntry *module = (*configFile.root["modules"])[i];

			if(module->type != ObjectEntry::STRING_ENTRY) 
				continue;

			data.modules.push_back(module->stringVal);
			CoreServices::getInstance()->getResourceManager()->addArchive("Standalone/Modules/"+module->stringVal+"/API");

		}
	}

	data.fonts.clear();
	if(configFile.root["fonts"]) {
		for(int i=0; i < configFile.root["fonts"]->length; i++) {
			ObjectEntry *font = (*configFile.root["fonts"])[i];

			String fontName, fontPath;
			if(font->readString("name", &fontName) && font->readString("path", &fontPath)) {
				ProjectFontData fontData = ProjectFontData(fontName, fontPath);
				data.fonts.push_back(fontData);
			}
		}
	}

	if(configFile.root["backgroundColor"]) {
		ObjectEntry *color = configFile.root["backgroundColor"];

		bool haveAllColors = 1;
		haveAllColors &= color->readNumber("red", &(data.backgroundColorR));
		haveAllColors &= color->readNumber("green", &(data.backgroundColorG));
		haveAllColors &= color->readNumber("blue", &(data.backgroundColorB));

		if(!haveAllColors) {
			data.backgroundColorR = 0.0;
			data.backgroundColorG = 0.0;
			data.backgroundColorB = 0.0;

			if(!color) color = configFile.root.addChild("backgroundColor");
			color->addChild("red", 0.0);
			color->addChild("green", 0.0);
			color->addChild("blue", 0.0);
		}
	}

	return true;
}

bool PolycodeProject::saveFile() {


	configFile.root["frameRate"]->intVal = data.frameRate;
	configFile.root["defaultWidth"]->intVal = data.defaultWidth;
	configFile.root["defaultHeight"]->intVal = data.defaultHeight;
	configFile.root["entryPoint"]->stringVal = data.entryPoint;
	configFile.root["entryPoint"]->type = ObjectEntry::STRING_ENTRY;

	configFile.root["textureFiltering"]->type = ObjectEntry::STRING_ENTRY;
	configFile.root["textureFiltering"]->stringVal = data.filteringMode;

	ObjectEntry *color = configFile.root["backgroundColor"];

	(*color)["red"]->NumberVal = data.backgroundColorR;
	(*color)["red"]->type = ObjectEntry::FLOAT_ENTRY;

	(*color)["green"]->NumberVal = data.backgroundColorG;
	(*color)["green"]->type = ObjectEntry::FLOAT_ENTRY;

	(*color)["blue"]->NumberVal = data.backgroundColorB;
	(*color)["blue"]->type = ObjectEntry::FLOAT_ENTRY;

	if(configFile.root["modules"]) {
		configFile.root["modules"]->Clear();
	}

	/*
	for(int j=0; j < data.modules.size(); j++) {
		if(!configFile.root["modules"]) {
			configFile.root.addChild("modules");
		}
		configFile.root["modules"]->type = ObjectEntry::ARRAY_ENTRY;
		configFile.root["modules"]->addChild("module", data.modules[j]);

		CoreServices::getInstance()->getResourceManager()->addArchive("Standalone/Modules/"+data.modules[j]+"/API");

	}
	*/

	if(configFile.root["fonts"]) {
		configFile.root["fonts"]->Clear();
	}

	for(int j=0; j < data.fonts.size(); j++) {
		if(!configFile.root["fonts"]) {
			configFile.root.addChild("fonts");
		}
		configFile.root["fonts"]->type = ObjectEntry::ARRAY_ENTRY;

		ObjectEntry *objectEntry = configFile.root["fonts"]->addChild("font");
		objectEntry->addChild("name", data.fonts[j].fontName);
		objectEntry->addChild("path", data.fonts[j].fontPath);

	}

	if(configFile.root["packedItems"]) {
		configFile.root["packedItems"]->Clear();
	}

	vector<OSFileEntry> files = OSBasics::parseFolder(projectFolder, false);

	for(int i=0; i < files.size(); i++) {
		OSFileEntry entry = files[i];

		if(!configFile.root["packedItems"]) {
				configFile.root.addChild("packedItems");
		}

		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			ObjectEntry *objectEntry = configFile.root["packedItems"]->addChild("item");
			objectEntry->addChild("type", "folder");
			objectEntry->addChild("path", entry.name);
		} else if(entry.fullPath != projectFile) {
			ObjectEntry *objectEntry = configFile.root["packedItems"]->addChild("item");
			objectEntry->addChild("type", "file");
			objectEntry->addChild("path", entry.name);

		}
	}


	unsigned int afMap[6] = {0,1,2,4,8,16};
	unsigned int aaMap[4] = {0,2,4,6};

	configFile.root["antiAliasingLevel"]->intVal = data.aaLevel;
	configFile.root["anisotropyLevel"]->intVal = data.anisotropy;
	configFile.root["vSync"]->boolVal = data.vSync;

	configFile.saveToXML(projectFile);

	return true;
}

PolycodeProject::~PolycodeProject() {

}
