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

#include "PolySceneSound.h"
#include "PolyCoreServices.h"
#include "PolySound.h"
#include "PolySoundManager.h"

using namespace Polycode;

SceneSoundListener::SceneSoundListener() : SceneEntity() {

}
SceneSoundListener::~SceneSoundListener() {

}

void SceneSoundListener::Update() {
	Matrix4 finalMatrix = getConcatenatedMatrix();
	CoreServices::getInstance()->getSoundManager()->setListenerPosition(finalMatrix.getPosition());
	
	Vector3 direction;
	direction.x = 0;		
	direction.y = 0;
	direction.z = -1;
	direction = finalMatrix.rotateVector(direction);
	CoreServices::getInstance()->getSoundManager()->setListenerOrientation(direction);

}


SceneSound::SceneSound(const String& fileName, Number referenceDistance, Number maxDistance) : SceneEntity() {
	sound = new Sound(fileName);
	sound->setIsPositional(true);
	sound->setPositionalProperties(referenceDistance, maxDistance);
}

SceneSound::~SceneSound() {
	delete sound;
}

void SceneSound::Update() {
	Matrix4 finalMatrix = getConcatenatedMatrix();
	sound->setSoundPosition(finalMatrix.getPosition());
	
	Vector3 direction;
	direction.x = 0;		
	direction.y = 0;
	direction.z = -1;
	direction = finalMatrix.rotateVector(direction);
	sound->setSoundDirection(direction);
	
}

Sound *SceneSound::getSound() {
	return sound;
}
