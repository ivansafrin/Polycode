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

#pragma once

 #include "OVR.h"
 #include "Polycode.h"

using namespace Polycode;

class PolycodeOVR {
    public:
        PolycodeOVR(Scene *parentScene, Number scale);
        ~PolycodeOVR();
    
        void initOVR();
    
        Texture *getLeftTexture();
        Texture *getRightTexture();
    
        void Update();
        Entity *getCameraRoot();
        Entity *getCameraBase();
    
        void setEyeDistanceScale(Number scale);
        Number getEyeDistanceScale();
    protected:
    
        float    interpupilaryDistance;
        Number eyeDistanceScale;
    
        OVR::Ptr<OVR::DeviceManager> pManager;
        OVR::Ptr<OVR::HMDDevice>     pHMD;
        OVR::Ptr<OVR::SensorDevice> pSensor;
        OVR::SensorFusion *SFusion;
    
        Entity *cameraRoot;
        Entity *cameraBase;
    
        SceneRenderTexture *leftTexture;
        SceneRenderTexture *rightTexture;
    
        Scene *parentScene; 
    
        Camera *leftCamera;
        Camera *rightCamera;
};
