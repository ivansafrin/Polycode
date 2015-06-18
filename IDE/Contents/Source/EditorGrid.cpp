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
 
#include "EditorGrid.h"

EditorGridSettingsWindow::EditorGridSettingsWindow(EditorGrid *grid) : UIWindow("Grid Settings", 100, 190) {
    
    visible = false;
    enabled = false;
    
    this->grid = grid;
    
    visibleCheck = new UICheckBox("Enabled", grid->visible);
    addChild(visibleCheck);
    visibleCheck->setPosition(10, 40);
    visibleCheck->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    UILabel *label = new UILabel("Size:", 12);
    label->setColor(1.0, 1.0 ,1.0, 1.0);
    addChild(label);
    label->setPosition(10, 70);
    
    sizeInput = new UITextInput(false, 50, 10);
    addFocusChild(sizeInput);
    sizeInput->setPosition(60, 68);
    sizeInput->setNumberOnly(true);
    sizeInput->setText(String::NumberToString(grid->getGridSize()));
    sizeInput->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    label = new UILabel("Count:", 12);
    label->setColor(1.0, 1.0 ,1.0, 1.0);
    addChild(label);
    label->setPosition(10, 100);

    countInput = new UITextInput(false, 50, 10);
    addFocusChild(countInput);
    countInput->setPosition(60, 98);
    countInput->setNumberOnly(true);
    countInput->setText(String::IntToString(grid->getGridLen()));
    countInput->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    xAxisBox = new UICheckBox("X Axis", grid->isXAxisEnabled());
    addChild(xAxisBox);
    xAxisBox->setPosition(10, 130);
    xAxisBox->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    yAxisBox = new UICheckBox("Y Axis", grid->isYAxisEnabled());
    addChild(yAxisBox);
    yAxisBox->setPosition(10, 155);
    yAxisBox->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    zAxisBox = new UICheckBox("Z Axis", grid->isZAxisEnabled());
    addChild(zAxisBox);
    zAxisBox->setPosition(10, 180);
    zAxisBox->addEventListener(this, UIEvent::CHANGE_EVENT);
}

void EditorGridSettingsWindow::handleEvent(Event *event) {
    if(event->getDispatcher() == sizeInput) {
        grid->setGridSize(sizeInput->getText().toNumber());
    } else if(event->getDispatcher() == countInput) {
        grid->setGridLen(countInput->getText().toInteger());
    } else if(event->getDispatcher() == xAxisBox) {
        grid->enableXAxis(xAxisBox->isChecked());
    } else if(event->getDispatcher() == yAxisBox) {
        grid->enableYAxis(yAxisBox->isChecked());
    } else if(event->getDispatcher() == zAxisBox) {
        grid->enableZAxis(zAxisBox->isChecked());
    } else if(event->getDispatcher() == visibleCheck) {
        grid->visible = visibleCheck->isChecked();
    }
    UIWindow::handleEvent(event);
}

EditorGridSettingsWindow::~EditorGridSettingsWindow() {
    
}

EditorGrid::EditorGrid() : Entity() {
	grid = NULL;
    gridMode = GRID_MODE_3D;
    
    Mesh *gridMesh = new Mesh(Mesh::LINE_MESH);
    
    grid = new SceneMesh(gridMesh);
    grid->setColor(0.3, 0.3, 0.3, 1.0);
    grid->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
    addChild(grid);
    
    yLine = new SceneLine(Vector3(), Vector3());
    addChild(yLine);
    yLine->setColor(0.0, 0.8, 0.0, 1.0);
    yLine->visible = false;
    
    xLine = new SceneLine(Vector3(), Vector3());
    addChild(xLine);
    xLine->setColor(0.8, 0.0, 0.0, 1.0);
    
    zLine = new SceneLine(Vector3(), Vector3());
    addChild(zLine);
    zLine->setColor(0.0, 0.0, 0.8, 1.0);

    gridSize = 1.0;
    gridLen = 16;
    
    
    rebuildGrid();
    grid->setPitch(90);
}

void EditorGrid::setGridSize(Number size) {
    gridSize = size;
    rebuildGrid();
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void EditorGrid::setGridLen(int len) {
    gridLen = len;
    rebuildGrid();
}

Number EditorGrid::getGridSize() {
    return gridSize;
}

int EditorGrid::getGridLen() {
    return gridLen;
}

bool EditorGrid::isXAxisEnabled() {
    return xLine->visible;
}

bool EditorGrid::isYAxisEnabled() {
    return yLine->visible;
}

bool EditorGrid::isZAxisEnabled() {
     return zLine->visible;
}

void EditorGrid::enableXAxis(bool val) {
    xLine->visible = val;
}

void EditorGrid::enableYAxis(bool val) {
    yLine->visible = val;
}

void EditorGrid::enableZAxis(bool val) {
    zLine->visible = val;
}

void EditorGrid::rebuildGrid() {
    
    int gridLen = this->gridLen;
    
    // make sure the grid is even
    if((gridLen % 2) != 0) {
        gridLen++;
    }
    
    grid->getMesh()->clearMesh();

    for(int x=0; x < gridLen+1; x++) {
        grid->getMesh()->addVertex((-gridSize * gridLen * 0.5) + (x * gridSize), (-gridSize * gridLen * 0.5), 0);
        grid->getMesh()->addVertex((-gridSize * gridLen * 0.5) + (x * gridSize) , (-gridSize * gridLen * 0.5) + (gridSize * gridLen), 0);
    }
    
    for(int y=0; y < gridLen+1; y++) {
        grid->getMesh()->addVertex((-gridSize * gridLen * 0.5), (-gridSize * gridLen * 0.5) + (y * gridSize), 0);
        grid->getMesh()->addVertex((-gridSize * gridLen * 0.5) + (gridSize * gridLen), (-gridSize * gridLen * 0.5) + (y * gridSize), 0);
    }
    
    yLine->setStart(Vector3(0.0, gridSize * gridLen * 0.5, 0.0));
    yLine->setEnd(Vector3(0.0, gridSize * gridLen * -0.5, 0.0));

    xLine->setStart(Vector3(gridSize * gridLen * 0.5, 0.0, 0.0));
    xLine->setEnd(Vector3(gridSize * gridLen * -0.5, 0.0, 0.0));

    zLine->setStart(Vector3(0.0, 0.0, gridSize * gridLen * 0.5));
    zLine->setEnd(Vector3(0.0, 0.0, gridSize * gridLen * -0.5));
    
    grid->setLocalBoundingBox(grid->getMesh()->calculateBBox());
    
    grid->cacheToVertexBuffer(true);
}

void EditorGrid::setGridMode(int mode) {
    gridMode = mode;
    switch(gridMode) {
        case GRID_MODE_3D:
            grid->setPitch(90);
            grid->setYaw(0);
        break;
        case GRID_MODE_2D_X:
            grid->setYaw(-90);
            grid->setPitch(0);
        break;
        case GRID_MODE_2D_Y:
            grid->setPitch(90);
            grid->setYaw(0);
        break;
        case GRID_MODE_2D_Z:
            grid->setPitch(0);
            grid->setYaw(0);
        break;
    }
}

EditorGrid::~EditorGrid() {

}
