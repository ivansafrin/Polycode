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

#include "PolycodeKinect.h"


using namespace Polycode;

PolycodeRunner *polycodeRunner;
pthread_mutex_t gl_backbuf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t usbMutex = PTHREAD_MUTEX_INITIALIZER;

PolycodeRunner::PolycodeRunner() : Threaded() {
	
	polycodeRunner = this;
	
	current_format = FREENECT_VIDEO_RGB;
	requested_format = FREENECT_VIDEO_RGB;
	freenect_angle = 0;		
	
	depth_mid = (uint8_t*)malloc(640*480*3);
	depth_front = (uint8_t*)malloc(640*480*3);
	rgb_back = (uint8_t*)malloc(640*480*3);
	rgb_mid = (uint8_t*)malloc(640*480*3);
	rgb_front = (uint8_t*)malloc(640*480*3);
	
	
	int i;
	for (i=0; i<2048; i++) {
		Number v = i/2048.0;
		v = powf(v, 3)* 5;
		t_gamma[i] = v*6*256;
	}
	
	initKinect();	
}


int PolycodeRunner::initKinect() {
	if (freenect_init(&f_ctx, NULL) < 0) {
		printf("freenect_init() failed\n");
		return 0;
	}	
	
	freenect_set_log_level(f_ctx, FREENECT_LOG_FATAL);
	
	int nr_devices = freenect_num_devices (f_ctx);
	printf ("Number of devices found: %d\n", nr_devices);
	
	
	if (freenect_open_device(f_ctx, &f_dev, 0) < 0) {
		printf("Could not open device\n");
		return 1;
	}
		
	return 1;
}

PolycodeRunner::~PolycodeRunner() {
	
}

void PolycodeRunner::runThread() {
	
	
	freenect_set_tilt_degs(f_dev,freenect_angle);
	freenect_set_led(f_dev,LED_BLINK_GREEN);
	freenect_set_depth_callback(f_dev, depth_cb);
	freenect_set_video_callback(f_dev, rgb_cb);
	freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, current_format));
	freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
	freenect_set_video_buffer(f_dev, rgb_back);
	
	freenect_start_depth(f_dev);
	freenect_start_video(f_dev);
	
	while (threadRunning && freenect_process_events(f_ctx) >= 0) {
		pthread_mutex_lock(&usbMutex);				
		freenect_raw_tilt_state* state;
		freenect_update_tilt_state(f_dev);
		state = freenect_get_tilt_state(f_dev);
		double dx,dy,dz;
		freenect_get_mks_accel(state, &dx, &dy, &dz);
//		printf("\r raw acceleration: %4d %4d %4d  mks acceleration: %4f %4f %4f", state->accelerometer_x, state->accelerometer_y, state->accelerometer_z, dx, dy, dz);
//		fflush(stdout);
		
		if (requested_format != current_format) {
			freenect_stop_video(f_dev);
			freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
			freenect_start_video(f_dev);
			current_format = requested_format;
		}
		pthread_mutex_unlock(&usbMutex);				
	}
	
	printf("\nshutting down streams...\n");	
	printf("Cleaning freenect...\n");
	
	free(depth_mid);
	free(depth_front);
	free(rgb_back);
	free(rgb_mid);
	free(rgb_front);
	
	
	freenect_stop_depth(f_dev);
	freenect_stop_video(f_dev);
	
	freenect_close_device(f_dev);
	freenect_shutdown(f_ctx);	
}

void PolycodeRunner::rgbCallback(freenect_device *dev, void *rgb, uint32_t timestamp) {
	rgb_back = rgb_mid;
	freenect_set_video_buffer(dev, rgb_back);
	rgb_mid = (uint8_t*)rgb;	
}

void PolycodeRunner::depthCallback(freenect_device *dev, void *v_depth, uint32_t timestamp) {
	
	int i;
	uint16_t *depth = (uint16_t*)v_depth;
	
//	pthread_mutex_lock(&gl_backbuf_mutex);
	
	for (i=0; i<640*480; i++) {
		int pval = t_gamma[depth[i]];
		int lb = pval & 0xff;
		depthMap[i] = pval;

		if(pval>>8 == 0) {
			depth_mid[3*i+0] = 255-lb;
			depth_mid[3*i+1] = 255-lb;
			depth_mid[3*i+2] = 255-lb;
		} else {
			depth_mid[3*i+0] = 0;
			depth_mid[3*i+1] = 0;
			depth_mid[3*i+2] = 0;
		}

/*
		switch (pval>>8) {
			case 0:
				depth_mid[3*i+0] = 255;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+2] = 255-lb;
				break;
			case 1:
				depth_mid[3*i+0] = 255;
				depth_mid[3*i+1] = lb;
				depth_mid[3*i+2] = 0;
				break;
			case 2:
				depth_mid[3*i+0] = 255-lb;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+2] = 0;
				break;
			case 3:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+2] = lb;
				break;
			case 4:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+2] = 255;
				break;
			case 5:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 255-lb;
				break;
			default:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
		}
 */
			/*	
		 
			case 0:
				depth_mid[3*i+0] = 255;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+2] = 255;
				break;
			case 1:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
			case 2:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
			case 3:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
			case 4:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
			case 5:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
			default:
				depth_mid[3*i+0] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+2] = 0;
				break;
				
		}
			 */			 
	}
	
}


void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp) {
	pthread_mutex_lock(&gl_backbuf_mutex);	
	polycodeRunner->depthCallback(dev, v_depth, timestamp);	
	pthread_mutex_unlock(&gl_backbuf_mutex);
}

void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp) {
	pthread_mutex_lock(&gl_backbuf_mutex);		
	polycodeRunner->rgbCallback(dev, rgb, timestamp);
	pthread_mutex_unlock(&gl_backbuf_mutex);	
}

void PolycodeRunner::tiltUp() {
	pthread_mutex_lock(&usbMutex);		
	freenect_angle++;
	if (freenect_angle > 30) {
		freenect_angle = 30;
	}	
	freenect_set_tilt_degs(f_dev,freenect_angle);	
	pthread_mutex_unlock(&usbMutex);		
}

void PolycodeRunner::tiltDown() {
	pthread_mutex_lock(&usbMutex);		
	freenect_angle--;
	if (freenect_angle < -30) {
		freenect_angle = -30;
	}
	freenect_set_tilt_degs(f_dev,freenect_angle);	
	pthread_mutex_unlock(&usbMutex);		
	
}

void PolycodeRunner::Level() {
	pthread_mutex_lock(&usbMutex);		
	freenect_angle = 0;
	freenect_set_tilt_degs(f_dev,freenect_angle);	
	pthread_mutex_unlock(&usbMutex);		
	
}

PolycodeKinect::PolycodeKinect(int frequency, bool calculatePoints, int pointCount, int depthStart, int depthEnd, int pixelSkip) {
	
	this->mesh = new Mesh(Mesh::POINT_MESH);
	
	this->pixelSkip = pixelSkip+1;
	this->depthStart = depthStart;
	this->depthEnd = depthEnd;	
	this->pointCount = pointCount;
	
	points = (Vector3*)malloc(sizeof(Vector3) * pointCount);
	colors = (Color*)malloc(sizeof(Color) * pointCount);
	
	this->calculatePoints = calculatePoints;
	this->calculateColors = true;
	rgbTexture = NULL;
	
	if(frequency < 1)
		frequency = 1;
		
	updateTimer = new Timer(true, frequency);
	updateTimer->addEventListener(this, Timer::EVENT_TRIGGER);
	
	
	runner = new PolycodeRunner();
	rgbPtr = runner->rgb_front;
	
	rgbTexture = CoreServices::getInstance()->getMaterialManager()->createTexture(640, 480, (char*)runner->rgb_front, false, Image::IMAGE_RGB);						
	closeDepthTexture = CoreServices::getInstance()->getMaterialManager()->createTexture(640, 480, (char*)runner->depth_mid, false, Image::IMAGE_RGB);
	CoreServices::getInstance()->getCore()->createThread(runner);	
}

void PolycodeKinect::handleEvent(Event *event) {
	if(event->getDispatcher() == updateTimer) {
		Image *newImage = new Image((char*)runner->rgb_back, 640, 480, Image::IMAGE_RGB);
		rgbTexture->setImageData(newImage);
		rgbTexture->recreateFromImageData();
		delete newImage;
		
		newImage = new Image((char*)runner->depth_mid, 640, 480, Image::IMAGE_RGB);
		closeDepthTexture->setImageData(newImage);
		closeDepthTexture->recreateFromImageData();
		delete newImage;				


		if(calculatePoints && calculateColors) {
		
			this->mesh->clearMesh();
		
			for(int i=0; i < this->pointCount; i++) {
				points[i] = Vector3(0,0,0);
				colors[i].setColorRGB(0,0,0);
			}
			
			int ptIndex = 0;
			char *data = closeDepthTexture->getTextureData();
			char *colorData = rgbTexture->getTextureData();
			Color depthColor;
			int pixelOffsetX = 30;
			int pixelOffsetY = 0;
			
				for(int y=0; y < 480; y+= pixelSkip) {
					for(int x=0; x < 640; x += pixelSkip) {					
						
					unsigned int depthArrColor = *((unsigned int*) (data + ((x-pixelOffsetX)*3)+((y+pixelOffsetY)*640*3)));						
					unsigned int testArrColor = *((unsigned int*) (colorData + ((x-pixelOffsetX)*3)+((y+pixelOffsetY)*640*3)));
					depthColor.setColorHexRGB(depthArrColor);
					int pval = runner->depthMap[x + (y*640)];
						
					if(pval > depthStart && pval < depthEnd) {
						if(ptIndex < this->pointCount) {							
							if(calculateColors) {
								colors[ptIndex].setColorHexRGB(testArrColor);
							}
							if(calculatePoints) {
								points[ptIndex] = Vector3(x, y, pval);
							}
							
							Polygon *poly = new Polygon();
							poly->addVertex(x,y,pval);
							mesh->addPolygon(poly);					
							ptIndex++;
						} else {
							return;
						}
					}
				}
			}			
			
		}
		
	}
}

void PolycodeKinect::tiltUp() {
	runner->tiltUp();
}

void PolycodeKinect::tiltDown() {
	runner->tiltDown();	
}

void PolycodeKinect::Level() {
	runner->Level();
}


Texture *PolycodeKinect::getCloseDepthTexture() {
	return closeDepthTexture;
}

Texture *PolycodeKinect::getRGBTexture() {
	return rgbTexture;
}

						
PolycodeKinect::~PolycodeKinect() {
	printf("Cleaning kinect\n");	
	runner->killThread();
}
