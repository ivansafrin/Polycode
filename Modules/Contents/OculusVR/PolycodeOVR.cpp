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

#include "PolycodeOVR.h"

PolycodeOVR::PolycodeOVR(Scene *parentScene, Number eyeDistanceScale) {
    
    this->eyeDistanceScale = eyeDistanceScale;
    this->parentScene = parentScene;
    
    cameraRoot = new Entity();
    
    cameraBase = new Entity();
    cameraRoot->addChild(cameraBase);
    
    leftCamera = new Camera(parentScene);
    rightCamera = new Camera(parentScene);
    
    leftCamera->setClippingPlanes(0.001, 100.0);
    leftCamera->frustumCulling = false;
    rightCamera->setClippingPlanes(0.001, 100.0);
    rightCamera->frustumCulling = false;
    
    cameraBase->addChild(leftCamera);
    cameraBase->addChild(rightCamera);
    
    initOVR();
}

void PolycodeOVR::initOVR() {
    OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));
    
    pManager = *OVR::DeviceManager::Create();
    pHMD     = *pManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();
    
    if(!pHMD) {
        Logger::log("Could not detect Oculus device\n");
        return;
    }
    
    pSensor = *pHMD->GetSensor();
    if (!pSensor) {
        Logger::log("Could not get Oculus sensor\n");
        return;
    }
    
    SFusion = new OVR::SensorFusion();
    SFusion->AttachToSensor(pSensor);
    
    OVR::HMDInfo hmd;
    if (!pHMD->GetDeviceInfo(&hmd)) {
        Logger::log("Unable to get Oculus device information.\n");
        return;
    }
    
    leftTexture = new SceneRenderTexture(parentScene, leftCamera, hmd.HResolution/2, hmd.VResolution);
    rightTexture = new SceneRenderTexture(parentScene, rightCamera, hmd.HResolution/2, hmd.VResolution);
    
    float halfScreenDistance = (hmd.VScreenSize / 2);
    float yfov = 2.0f * atan(halfScreenDistance/hmd.EyeToScreenDistance);
    
//    leftCamera->setFOV(yfov);
//    rightCamera->setFOV(yfov);
    
    float aspectRatio = float(hmd.HResolution * 0.5f) / float(hmd.VResolution);
    
    float viewCenter             = hmd.HScreenSize * 0.25f;
    float eyeProjectionShift     = viewCenter - hmd.LensSeparationDistance*0.5f;
    float projectionCenterOffset = 4.0f * eyeProjectionShift / hmd.HScreenSize;
    
    OVR::Matrix4f projCenter = OVR::Matrix4f::PerspectiveRH(yfov, aspectRatio, 0.3f, 1000.0f);
    OVR::Matrix4f projLeft   = OVR::Matrix4f::Translation(projectionCenterOffset, 0, 0) * projCenter;
    OVR::Matrix4f projRight  = OVR::Matrix4f::Translation(-projectionCenterOffset, 0, 0) * projCenter;
    
    Matrix4 projLeftPolycode(projLeft.M[0][0], projLeft.M[1][0], projLeft.M[2][0], projLeft.M[3][0],
                             projLeft.M[0][1], projLeft.M[1][1], projLeft.M[2][1], projLeft.M[3][1],
                             projLeft.M[0][2], projLeft.M[1][2], projLeft.M[2][2], projLeft.M[3][2],
                             projLeft.M[0][3], projLeft.M[1][3], projLeft.M[2][3], projLeft.M[3][3]);
    
    leftCamera->setProjectionMode(Camera::MANUAL_MATRIX);
    leftCamera->setProjectionMatrix(projLeftPolycode);
    

    Matrix4 projRightPolycode(projRight.M[0][0], projRight.M[1][0], projRight.M[2][0], projRight.M[3][0],
                              projRight.M[0][1], projRight.M[1][1], projRight.M[2][1], projRight.M[3][1],
                              projRight.M[0][2], projRight.M[1][2], projRight.M[2][2], projRight.M[3][2],
                              projRight.M[0][3], projRight.M[1][3], projRight.M[2][3], projRight.M[3][3]);
    
    rightCamera->setProjectionMode(Camera::MANUAL_MATRIX);
    rightCamera->setProjectionMatrix(projRightPolycode);
    
    interpupilaryDistance = hmd.InterpupillaryDistance;
    float halfIPD  = interpupilaryDistance * 0.5f * eyeDistanceScale;
    leftCamera->setPosition(-halfIPD, 0.0, 0.0);
    rightCamera->setPosition(halfIPD, 0.0, 0.0);
    
    Number scale = 1.0;
    
    leftCamera->setPostFilterByName("VRCorrect");
    leftCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "screenCenter")->setVector2(Vector2(0.5, 0.5));
    leftCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "lensCenter")->setVector2(Vector2(0.5, 0.5));
    leftCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "scale")->setVector2(Vector2(0.5f / scale, 0.5f * aspectRatio / scale));
    leftCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "scaleIn")->setVector2(Vector2(2.0f, 2.0f / aspectRatio));
    leftCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_COLOR, "hmdWarpParam")->setColor(Color(hmd.DistortionK[0], hmd.DistortionK[1], hmd.DistortionK[2], hmd.DistortionK[3]));

    
    rightCamera->setPostFilterByName("VRCorrect");
    rightCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "screenCenter")->setVector2(Vector2(0.5, 0.5));
    rightCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "lensCenter")->setVector2(Vector2(0.5, 0.5));
    rightCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "scale")->setVector2(Vector2(0.5f / scale, 0.5f * aspectRatio / scale));
    rightCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_VECTOR2, "scaleIn")->setVector2(Vector2(2.0f, 2.0f / aspectRatio));
    rightCamera->getLocalShaderOptions()[0]->addParam(ProgramParam::PARAM_COLOR, "hmdWarpParam")->setColor(Color(hmd.DistortionK[0], hmd.DistortionK[1], hmd.DistortionK[2], hmd.DistortionK[3]));
    
}

Number PolycodeOVR::getEyeDistanceScale() {
    return eyeDistanceScale;
}

void PolycodeOVR::setEyeDistanceScale(Number scale) {
    this->eyeDistanceScale = scale;
    float halfIPD  = interpupilaryDistance * 0.5f * eyeDistanceScale;
    leftCamera->setPosition(-halfIPD, 0.0, 0.0);
    rightCamera->setPosition(halfIPD, 0.0, 0.0);

    
}

Texture *PolycodeOVR::getLeftTexture() {
    return leftTexture->getTargetTexture();
}

Texture *PolycodeOVR::getRightTexture() {
    return rightTexture->getTargetTexture();
}

void PolycodeOVR::Update() {
    Quaternion q;
    OVR::Quatf ovrQ = SFusion->GetOrientation();
    q.set(ovrQ.w, ovrQ.x, ovrQ.y, ovrQ.z);
    cameraBase->setRotationByQuaternion(q);
}

Entity *PolycodeOVR::getCameraRoot() {
    return cameraRoot;
}

Entity *PolycodeOVR::getCameraBase() {
    return cameraBase;
}

PolycodeOVR::~PolycodeOVR() {
    if(cameraRoot->getParentEntity()) {
        cameraRoot->getParentEntity()->removeChild(cameraRoot);
    }
    delete cameraRoot;
    delete leftCamera;
    delete rightCamera;
    delete SFusion;
    delete leftTexture;
    delete rightTexture;
}
