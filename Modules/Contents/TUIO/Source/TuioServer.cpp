/*
	TUIO Server Component - part of the reacTIVision project
	http://reactivision.sourceforge.net/

	Copyright (c) 2005-2009 Martin Kaltenbrunner <mkalten@iua.upf.edu>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "TuioServer.h"

using namespace TUIO;
using namespace osc;

#ifndef WIN32
static void* ThreadFunc( void* obj )
#else
static DWORD WINAPI ThreadFunc( LPVOID obj )
#endif
{
	TuioServer *tuioServer = static_cast<TuioServer*>(obj);
	while ((tuioServer->isConnected()) && (tuioServer->periodicMessagesEnabled())) {
		tuioServer->sendFullMessages();
#ifndef WIN32
		usleep(USEC_SECOND*tuioServer->getUpdateInterval());
#else
		Sleep(MSEC_SECOND*tuioServer->getUpdateInterval());
#endif
	}	
	return 0;
};

void TuioServer::enablePeriodicMessages(int interval) {
	if (periodic_update) return;
	
	update_interval = interval;
	periodic_update = true;
	
#ifndef WIN32
	pthread_create(&thread , NULL, ThreadFunc, this);
#else
	DWORD threadId;
	thread = CreateThread( 0, 0, ThreadFunc, this, 0, &threadId );
#endif
}

void TuioServer::disablePeriodicMessages() {
	if (!periodic_update) return;
	periodic_update = false;
	
#ifdef WIN32
	if( thread ) CloseHandle( thread );
#endif
	thread = NULL;	
}

void TuioServer::sendFullMessages() {
	
	// prepare the cursor packet
	fullPacket->Clear();
	(*fullPacket) << osc::BeginBundleImmediate;
	
	// add the cursor alive message
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive";
	for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++)
		(*fullPacket) << (int32)((*tuioCursor)->getSessionID());	
	(*fullPacket) << osc::EndMessage;	

	// add all current cursor set messages
	for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		
		// start a new packet if we exceed the packet capacity
		if ((fullPacket->Capacity()-fullPacket->Size())<CUR_MESSAGE_SIZE) {
			
			// add the immediate fseq message and send the cursor packet
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << -1 << osc::EndMessage;
			(*fullPacket) << osc::EndBundle;
			socket->Send( fullPacket->Data(), fullPacket->Size() );

			// prepare the new cursor packet
			fullPacket->Clear();	
			(*fullPacket) << osc::BeginBundleImmediate;
			
			// add the cursor alive message
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive";
			for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++)
				(*fullPacket) << (int32)((*tuioCursor)->getSessionID());	
			(*fullPacket) << osc::EndMessage;				
		}

		// add the actual cursor set message
		(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "set";
		(*fullPacket) << (int32)((*tuioCursor)->getSessionID()) << (*tuioCursor)->getX() << (*tuioCursor)->getY();
		(*fullPacket) << (*tuioCursor)->getXSpeed() << (*tuioCursor)->getYSpeed() <<(*tuioCursor)->getMotionAccel();	
		(*fullPacket) << osc::EndMessage;	
	}
	
	// add the immediate fseq message and send the cursor packet
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << -1 << osc::EndMessage;
	(*fullPacket) << osc::EndBundle;
	socket->Send( fullPacket->Data(), fullPacket->Size() );
	
	// prepare the object packet
	fullPacket->Clear();
	(*fullPacket) << osc::BeginBundleImmediate;
	
	// add the object alive message
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive";
	for (std::list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++)
		(*fullPacket) << (int32)((*tuioObject)->getSessionID());	
	(*fullPacket) << osc::EndMessage;	

	for (std::list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		
		// start a new packet if we exceed the packet capacity
		if ((fullPacket->Capacity()-fullPacket->Size())<OBJ_MESSAGE_SIZE) {
			// add the immediate fseq message and send the object packet
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << -1 << osc::EndMessage;
			(*fullPacket) << osc::EndBundle;
			socket->Send( fullPacket->Data(), fullPacket->Size() );
			
			// prepare the new object packet
			fullPacket->Clear();	
			(*fullPacket) << osc::BeginBundleImmediate;
			
			// add the object alive message
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive";
			for (std::list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++)
				(*fullPacket) << (int32)((*tuioObject)->getSessionID());	
			(*fullPacket) << osc::EndMessage;	
		}

		// add the actual object set message
		(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "set";
		(*fullPacket) << (int32)((*tuioObject)->getSessionID()) << (*tuioObject)->getSymbolID() << (*tuioObject)->getX() << (*tuioObject)->getY() << (*tuioObject)->getAngle();
		(*fullPacket) << (*tuioObject)->getXSpeed() << (*tuioObject)->getYSpeed() << (*tuioObject)->getRotationSpeed() << (*tuioObject)->getMotionAccel() << (*tuioObject)->getRotationAccel();	
		(*fullPacket) << osc::EndMessage;
		
	}
	// add the immediate fseq message and send the object packet
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << -1 << osc::EndMessage;
	(*fullPacket) << osc::EndBundle;
	socket->Send( fullPacket->Data(), fullPacket->Size() );
}

TuioServer::TuioServer() {
	initialize("127.0.0.1",3333,MAX_UDP_SIZE);
}

TuioServer::TuioServer(const char *host, int port) {
	initialize(host,port,IP_MTU_SIZE);
}

TuioServer::TuioServer(const char *host, int port, int size) {
	initialize(host,port,size);
}

void TuioServer::initialize(const char *host, int port, int size) {
	if (size>MAX_UDP_SIZE) size = MAX_UDP_SIZE;
	else if (size<MIN_UDP_SIZE) size = MIN_UDP_SIZE;

	try {
		long unsigned int ip = GetHostByName(host);
		socket = new UdpTransmitSocket(IpEndpointName(ip, port));

		oscBuffer = new char[size];
		oscPacket = new osc::OutboundPacketStream(oscBuffer,size);
		fullBuffer = new char[size];
		fullPacket = new osc::OutboundPacketStream(fullBuffer,size);
	} catch (std::exception &e) { 
		std::cout << "could not create socket" << std::endl;
		socket = NULL;
	}
	
	currentFrameTime = TuioTime::getSessionTime().getSeconds();
	currentFrame = sessionID = maxCursorID = -1;
	verbose = updateObject = updateCursor = false;
	lastObjectUpdate = lastCursorUpdate = currentFrameTime.getSeconds();
	
	sendEmptyCursorBundle();
	sendEmptyObjectBundle();

	periodic_update = false;
	full_update = false;
	connected = true;
}

TuioServer::~TuioServer() {
	connected = false;

	sendEmptyCursorBundle();
	sendEmptyObjectBundle();

	delete oscPacket;
	delete []oscBuffer;
	delete fullPacket;
	delete []fullBuffer;
	delete socket;
}


TuioObject* TuioServer::addTuioObject(int f_id, float x, float y, float a) {
	sessionID++;
	TuioObject *tobj = new TuioObject(currentFrameTime, sessionID, f_id, x, y, a);
	objectList.push_back(tobj);
	updateObject = true;

	if (verbose)
		std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;

	return tobj;
}

void TuioServer::addExternalTuioObject(TuioObject *tobj) {
	if (tobj==NULL) return;
	objectList.push_back(tobj);
	updateObject = true;
	
	if (verbose)
		std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
}

void TuioServer::updateTuioObject(TuioObject *tobj, float x, float y, float a) {
	if (tobj==NULL) return;
	if (tobj->getTuioTime()==currentFrameTime) return;
	tobj->update(currentFrameTime,x,y,a);
	updateObject = true;

	if (verbose && tobj->isMoving())		
		std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() 
		<< " " << tobj->getXSpeed() << " " << tobj->getYSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;	
}

void TuioServer::updateExternalTuioObject(TuioObject *tobj) {
	if (tobj==NULL) return;
	updateObject = true;
	if (verbose && tobj->isMoving())	
		std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() 
		<< " " << tobj->getXSpeed() << " " << tobj->getYSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;	
}

void TuioServer::removeTuioObject(TuioObject *tobj) {
	if (tobj==NULL) return;
	objectList.remove(tobj);
	delete tobj;
	updateObject = true;
	
	if (verbose)
		std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
}

void TuioServer::removeExternalTuioObject(TuioObject *tobj) {
	if (tobj==NULL) return;
	objectList.remove(tobj);
	updateObject = true;
	
	if (verbose)
		std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
}

TuioCursor* TuioServer::addTuioCursor(float x, float y) {
	sessionID++;
	
	int cursorID = (int)cursorList.size();
	if (((int)(cursorList.size())<=maxCursorID) && ((int)(freeCursorList.size())>0)) {
		std::list<TuioCursor*>::iterator closestCursor = freeCursorList.begin();
		
		for(std::list<TuioCursor*>::iterator iter = freeCursorList.begin();iter!= freeCursorList.end(); iter++) {
			if((*iter)->getDistance(x,y)<(*closestCursor)->getDistance(x,y)) closestCursor = iter;
		}
		
		TuioCursor *freeCursor = (*closestCursor);
		cursorID = (*closestCursor)->getCursorID();
		freeCursorList.erase(closestCursor);
		delete freeCursor;
	} else maxCursorID = cursorID;	
	
	TuioCursor *tcur = new TuioCursor(currentFrameTime, sessionID, cursorID, x, y);
	cursorList.push_back(tcur);
	updateCursor = true;

	if (verbose) 
		std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;

	return tcur;
}

void TuioServer::addExternalTuioCursor(TuioCursor *tcur) {
	if (tcur==NULL) return;
	cursorList.push_back(tcur);
	updateCursor = true;
	
	if (verbose) 
		std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;
}

void TuioServer::updateTuioCursor(TuioCursor *tcur,float x, float y) {
	if (tcur==NULL) return;
	if (tcur->getTuioTime()==currentFrameTime) return;
	tcur->update(currentFrameTime,x,y);
	updateCursor = true;

	if (verbose && tcur->isMoving())	 	
		std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
		<< " " << tcur->getXSpeed() << " " << tcur->getYSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
}

void TuioServer::updateExternalTuioCursor(TuioCursor *tcur) {
	if (tcur==NULL) return;
	updateCursor = true;
	if (verbose && tcur->isMoving())		
		std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
		<< " " << tcur->getXSpeed() << " " << tcur->getYSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
}

void TuioServer::removeTuioCursor(TuioCursor *tcur) {
	if (tcur==NULL) return;
	cursorList.remove(tcur);
	tcur->remove(currentFrameTime);
	updateCursor = true;

	if (verbose)
		std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;

	if (tcur->getCursorID()==maxCursorID) {
		maxCursorID = -1;
		delete tcur;
		
		if (cursorList.size()>0) {
			std::list<TuioCursor*>::iterator clist;
			for (clist=cursorList.begin(); clist != cursorList.end(); clist++) {
				int cursorID = (*clist)->getCursorID();
				if (cursorID>maxCursorID) maxCursorID=cursorID;
			}
			
			freeCursorBuffer.clear();
			for (std::list<TuioCursor*>::iterator flist=freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
				TuioCursor *freeCursor = (*flist);
				if (freeCursor->getCursorID()>maxCursorID) delete freeCursor;
				else freeCursorBuffer.push_back(freeCursor);
			}
			freeCursorList = freeCursorBuffer;
			
		} else {
			for (std::list<TuioCursor*>::iterator flist=freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
				TuioCursor *freeCursor = (*flist);
				delete freeCursor;
			}
			freeCursorList.clear();
		} 
	} else if (tcur->getCursorID()<maxCursorID) {
		freeCursorList.push_back(tcur);
	}
}

void TuioServer::removeExternalTuioCursor(TuioCursor *tcur) {
	if (tcur==NULL) return;
	cursorList.remove(tcur);
	updateCursor = true;
	
	if (verbose)
		std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

long TuioServer::getSessionID() {
	sessionID++;
	return sessionID;
}

long TuioServer::getFrameID() {
	return currentFrame;
}

TuioTime TuioServer::getFrameTime() {
	return currentFrameTime;
}

void TuioServer::initFrame(TuioTime ttime) {
	currentFrameTime = ttime;
	currentFrame++;
}

void TuioServer::commitFrame() {
	
	if(updateCursor) {
		startCursorBundle();
		for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
			
			// start a new packet if we exceed the packet capacity
			if ((oscPacket->Capacity()-oscPacket->Size())<CUR_MESSAGE_SIZE) {
				sendCursorBundle(currentFrame);
				startCursorBundle();
			}

			TuioCursor *tcur = (*tuioCursor);
			if ((full_update) || (tcur->getTuioTime()==currentFrameTime)) addCursorMessage(tcur);				
		}
		sendCursorBundle(currentFrame);
	} else if ((!periodic_update) && (lastCursorUpdate<currentFrameTime.getSeconds())) {
		lastCursorUpdate = currentFrameTime.getSeconds();
		startCursorBundle();
		sendCursorBundle(currentFrame);
	}
	updateCursor = false;
	
	if(updateObject) {
		startObjectBundle();
		for (std::list<TuioObject*>::iterator  tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
			
			// start a new packet if we exceed the packet capacity
			if ((oscPacket->Capacity()-oscPacket->Size())<OBJ_MESSAGE_SIZE) {
				sendObjectBundle(currentFrame);
				startObjectBundle();
			}
			
			TuioObject *tobj = (*tuioObject);
			if  ((full_update) || (tobj->getTuioTime()==currentFrameTime)) addObjectMessage(tobj);
		} 
		sendObjectBundle(currentFrame);
	} else if ((!periodic_update) && (lastObjectUpdate<currentFrameTime.getSeconds())) {
		lastObjectUpdate = currentFrameTime.getSeconds();
		startObjectBundle();
		sendObjectBundle(currentFrame);
	}
	updateObject = false;
}

void TuioServer::sendEmptyCursorBundle() {
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive" << osc::EndMessage;	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << -1 << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

void TuioServer::startCursorBundle() {	
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive";
	for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		(*oscPacket) << (int32)((*tuioCursor)->getSessionID());	
	}
	(*oscPacket) << osc::EndMessage;	
}

void TuioServer::addCursorMessage(TuioCursor *tcur) {

	 (*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "set";
	 (*oscPacket) << (int32)(tcur->getSessionID()) << tcur->getX() << tcur->getY();
	 (*oscPacket) << tcur->getXSpeed() << tcur->getYSpeed() << tcur->getMotionAccel();	
	 (*oscPacket) << osc::EndMessage;
}

void TuioServer::sendCursorBundle(long fseq) {
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << (int32)fseq << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

void TuioServer::sendEmptyObjectBundle() {
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive" << osc::EndMessage;	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << -1 << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

void TuioServer::startObjectBundle() {
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive";
	for (std::list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		(*oscPacket) << (int32)((*tuioObject)->getSessionID());	
	}
	(*oscPacket) << osc::EndMessage;	
}

void TuioServer::addObjectMessage(TuioObject *tobj) {
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "set";
	(*oscPacket) << (int32)(tobj->getSessionID()) << tobj->getSymbolID() << tobj->getX() << tobj->getY() << tobj->getAngle();
	(*oscPacket) << tobj->getXSpeed() << tobj->getYSpeed() << tobj->getRotationSpeed() << tobj->getMotionAccel() << tobj->getRotationAccel();	
	(*oscPacket) << osc::EndMessage;
}

void TuioServer::sendObjectBundle(long fseq) {
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << (int32)fseq << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

TuioObject* TuioServer::getTuioObject(long s_id) {
	for (std::list<TuioObject*>::iterator iter=objectList.begin(); iter != objectList.end(); iter++)
		if((*iter)->getSessionID()==s_id) return (*iter);
	
	return NULL;
}

TuioCursor* TuioServer::getTuioCursor(long s_id) {
	for (std::list<TuioCursor*>::iterator iter=cursorList.begin(); iter != cursorList.end(); iter++)
		if((*iter)->getSessionID()==s_id) return (*iter);
	
	return NULL;
}

TuioObject* TuioServer::getClosestTuioObject(float xp, float yp) {
	
	TuioObject *closestObject = NULL;
	float closestDistance = 1.0f;
	
	for (std::list<TuioObject*>::iterator iter=objectList.begin(); iter != objectList.end(); iter++) {
		float distance = (*iter)->getDistance(xp,yp);
		if(distance<closestDistance) {
			closestObject = (*iter);
			closestDistance = distance;
		}
	}
	
	return closestObject;
}

TuioCursor* TuioServer::getClosestTuioCursor(float xp, float yp) {

	TuioCursor *closestCursor = NULL;
	float closestDistance = 1.0f;

	for (std::list<TuioCursor*>::iterator iter=cursorList.begin(); iter != cursorList.end(); iter++) {
		float distance = (*iter)->getDistance(xp,yp);
		if(distance<closestDistance) {
			closestCursor = (*iter);
			closestDistance = distance;
		}
	}
	
	return closestCursor;
}

std::list<TuioObject*> TuioServer::getTuioObjects() {
	return objectList;
}

std::list<TuioCursor*> TuioServer::getTuioCursors() {
	return cursorList;
}

std::list<TuioObject*> TuioServer::getUntouchedObjects() {
	
	std::list<TuioObject*> untouched;
	for (std::list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		TuioObject *tobj = (*tuioObject);
		if (tobj->getTuioTime()!=currentFrameTime) untouched.push_back(tobj);
	}	
	return untouched;
}

void TuioServer::stopUntouchedMovingObjects() {
	
	std::list<TuioObject*> untouched;
	for (std::list<TuioObject*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		
		TuioObject *tobj = (*tuioObject);
		if ((tobj->getTuioTime()!=currentFrameTime) && (tobj->isMoving())) {
			tobj->stop(currentFrameTime);
			updateObject = true;
			if (verbose)		
				std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() 
				<< " " << tobj->getXSpeed() << " " << tobj->getYSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
		}
	}
}

void TuioServer::removeUntouchedStoppedObjects() {
	
	std::list<TuioObject*>::iterator tuioObject = objectList.begin();
	while (tuioObject!=objectList.end()) {
		TuioObject *tobj = (*tuioObject);
		if ((tobj->getTuioTime()!=currentFrameTime) && (!tobj->isMoving())) {
			removeTuioObject(tobj);
			tuioObject = objectList.begin();
		} else tuioObject++;
	}
}


std::list<TuioCursor*> TuioServer::getUntouchedCursors() {
	
	std::list<TuioCursor*> untouched;
	for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		TuioCursor *tcur = (*tuioCursor);
		if (tcur->getTuioTime()!=currentFrameTime) untouched.push_back(tcur);
	}	
	return untouched;
}

void TuioServer::stopUntouchedMovingCursors() {
	
	std::list<TuioCursor*> untouched;
	for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		TuioCursor *tcur = (*tuioCursor);
		if ((tcur->getTuioTime()!=currentFrameTime) && (tcur->isMoving())) {
			tcur->stop(currentFrameTime);
			updateCursor = true;
			if (verbose) 	
				std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
				<< " " << tcur->getXSpeed() << " " << tcur->getYSpeed()<< " " << tcur->getMotionAccel() << " " << std::endl;							
		}
	}	
}

void TuioServer::removeUntouchedStoppedCursors() {
	
	if (cursorList.size()==0) return;
	std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin();
	while (tuioCursor!=cursorList.end()) {
		TuioCursor *tcur = (*tuioCursor);
		if ((tcur->getTuioTime()!=currentFrameTime) && (!tcur->isMoving())) {
			removeTuioCursor(tcur);
			tuioCursor = cursorList.begin();
		} else tuioCursor++;
	}	
}
