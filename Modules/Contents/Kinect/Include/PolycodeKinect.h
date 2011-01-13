/*
 *  PolycodeKinect.h
 *  PolycodeKinectTest
 *
 *  Created by Ivan Safrin on 12/2/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */
#pragma once

#include "Polycode.h"
#include "libfreenect.h"

using namespace Polycode;

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);
void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp);


#define MAX_KINECT_POINTS	6000

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
	
	
protected:
	
	uint16_t t_gamma[2048];
	
	
	int freenect_angle;
	freenect_video_format current_format;
	freenect_video_format requested_format;
	
	
};

class PolycodeKinect : EventHandler {
	public:
		PolycodeKinect(bool calculatePoints);
		~PolycodeKinect();
	
		Texture *getRGBTexture();
		Texture *getCloseDepthTexture();
	
		void tiltUp();
		void tiltDown();
		void Level();
	
		void handleEvent(Event *event);
	
		Vector3 points[MAX_KINECT_POINTS];	
		Color colors[MAX_KINECT_POINTS];
protected:
	
	Timer *updateTimer;

	bool calculatePoints;
	bool calculateColors;
	
	uint8_t *rgbPtr;
	Texture *rgbTexture;
	Texture *closeDepthTexture;
	PolycodeRunner *runner;
	
};

