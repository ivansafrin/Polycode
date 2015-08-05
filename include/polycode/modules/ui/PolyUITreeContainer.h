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
#include "PolyUITree.h"
#include "PolyUIBox.h"
#include "PolyInputKeys.h"
#include "PolyUIElement.h"
#include "PolyUIScrollContainer.h"

namespace Polycode {
	
	class _PolyExport UITreeContainer : public UIElement {
	public:
		UITreeContainer(String icon, String text, Number treeWidth, Number treeHeight);
		virtual ~UITreeContainer();
		
		void handleEvent(Event *event);
		void Resize(Number width, Number height);
		
		UITree *getRootNode();
		Entity *scrollChild;
		
		void onKeyDown(PolyKEY key, wchar_t charCode);
		void onGainFocus();
		
		/**
		 * Scrolls the container to show a specified node.
		 * @param node The tree node to scroll to or show.
		 * @param showAtTop If true, show the node at the top of the container. If false, show it at the bottom.
		 */
		void scrollToNode(UITree *node, bool showAtTop);
		
        UIScrollContainer *getScrollContainer();
        
	protected:
		bool keyNavigable;
		
		UITree *findLastOpenNode(UITree *tree);
		UITree *findNextParentSibling(UITree *parent);
		
	private:
		
		UIScrollContainer *mainContainer;
		
		UITree *rootNode;
		UIBox *bgBox;
	};
}
