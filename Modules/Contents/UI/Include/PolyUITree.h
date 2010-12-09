/*
 *  PolyUITree.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenLabel.h"
#include "PolyScreenImage.h"
#include "PolyScreenShape.h"
#include "PolyScreenEntity.h"
#include "PolyUITreeEvent.h"
#include "PolyUIBox.h"
#include <vector>

using std::vector;

namespace Polycode {

	class _PolyExport UITree : public ScreenEntity {
		public:
			UITree(String icon, String text, float treeWidth, float treeOffset=0);
			~UITree();
			
			void handleEvent(Event *event);
			void toggleCollapsed();
			UITree *addTreeChild(String icon, String text, void *userData = NULL);
			void Update();
			void refreshTree();
			float getTreeHeight();
			void setParent(UITree *parent);
			void clearSelection(UITree *selectedNode);
			bool isCollapsed();
			void *getUserData();
			void setUserData(void *data);
			UITree *getSelectedNode();
			void setIcon(String iconFile);
			void setSelected();
		
			float handleRotation;
		
		private:
		
			void *userData;
			float treeWidth;
			float treeOffset;
			UITree *selectedNode;
			UITree *parent;
			UIBox *selection;
		//	UIBox *bgBox;
			ScreenShape *bgBox;
			ScreenLabel *textLabel;
			ScreenImage *iconImage;
			bool selected;
			float treeHeight;
			vector<UITree*> treeChildren;
			bool collapsed;
			bool collapsing;
			ScreenImage *arrowIconImage;
			String arrowIcon;
			String fontName;
			int size;
			float cellHeight;
			float cellPadding;
	};
}