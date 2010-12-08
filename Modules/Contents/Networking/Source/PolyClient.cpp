/*
 *  PolyClient.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyClient.h"

using namespace Polycode;

Client::Client(unsigned int port, int rate) : Peer(port) {
	rateTimer = new Timer(true, 1000/rate);
	rateTimer->addEventListener(this, Timer::EVENT_TRIGGER);
	connected = false;
	DummyData *dummy = new DummyData;
	dummy->dummy = 30;	
	clientID = -1;	
	setPersistentData((void*)dummy, sizeof(DummyData));
}

Client::~Client() {
}

void Client::handleEvent(Event *event) {
	if(connected) {		
		if(event->getDispatcher() == rateTimer) {	
			sendData(serverAddress, (char*)data, dataSize, PACKET_TYPE_CLIENT_DATA);
		}
	}
	Peer::handleEvent(event);
}

unsigned int Client::getClientID() {
	return clientID;
}

void Client::sendReliableDataToServer(char *data, unsigned int size, unsigned short type) {
	sendReliableData(serverAddress, data, size, type);
}

void Client::handlePacket(Packet *packet, PeerConnection *connection) {
	if(connection->address == serverAddress) {
		switch(packet->header.type) {
			case PACKET_TYPE_SETCLIENT_ID: {
				clientID = (unsigned short)*packet->data;
				ClientEvent *newEvent = new ClientEvent();
				dispatchEvent(newEvent, ClientEvent::EVENT_CLIENT_READY);
				sendReliableData(serverAddress, (char*)&clientID, sizeof(unsigned short), PACKET_TYPE_CLIENT_READY);
			} break;
			default: {
				ClientEvent *newEvent = new ClientEvent();
				newEvent->dataSize = packet->header.size;
				newEvent->dataType = packet->header.type;
				memcpy(newEvent->data, packet->data, newEvent->dataSize);
				dispatchEvent(newEvent, ClientEvent::EVENT_SERVER_DATA);				
			}
			break;
		}
	}
}

void Client::setPersistentData(void *data, unsigned int size) {
	this->data = data;
	dataSize = size;
}

void Client::connect(string ipAddress, unsigned int port) {
	serverAddress.setAddress(ipAddress, port);
	connected = true;	
}

void Client::updatePeer() {
	
}
