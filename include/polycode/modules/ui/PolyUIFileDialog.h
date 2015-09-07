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

#include "PolyGlobals.h"
#include "PolyUIWindow.h"
#include "PolyUIButton.h"
#include "PolyUIScrollContainer.h"
#include "PolyUITextInput.h"
#include "OSBasics.h"
#include "PolyInputEvent.h"

namespace Polycode {

	class CreateFolderWindow : public UIWindow {
		public:
			CreateFolderWindow();
			virtual ~CreateFolderWindow();

			UIButton *okButton;
			UIButton *cancelButton;
			UITextInput *nameInput;

	};

	class UIFileDialogEntry : public UIElement {
		public:
			UIFileDialogEntry(OSFileEntry entry, bool canSelect, int width=340, bool isPlace=false);
			~UIFileDialogEntry();
			void Select();
			void Deselect();

			bool canSelect;
			UIRect *bg;
			UILabel *label;
			OSFileEntry fileEntry;
			UIImage *icon;
	};

	/**
	 * A dialog that allows the user to choose a file or directory from a
	 * file system.
	 */
	class UIFileDialog : public UIWindow {
		public:
			/**
			 * Create a new file dialog.
			 *
			 * @param baseDir The top-level directory, only entries in this directory and below can be selected.
			 * @param foldersOnly If true, directories will be selected. If false, files will be selected.
			 * @param extensions A list of accepted file extensions.
			 * @param allowMultiple If true, multiple entries can be selected at once.
			 */
			UIFileDialog(String baseDir, bool foldersOnly, std::vector<String> extensions, bool allowMultiple);
			virtual ~UIFileDialog();

			void onClose();
			void handleEvent(Event *event);

			/**
			 * Clears all entries in the file dialog.
			 */
			void clearEntries();

			/**
			 * Set a new top-level directory to display.
			 */
			void showFolder(String folderPath);

			/**
			 * Returns whether a file with a specific file extension
			 * can be selected.
			 *
			 * @param extension The file extension to be tested.
			 */
			bool canOpen(String extension);

			void addToSidebar(String path, String name);

			void Update();

			/**
			 * Get the selected entry.
			 *
			 * @return Full path of the selected entry
			 * 		   (base path + relative path to top level directory)
			 */
			String getSelection();

			String action;
		protected:

			String selection;

			String currentFolderPath;

			UIFileDialogEntry *currentEntry;

			bool foldersOnly;
			bool allowMultiple;

			bool doChangeFolder;
			String newPath;

			UIButton *okButton;
			UIButton *cancelButton;
			UIButton *newFolderButton;

			CreateFolderWindow *createFolderWindow;

			UIScrollContainer *scrollContainer;

			std::vector<String> extensions;
			std::vector<UIFileDialogEntry*> entries;
			std::vector<UIFileDialogEntry*> sideBarEntries;
			UIElement *entryHolder;
	};
}

