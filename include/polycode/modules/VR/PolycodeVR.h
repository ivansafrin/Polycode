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

#pragma once

#include <openvr.h>
#include "Polycode.h"

using namespace Polycode;

class PolycodeVR {
public:
	PolycodeVR();

	int shutdownVR();
	int initVR(Core *core, Scene *targetScene);

	void processEvents();
	void Update();
	void Render();
	void submitToCompositorLeft();
	void submitToCompositorRight();
	std::mutex updateMutex;

private:


	static void VRRenderCallbackLeft(void *data);
	static void VRRenderCallbackRight(void *data);

	Matrix4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye, Number nearClip, Number farClip);
	Matrix4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);
	void UpdateHMDMatrixPose();
	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);

	void ProcessVREvent(const vr::VREvent_t & event);

	vr::IVRSystem *m_pHMD;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	std::string m_strPoseClasses;
	Matrix4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];
	char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];
	Matrix4 m_mat4HMDPose;
	float lastTicks;

	int m_iTrackedControllerCount;
	int m_iValidPoseCount;
	int m_iValidPoseCount_Last;

	Camera *leftEyeCamera;
	Camera *rightEyeCamera;

	Core *core;
	Scene *targetScene;

	std::shared_ptr<RenderBuffer> leftRenderTexture;
	std::shared_ptr<RenderBuffer> rightRenderTexture;
};
