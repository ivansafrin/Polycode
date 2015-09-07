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
#include "OSBasics.h"

using namespace Polycode;

class TextInputPopup : public UIWindow {
	public:
		TextInputPopup();
		~TextInputPopup();
		
		void setCaption(String caption);
		void setValue(String value);
		String getValue();
		void handleEvent(Event *event);
		
        virtual void onGainFocus();
    
		String action;
				
	protected:
	
		UITextInput *textInput;
	
		UIButton *cancelButton;
		UIButton *okButton;	
};

class MessagePopup : public UIWindow {
    public:
    MessagePopup();
    ~MessagePopup();
    
    void setCaption(String caption);
    void handleEvent(Event *event);
    
    virtual void onGainFocus();
    
        String action;
        UILabel *captionLabel;
        UIButton *okButton;
    
};

class YesNoPopup : public UIWindow {
	public:
		YesNoPopup();
		~YesNoPopup();
		
		void setCaption(String caption);
		void handleEvent(Event *event);
		
        virtual void onGainFocus();
    
		String action;
	
		UILabel *captionLabel;
	
		UIElement *buttonAnchor;
		UIButton *cancelButton;
		UIButton *okButton;	
};


class YesNoCancelPopup : public UIWindow {
	public:
		YesNoCancelPopup();
		~YesNoCancelPopup();
		
		void setCaption(String caption);
		void handleEvent(Event *event);
		
        virtual void onGainFocus();
    
		String action;
	
		UILabel *captionLabel;
	
		UIElement *buttonAnchor;
		UIButton *cancelButton;
		UIButton *noButton;		
		UIButton *okButton;
};

class AssetImporterWindow : public UIWindow {
	public:
		AssetImporterWindow();
		~AssetImporterWindow();

		void clearFiles();
		void addFile(String fileName);
		void setFilesToImport(String files);
		
		void setSourceFileAndTargetFolder(String file, String folder, String projectRelativeFolder);
		void refreshPreview();
    
        virtual void onGainFocus();
			
		void handleEvent(Event *event);	
			
	protected:

		String file;
		String folder;
		String projectRelativeFolder;
    
		UIButton *cancelButton;
		UIButton *okButton;
		std::vector<UILabel*> fileLabels;

		UICheckBox *usePrefixCheckbox;
		UITextInput *prefixInput;
		UICheckBox *addMeshesCheckbox;
		UICheckBox *generateTangensCheckbox;
		UICheckBox *generateNormalsCheckbox;
		UICheckBox *swapZYAxisCheckbox;

        UICheckBox *exportNormals;
        UICheckBox *exportTangents;
        UICheckBox *exportColors;
        UICheckBox *exportBoneWeights;
        UICheckBox *exportUVs;
        UICheckBox *exportSecondaryUVs;
        UICheckBox *exportScene;
    
        UICheckBox *generateMatFile;
        UICheckBox *overrideMaterial;
        UITextInput *overrideMaterialInput;
    
		UIElement *filesAnchor;
		UIScrollContainer *filesScroller;

		UILabel *filesToImportLabel;
};

