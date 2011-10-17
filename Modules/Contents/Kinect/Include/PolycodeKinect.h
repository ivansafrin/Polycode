/*
Copyright (C) 2011 by Ivan Safrin

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

#include "Polycode.h"
#include "libfreenect.h"

using namespace Polycode;

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);
void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp);

class PolycodeRunner : public Threaded {
public:
	PolycodeRunner();
	~PolycodeRunner();
	
	void runThread();
	void updateThread() {}
	
	void rgbCallback(freenect_device *dev, void *rgb, uint32_t timestamp);
	void depthCallback(freenect_device *dev, void *v_depth, uint32_t timestamp);
	
//	static void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);
//	static void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp);
	
	int initKinect();
	
	void tiltUp();
	void tiltDown();
	void Level();	
	
	CoreMutex *drawMutex;
		
	uint8_t *depth_mid, *depth_front;
	uint8_t *rgb_back, *rgb_mid, *rgb_front;
		
	freenect_context *f_ctx;
	freenect_device *f_dev;
	int depthMap[640*480];	
	
protected:
	
	uint16_t t_gamma[2048];
	
	
	int freenect_angle;
	freenect_video_format current_format;
	freenect_video_format requested_format;
	
	
};

class PolycodeKinect : EventHandler {
	public:
		PolycodeKinect(int frequency, bool calculatePoints, int pointCount, int depthStart, int depthEnd, int pixelSkip);
		~PolycodeKinect();
	
		Texture *getRGBTexture();
		Texture *getCloseDepthTexture();
	
		void tiltUp();
		void tiltDown();
		void Level();
	
		void handleEvent(Event *event);
		
		Mesh *mesh;
	
		Vector3 *points;
		Color *colors;
protected:
	
	int pointCount;
	int depthStart;
	int depthEnd;
	int pixelSkip;
	
	Timer *updateTimer;

	bool calculatePoints;
	bool calculateColors;
	
	uint8_t *rgbPtr;
	Texture *rgbTexture;
	Texture *closeDepthTexture;
	PolycodeRunner *runner;
	
};

