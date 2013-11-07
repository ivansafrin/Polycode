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

EditorGrid::EditorGrid() : Entity() {
	grid = NULL;
    gridMode = GRID_MODE_3D;
    
	setGrid(1.0);
	setPitch(90);
}

void EditorGrid::setGrid(int gridSize) {
	Polycode::Polygon *gridPoly = new Polycode::Polygon();
	int gridLen = 16;
    
	for(int x=0; x < gridLen+1; x++) {
			gridPoly->addVertex((-gridSize * gridLen * 0.5) + (x * gridSize), (-gridSize * gridLen * 0.5), 0);
			gridPoly->addVertex((-gridSize * gridLen * 0.5) + (x * gridSize) , (-gridSize * gridLen * 0.5) + (gridSize * gridLen), 0);
	}

	for(int y=0; y < gridLen+1; y++) {
			gridPoly->addVertex((-gridSize * gridLen * 0.5), (-gridSize * gridLen * 0.5) + (y * gridSize), 0);
			gridPoly->addVertex((-gridSize * gridLen * 0.5) + (gridSize * gridLen), (-gridSize * gridLen * 0.5) + (y * gridSize), 0);
	}        

	if(grid) {
			grid->getMesh()->clearMesh();
			grid->getMesh()->addPolygon(gridPoly);
	} else {
			Mesh *gridMesh = new Mesh(Mesh::LINE_MESH);
			gridMesh->addPolygon(gridPoly);
				
			grid = new SceneMesh(gridMesh);
			grid->setColor(0.3, 0.3, 0.3, 1.0);
            grid->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
			addChild(grid);
            grid->cacheToVertexBuffer(true);
            
	}
}

void EditorGrid::setGridMode(int mode) {
    gridMode = mode;
    if(gridMode == GRID_MODE_3D) {
        grid->setPitch(0);
    } else {
        grid->setPitch(90);
    }
}

EditorGrid::~EditorGrid() {

}
