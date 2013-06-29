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

#pragma once

#include "Polycode.h"
#include "OSBasics.h"

using namespace Polycode;

class ProjectFontData {
	public:
		ProjectFontData();
		ProjectFontData(String fontName, String fontPath) {
			this->fontName = fontName;
			this->fontPath = fontPath;
		}

		String fontName;
		String fontPath;
};

class ProjectData {
	public:
		String entryPoint;
		int defaultWidth;
		int defaultHeight;
		bool vSync;
		unsigned int anisotropy;
		unsigned int aaLevel;
		unsigned int frameRate;
		String filteringMode;

		std::vector<String> modules;
		std::vector<ProjectFontData> fonts;

		Number backgroundColorR;
		Number backgroundColorG;
		Number backgroundColorB;
};

class PolycodeProject {
	public:
		PolycodeProject(String name, String path, String file);
		~PolycodeProject();

		bool loadProjectFromFile();
		bool saveFile();

		String getProjectName() { return projectName; }
		String getProjectFile() { return projectFile; }
		String getRootFolder() { return projectFolder; }

		ProjectData data;

private:


	Object configFile;

	String filPath;

	String projectFile;
	String projectFolder;
	String projectName;
};
