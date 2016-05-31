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

#include "polycode/core/PolySceneSound.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolySound.h"
#include "polycode/core/PolySoundManager.h"

using namespace Polycode;

SceneSoundListener::SceneSoundListener() : Entity() {

}
SceneSoundListener::~SceneSoundListener() {

}

void SceneSoundListener::Update() {
	Matrix4 finalMatrix = getConcatenatedMatrix();
	CoreServices::getInstance()->getSoundManager()->setListenerPosition(finalMatrix.getPosition());
    Quaternion orientation;
    orientation.setFromMatrix(finalMatrix);
	CoreServices::getInstance()->getSoundManager()->setListenerOrientation(orientation);
}

void SceneSound::setLoopOnLoad(bool val) {
    loopOnLoad = val;
}

bool SceneSound::getLoopOnLoad() {
    return loopOnLoad;
}


Entity *SceneSound::Clone(bool deepClone, bool ignoreEditorOnly) const {
    SceneSound *newSound = new SceneSound(sound->getFileName(), sound->getReferenceDistance(), sound->getMaxDistance(), directionalSound);
    applyClone(newSound, deepClone, ignoreEditorOnly);
    return newSound;
}

void SceneSound::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    Entity::applyClone(clone, deepClone, ignoreEditorOnly);
    SceneSound *cloneSound = (SceneSound*) clone;
    cloneSound->setLoopOnLoad(loopOnLoad);
    cloneSound->getSound()->setPositionalProperties(sound->getReferenceDistance(), sound->getMaxDistance());
    cloneSound->setDirectionalSound(directionalSound);
    cloneSound->getSound()->setVolume(sound->getVolume());
    cloneSound->getSound()->setPitch(sound->getPitch());
}

SceneSound::SceneSound(const String& fileName, Number referenceDistance, Number maxDistance, bool directionalSound) : Entity() {

	this->directionalSound = directionalSound;
	loopOnLoad = false;
	sound = new Sound(fileName);
	sound->setIsPositional(true);
	sound->setPositionalProperties(referenceDistance, maxDistance);
}

SceneSound::~SceneSound() {
	delete sound;
}

bool SceneSound::isDirectionalSound() const {
    return directionalSound;
}
void SceneSound::setDirectionalSound(bool val) {
    directionalSound = val;
}

void SceneSound::Update() {
	Matrix4 finalMatrix = getConcatenatedMatrix();
	sound->setSoundPosition(finalMatrix.getPosition());
	
	if(directionalSound) {
		Vector3 direction;
		direction.x = 0;		
		direction.y = 0;
		direction.z = -1;
		direction = finalMatrix.rotateVector(direction);
		sound->setSoundDirection(direction);
	}
	
}

Sound *SceneSound::getSound() {
	return sound;
}
