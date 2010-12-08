/*
 *  PolyUITreeContainer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/18/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyUITree.h"
#include "PolyUIBox.h"
#include "PolyUIScrollContainer.h"

namespace Polycode {
	
	class _PolyExport UITreeContainer : public ScreenEntity {
	public:
		UITreeContainer(string icon, wstring text, float treeWidth, float treeHeight);
		~UITreeContainer();
		
		void handleEvent(Event *event);
		void Resize(int x, int y);
		
		UITree *getRootNode();
		ScreenEntity *scrollChild;
	private:
		
		UIScrollContainer *mainContainer;
		ScreenShape *maskShape;
		
		UITree *rootNode;
		UIBox *bgBox;
	};

}