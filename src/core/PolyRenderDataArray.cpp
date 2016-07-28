/*
 Copyright (C) 2014 by Ivan Safrin
 
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

#include "polycode/core/PolyRenderDataArray.h"
#include "polycode/core/PolyRenderer.h"

using namespace Polycode;

RenderDataArray::RenderDataArray(unsigned int type) : type(type) {

}

RenderDataArray::RenderDataArray(const RenderDataArray &other) {
	type = other.type;
	customArrayName = other.customArrayName;
}

RenderDataArray &RenderDataArray::operator=(const RenderDataArray &other) {
	type = other.type;
	return *this;
}

void *RenderDataArray::getArrayData()  const{
	return NULL;
}

unsigned int RenderDataArray::getDataSize() const {
	return 0;
}

VertexDataArray::VertexDataArray(const VertexDataArray &other) : RenderDataArray(other) {
	countPerVertex = other.countPerVertex;
	data = other.data;
}

VertexDataArray &VertexDataArray::operator=(const VertexDataArray &other) {
	data = other.data;
	countPerVertex = other.countPerVertex;
	RenderDataArray::operator=(other);
	return *this;
}

void *VertexDataArray::getArrayData() const {
	return (void*) data.data();
}

unsigned int VertexDataArray::getDataSize()	 const{
	return data.size();
}

IndexDataArray &IndexDataArray::operator=(const IndexDataArray &other) {
	data = other.data;
	RenderDataArray::operator=(other);
	return *this;
}

IndexDataArray::IndexDataArray(const IndexDataArray &other) : RenderDataArray(other) {
	data = other.data;
}

void *IndexDataArray::getArrayData() const {
	return (void*) data.data();
}

unsigned int IndexDataArray::getDataSize()	const {
	return data.size();
}

unsigned char VertexDataArray::getCountPerVertex() const {
	return countPerVertex;
}