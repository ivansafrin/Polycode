/*
 Copyright (C) 2013 by Ivan Safrin
 
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

#include <Polycode.h>
#include "PolycodeUI.h"

#include "OSBasics.h"

using namespace Polycode;

class EditorGrid : public Entity {
	public:
		EditorGrid();
		~EditorGrid();
		
        void setGridMode(int mode);
    
        Number getGridSize();
        int getGridLen();
    
        void setGridSize(Number size);
        void setGridLen(int len);
    
        bool isXAxisEnabled();
        bool isYAxisEnabled();
        bool isZAxisEnabled();

        void enableXAxis(bool val);
        void enableYAxis(bool val);
        void enableZAxis(bool val);
    
        void rebuildGrid();
		
        static const int GRID_MODE_3D = 0;
        static const int GRID_MODE_2D_X = 1;
        static const int GRID_MODE_2D_Y = 2;
        static const int GRID_MODE_2D_Z = 3;
    
	private:
        int gridMode;
		SceneMesh *grid;
    
        SceneLine *yLine;
        SceneLine *xLine;
        SceneLine *zLine;
    
        Number gridSize;
        int gridLen;
    
        bool threeDeeGrid;
};


class EditorGridSettingsWindow : public UIWindow {
public:
    EditorGridSettingsWindow(EditorGrid *grid);
    ~EditorGridSettingsWindow();
    
    void handleEvent(Event *event);
    
protected:
    
    EditorGrid *grid;
    
    UICheckBox *visibleCheck;
    
    UITextInput *sizeInput;
    UITextInput *countInput;
    
    UICheckBox *xAxisBox;
    UICheckBox *yAxisBox;
    UICheckBox *zAxisBox;
};
