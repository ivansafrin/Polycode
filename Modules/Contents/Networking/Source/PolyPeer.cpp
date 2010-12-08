/*
 *  PolyPeer.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyPeer.h"

using namespace Polycode;

void PeerConnection::ackPackets(unsigned int ack) {
	for(int i=0; i < reliablePacketQueue.size(); i++) {
		if(reliablePacketQueue[i].packet->header.sequence == ack) {
			delete reliablePacketQueue[i].packet;
			reliablePacketQueue.erase(reliablePacketQueue.begin()+i);
		}
	}
}

Peer::Peer(unsigned int port) : EventDispatcher(), Threaded() {
	socket = new Socket(port);
	socket->addEventListener(this, SocketEvent::EVENT_DATA_RECEIVED);

#if USE_THREADED_SOCKETS == 1
	CoreServices::getInstance()->getCore()->createThread(this);
	updateTimer = NULL;
#else
	updateTimer = new Timer(true, SOCKET_POLL_INTERVAL);
	updateTimer->addEventListener(this, Timer::EVENT_TRIGGER);
#endif

}

Peer::~Peer() {
	delete socket;
}

PeerConnection *Peer::getPeerConnection(const Address &address) {
	for(int i=0; i < peerConnections.size(); i++) {
		if(peerConnections[i]->address == address) {
			return peerConnections[i];
		}
	}
	return NULL;
}

PeerConnection *Peer::addPeerConnection(const Address &address) {
	PeerConnection *newConnection = new PeerConnection();
	newConnection->address = address;
	peerConnections.push_back(newConnection);
	handlePeerConnection(newConnection);
	return newConnection;
}

Packet *Peer::createPacket(const Address &target, char *data, unsigned int size, unsigned short type) {	
	PeerConnection *connection = getPeerConnection(target);
	if(!connection)
		connection = addPeerConnection(target);
	Packet *packet = new Packet();
	packet->header.sequence = connection->localSequence;
	packet->header.headerHash = 20;
	packet->header.reliableID = 0;	
	packet->header.ack = connection->remoteSequence;
	packet->header.ackBitfield = 0;
	packet->header.size = size;	
	packet->header.type = type;
	if(size > 0)
		memcpy(packet->data, data, size);	
	connection->localSequence++;	
	return packet;	
}

void Peer::sendReliableData(const Address &target, char *data, unsigned int size, unsigned short type) {	
	PeerConnection *connection = getPeerConnection(target);	
	Packet *packet = createPacket(target, data, size, type);
	packet->header.reliableID = connection->reliableID;
	connection->reliableID++;
	sendPacket(target, packet);	
	
	SentPacketEntry entry;
	entry.packet = packet;
	entry.timestamp = CoreServices::getInstance()->getCore()->getTicks();
	connection->reliablePacketQueue.push_back(entry);
}

void Peer::sendDataToAll(char *data, unsigned int size, unsigned short type) {
	for(int i=0; i < peerConnections.size(); i++) {
		sendData(peerConnections[i]->address, data, size, type);
	}	
}

void Peer::sendReliableDataToAll(char *data, unsigned int size, unsigned short type) {
	for(int i=0; i < peerConnections.size(); i++) {
		sendReliableData(peerConnections[i]->address, data, size, type);
	}
}

void Peer::sendData(const Address &target, char *data, unsigned int size, unsigned short type) {
	Packet *packet = createPacket(target, data, size, type);
	sendPacket(target, packet);
	delete packet;
}

void Peer::sendPacket(const Address &target, Packet *packet) {
	unsigned int packetSize = packet->header.size + sizeof(packet->header);	
	socket->sendData(target, (char*)packet, packetSize);	
}

bool Peer::checkPacketAcks(PeerConnection *connection, Packet *packet) {
	bool retVal = true;
	if(packet->header.sequence > connection->remoteSequence)
		connection->remoteSequence = packet->header.sequence;
	else // ignore old packets
		retVal = false;
	
	// if this is a reliable packet, check if it was recently received	
	if(packet->header.reliableID != 0) {
		retVal = true;
		for(int i=0; i < connection->recentReliableIDs.size(); i++) {
			if(connection->recentReliableIDs[i] == packet->header.reliableID)
				retVal = false;
		}
		
		// if still good, push the id into recent reliable acks
		if(retVal) {
			connection->recentReliableIDs.push_back(packet->header.reliableID);
			if(connection->recentReliableIDs.size() > 50)
				connection->recentReliableIDs.erase(connection->recentReliableIDs.begin());
		}		
	}
	
	for(int i=0; i < peerConnections.size(); i++) {
		peerConnections[i]->ackPackets(packet->header.ack);
	}
	
	return retVal;
}

void Peer::handleEvent(Event *event) {
	if(event->getDispatcher() == socket) {
		SocketEvent *socketEvent = (SocketEvent*) event;
		switch(socketEvent->getEventCode()) {
			case SocketEvent::EVENT_DATA_RECEIVED:
				PeerConnection *connection = getPeerConnection(socketEvent->fromAddress);
				if(!connection)
					connection = addPeerConnection(socketEvent->fromAddress);				
				if(checkPacketAcks(connection, (Packet*)socketEvent->data))
					handlePacket((Packet*)socketEvent->data, connection);
			break;
		}
	} else if(event->getDispatcher() == updateTimer) {
		updateThread();
	}
}

void Peer::updateThread() {
	for(int i=0; i < peerConnections.size(); i++) {
		for(int j=0; j < peerConnections[i]->reliablePacketQueue.size(); j++) {
			if(peerConnections[i]->reliablePacketQueue[j].timestamp < CoreServices::getInstance()->getCore()->getTicks() - 1000) {
				peerConnections[i]->reliablePacketQueue[j].timestamp = CoreServices::getInstance()->getCore()->getTicks(); 
				sendPacket(peerConnections[i]->address, peerConnections[i]->reliablePacketQueue[j].packet);
			}
		}
	}

	int received = 1;
	while( received > 0) {
		received = socket->receiveData();
	}
}
