/*
 Copyright (C) 2016 by Ivan Safrin
 
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

#include "polycode/modules/VR/PolycodeVR.h"


PolycodeVR::PolycodeVR() {

}

int PolycodeVR::initVR(Core *core, Scene *targetScene) {

	this->core = core;

	vr::EVRInitError eError = vr::VRInitError_None;
	m_pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	this->targetScene = targetScene;

	if (eError != vr::VRInitError_None)
	{
		Logger::log("Error initializing OpenVR!\n");
		return 0;
	}

	if (!vr::VRCompositor())
	{
		Logger::log("Compositor initialization failed. See log file for details\n");
		return 0;
	}

	uint32_t nRenderWidth;
	uint32_t nRenderHeight;
	m_pHMD->GetRecommendedRenderTargetSize(&nRenderWidth, &nRenderHeight);


	leftEyeCamera = new Camera();
	rightEyeCamera = new Camera();

	leftEyeCamera->setProjectionMode(Camera::MANUAL_MATRIX);
	rightEyeCamera->setProjectionMode(Camera::MANUAL_MATRIX);

	targetScene->addChild(leftEyeCamera);
	targetScene->addChild(rightEyeCamera);

	leftRenderTexture = std::make_shared<RenderBuffer>(nRenderWidth, nRenderHeight, true, false);
	rightRenderTexture = std::make_shared<RenderBuffer>(nRenderWidth, nRenderHeight, true, false);


	vr::VRCompositor()->FadeGrid(0.0, false);
	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, 0, NULL, 0);

	return 1;
}

int PolycodeVR::shutdownVR() {
	vr::VR_Shutdown();
	return 1;
}

Matrix4 PolycodeVR::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye, Number nearClip, Number farClip) {
	if (!m_pHMD) {
		return Matrix4();
	}

	vr::HmdMatrix44_t mat = m_pHMD->GetProjectionMatrix(nEye, nearClip, farClip, vr::API_OpenGL);

	return Matrix4(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);
}

Matrix4 PolycodeVR::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye) {
	if (!m_pHMD) {
		return Matrix4();
	}

	vr::HmdMatrix34_t matEyeRight = m_pHMD->GetEyeToHeadTransform(nEye);
	Matrix4 matrixObj(
		matEyeRight.m[0][0], matEyeRight.m[1][0], matEyeRight.m[2][0], 0.0,
		matEyeRight.m[0][1], matEyeRight.m[1][1], matEyeRight.m[2][1], 0.0,
		matEyeRight.m[0][2], matEyeRight.m[1][2], matEyeRight.m[2][2], 0.0,
		matEyeRight.m[0][3], matEyeRight.m[1][3], matEyeRight.m[2][3], 1.0f
	);

	return matrixObj;
}

Matrix4 PolycodeVR::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	Matrix4 matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	);
	return matrixObj;
}

void PolycodeVR::UpdateHMDMatrixPose() {
	if (!m_pHMD) {
		return;
	}

	//vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, 0, NULL, 0);
	
	float frameTime = (float)(core->getRenderer()->getRenderThread()->getFrameInfo().timeTaken)/1000.0f;
	float fDisplayFrequency = m_pHMD->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_DisplayFrequency_Float);
	float fFrameDuration = 1.f / fDisplayFrequency;
	float fVsyncToPhotons = m_pHMD->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SecondsFromVsyncToPhotons_Float);
	float fSecondsSinceLastVsync = core->getTicksFloat() - lastTicks;
	float fPredictedSecondsFromNow = fFrameDuration - fSecondsSinceLastVsync + fVsyncToPhotons;

	m_pHMD->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, fPredictedSecondsFromNow, m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount);
	
	vr::VRCompositor()->WaitGetPoses(NULL, 0, m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount);
	//vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);


	m_iValidPoseCount = 0;
	m_strPoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_iValidPoseCount++;
			m_rmat4DevicePose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (m_pHMD->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_Other:             m_rDevClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
				default:                                       m_rDevClassChar[nDevice] = '?'; break;
				}
			}
			m_strPoseClasses += m_rDevClassChar[nDevice];
		}
	}

	if (m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd];
	}
}


void PolycodeVR::ProcessVREvent(const vr::VREvent_t & event)
{
	switch (event.eventType)
	{
	case vr::VREvent_TrackedDeviceActivated:
	{
		//SetupRenderModelForTrackedDevice(event.trackedDeviceIndex);
		//dprintf("Device %u attached. Setting up render model.\n", event.trackedDeviceIndex);
	}
	break;
	case vr::VREvent_TrackedDeviceDeactivated:
	{
		//dprintf("Device %u detached.\n", event.trackedDeviceIndex);
	}
	break;
	case vr::VREvent_TrackedDeviceUpdated:
	{
		//dprintf("Device %u updated.\n", event.trackedDeviceIndex);
	}
	break;
	}
}

void PolycodeVR::processEvents() {
	if (!m_pHMD) {
		return;
	}

	vr::VREvent_t event;
	while (m_pHMD->PollNextEvent(&event, sizeof(event)))
	{
		ProcessVREvent(event);
	}

	for (vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++)
	{
		vr::VRControllerState_t state;
		if (m_pHMD->GetControllerState(unDevice, &state))
		{
			//m_rbShowTrackedDevice[unDevice] = state.ulButtonPressed == 0;
		}
	}

}

void PolycodeVR::Update() {
	if (!m_pHMD) {
		return;
	}

	UpdateHMDMatrixPose();
	processEvents();


	Matrix4 mat4ProjectionLeft = GetHMDMatrixProjectionEye(vr::Eye_Left, leftEyeCamera->getNearClippingPlane(), leftEyeCamera->getFarClippingPlane());
	Matrix4 mat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right, rightEyeCamera->getNearClippingPlane(), rightEyeCamera->getFarClippingPlane());
	Matrix4 mat4eyePosLeft = GetHMDMatrixPoseEye(vr::Eye_Left) * m_mat4HMDPose;
	Matrix4 mat4eyePosRight = GetHMDMatrixPoseEye(vr::Eye_Right) * m_mat4HMDPose;

	leftEyeCamera->setCustomProjectionMatrix(mat4ProjectionLeft);
	rightEyeCamera->setCustomProjectionMatrix(mat4ProjectionRight);

	targetScene->getDefaultCamera()->setTransformByMatrixPure(m_mat4HMDPose);

	leftEyeCamera->setTransformByMatrixPure(mat4eyePosLeft);
	rightEyeCamera->setTransformByMatrixPure(mat4eyePosRight);

;

}

void PolycodeVR::Render() {
	RenderFrame *frame = new RenderFrame(leftEyeCamera->getViewport());
	frame->customFrameFinalizer = &PolycodeVR::VRRenderCallbackLeft;
	frame->customFrameFinalizerData = (void*)this;
	targetScene->Render(frame, leftEyeCamera, leftRenderTexture, NULL, false);
	core->getRenderer()->submitRenderFrame(frame);

	frame = new RenderFrame(rightEyeCamera->getViewport());
	frame->customFrameFinalizer = &PolycodeVR::VRRenderCallbackRight;
	frame->customFrameFinalizerData = (void*)this;
	targetScene->Render(frame, rightEyeCamera, rightRenderTexture, NULL, false);
	core->getRenderer()->submitRenderFrame(frame);
}


void PolycodeVR::submitToCompositorRight() {
	if (rightRenderTexture->colorTexture) {
		if (rightRenderTexture->colorTexture->platformData.data) {
			uint32_t val = *((uint32_t*)rightRenderTexture->colorTexture->platformData.data);
			vr::Texture_t rightEyeTexture = { (void*)val, vr::API_OpenGL, vr::ColorSpace_Gamma };
			vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);
		}
	}

	lastTicks = core->getTicksFloat();
}

void PolycodeVR::submitToCompositorLeft() {
	if (leftRenderTexture->colorTexture) {
		if (leftRenderTexture->colorTexture->platformData.data) {
			uint32_t val = *((uint32_t*)leftRenderTexture->colorTexture->platformData.data);
			vr::Texture_t leftEyeTexture = { (void*)val, vr::API_OpenGL, vr::ColorSpace_Gamma };
			vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
		}
	}
}

void PolycodeVR::VRRenderCallbackRight(void *data) {
	PolycodeVR *vr = (PolycodeVR*)data;
	vr->submitToCompositorRight();
}

void PolycodeVR::VRRenderCallbackLeft(void *data) {
	PolycodeVR *vr = (PolycodeVR*)data;
	vr->submitToCompositorLeft();
}