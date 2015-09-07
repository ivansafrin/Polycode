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
#include "PolyUIElement.h"
#include "PolySceneLabel.h"
#include "PolySceneImage.h"
#include "PolyScenePrimitive.h"
#include "PolyEntity.h"
#include "PolyUITreeEvent.h"
#include "PolyUIBox.h"
#include "PolyTween.h"
#include <vector>

using std::vector;

namespace Polycode {

	class _PolyExport UITree : public UIElement {
		public:
			using UIElement::Resize;

			UITree(String icon, String text, Number treeWidth, Number treeOffset=0);
			virtual ~UITree();
			
			
			void handleEvent(Event *event);
			void toggleCollapsed();
			UITree *addTreeChild(String icon, String text, void *userData = NULL);
			void Update();
			void refreshTree();
			Number getTreeHeight();
			void setParent(UITree *parent);
			void clearSelection(UITree *selectedNode);
			bool isCollapsed();
			void *getUserData();
			void setUserData(void *data);
			UITree *getSelectedNode();
			void setIcon(String iconFile);
			void setSelected(bool byKey=false);
			
			void setLabelText(const String &text);
			
			void Resize(Number width);
		
			int getNumTreeChildren() { return treeChildren.size(); }
			UITree *getTreeChild(int index) { return treeChildren[index]; }
			void removeTreeChild(UITree *child);
			void clearTree();
		
			String getLabelText();
			
			Number handleRotation;

			UITree *getParent();
			bool hasTreeChildren() { return (getNumTreeChildren()); }
			UITree *getPrevSibling();
			UITree *getNextSibling();
			Number getCellHeight() { return cellHeight; }

			bool isSelectedByKey() { return selectedByKey; }
		
		private:

			bool willDrag;
			bool isDragging;
		
			String labelText;
			void *userData;
			Number treeWidth;
			Number treeOffset;
			UITree *selectedNode;
			UITree *parent;
			Number padding;
			UIBox *selection;
			Entity *bgBox;
			SceneLabel *textLabel;
			UIImage *iconImage;
			bool selected;
			Number treeHeight;
			vector<UITree*> treeChildren;
			bool collapsed;
			UIImage *arrowIconImage;
			String arrowIcon;
			Vector2 mouseDownPosition;
			String fontName;
			int size;
			Number cellHeight;
			Number cellPadding;

			bool selectedByKey;
	};
}
