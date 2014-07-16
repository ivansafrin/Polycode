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

#include "PolycodeGlobals.h"
#include "PolycodeUI.h"
#include "Polycode.h"
#include "PolycodeProject.h"
#include "OSBasics.h"

using namespace Polycode;

class FolderUserData  {
public:
	String folderPath;
	int type;
};

class AssetEntry : public UIElement {
	public:
		AssetEntry(String assetPath, String assetName, String extension, Resource *resource);
		~AssetEntry();
		
		UIRect *imageShape;
        SceneSprite *spritePreview;
		UILabel *nameLabel;
		
		String assetPath;
        Resource *resource;
		UIRect *selectShape;
};

class AssetList : public UIElement {
	public:
		AssetList();
		~AssetList();
		
		void handleEvent(Event *event);
		
		bool hasExtension(String extension);
    
        void clearList();
		
		void showFolder(String folderPath);
        void showResourcePool(ResourcePool *pool, int resourceFilter);
    
        Resource *getSelectedResource();
    
		String selectedPath;
		
		void setExtensions(std::vector<String> extensions);
		
	protected:
	
        Resource *selectedResource;
		UIImageButton *reloadButton;
	
		String currentFolderPath;
	
		AssetEntry *currentEntry;		
		std::vector<AssetEntry*> assetEntries;
		
		std::vector<String> extensions;
};

class AssetBrowser : public UIWindow {
	public:
		AssetBrowser();
		~AssetBrowser();
	
		String getSelectedAssetPath();
		String getFullSelectedAssetPath();
			
		void parseFolderIntoTree(UITree *tree, OSFileEntry folder);

		String getTemplatePath();
		String getFileName();
		
		void setExtensions(std::vector<String> extensions);
		
		void setProject(PolycodeProject *project);
    
        void setBrowseMode(unsigned int newBrowseMode);

        void setResourcePools(std::vector<ResourcePool*> pools, int resourceFilter);
        void setResourceFilter(int resourceType);
		void handleEvent(Event *event);
    
        Resource *getSelectedResource();
    
        static const int BROWSE_MODE_FILES = 0;
        static const int BROWSE_MODE_RESOURCES = 1;
	
	protected:
	
		AssetList *assetList;
		UIScrollContainer *listContainer;
	
		PolycodeProject *currentProject;
	
        unsigned int browseMode;
        int resourceFilter;
    
		UIButton *cancelButton;
		UIButton *okButton;
		
		String templatePath;
			
		UITreeContainer *templateContainer;	
		UITree *defaultTemplateTree;
};