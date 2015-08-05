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

#include "PolyPeer.h"
#include <string.h>
#include "PolyCore.h"
#include "PolyTimer.h"

using namespace Polycode;

PeerConnection::PeerConnection() {
	localSequence = 0;
	remoteSequence = 0;
	receivedPacketQueue.resize(32, 0);
}

PeerConnection::~PeerConnection() {

}

void PeerConnection::ackPackets(unsigned int ack) {	
	std::vector<SentPacketEntry>::iterator it;	
	for(it = reliablePacketQueue.begin(); it != reliablePacketQueue.end();) {
		if((*it).packet->header.sequence == ack) {
			delete (*it).packet;
			it = reliablePacketQueue.erase(it);
		} else {
			++it;
		}
	}
}

void PeerConnection::ackPacketsWithBitfield(unsigned int ack, unsigned int ackBitfield) {

	if(reliablePacketQueue.size() == 0) {
		return;
	}
	
	for(int i=0; i <32; i++) {
		if(ackBitfield & (1<<i)) {
			ackPackets(ack-i);
		}
	}
}

#if USE_THREADED_SOCKETS == 1
	Peer::Peer(unsigned int port) : Threaded() {
#else
	Peer::Peer(unsigned int port) : EventDispatcher() {
#endif
	socket = new Socket(port);
	socket->addEventListener(this, SocketEvent::EVENT_DATA_RECEIVED);

#if USE_THREADED_SOCKETS == 1
	CoreServices::getInstance()->getCore()->createThread(this);
	updateTimer = NULL;
#else
	updateTimer = new Timer(true, SOCKET_POLL_INTERVAL);
	updateTimer->addEventListener(this, Timer::EVENT_TRIGGER);
#endif

	reliableRetransmissionInverval = 1000;
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

void Peer::removePeerConnection(PeerConnection* connection) {
	for(unsigned int i=0;i<peerConnections.size();i++) {
		if(peerConnections[i] == connection) {			
			peerConnections.erase(peerConnections.begin()+i);
		}
	}
}

void Peer::setReliableRetransmissionInterval(int interval) {
	reliableRetransmissionInverval = interval;
}

Packet *Peer::createPacket(const Address &target, char *data, unsigned int size, unsigned short type) {	
	PeerConnection *connection = getPeerConnection(target);
	if(!connection)
		connection = addPeerConnection(target);
	Packet *packet = new Packet();
	packet->header.sequence = connection->localSequence;
	packet->header.headerHash = 20;
	packet->header.ack = connection->remoteSequence;
	packet->header.ackBitfield = 0;
			
	for(int i=0; i < 32; i++) {
		if(connection->receivedPacketQueue[31-i] == connection->remoteSequence-i) {
			packet->header.ackBitfield = (packet->header.ackBitfield & ~(1 << i)) | (1 << i);
		} else {
			packet->header.ackBitfield = (packet->header.ackBitfield & ~(1 << i)) | (0 << i);		
		}
	}

	int sizeToCopy = size;
	if(size > MAX_PACKET_SIZE) {
		size = MAX_PACKET_SIZE; 
	}
	
	packet->header.size = sizeToCopy;	
	packet->header.type = type;
	
	
	if(size > 0)
		memcpy(packet->data, data, size);	
	connection->localSequence++;	
	return packet;	
}

void Peer::sendReliableData(const Address &target, char *data, unsigned int size, unsigned short type) {	
	PeerConnection *connection = getPeerConnection(target);	
	if(!connection)
		connection = addPeerConnection(target);	
	Packet *packet = createPacket(target, data, size, type);	
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
	if(packet->header.sequence > connection->remoteSequence || connection->remoteSequence == 0) {
		connection->remoteSequence = packet->header.sequence;
	} else {
		return false;
	}
	
	connection->receivedPacketQueue.push_back(packet->header.sequence);	
	connection->receivedPacketQueue.pop_front();
	
	connection->ackPacketsWithBitfield(packet->header.ack, packet->header.ackBitfield);	
	return true;
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

void Peer::updateReliableDataQueue() {
	for(int i=0; i < peerConnections.size(); i++) {
		for(int j=0; j < peerConnections[i]->reliablePacketQueue.size(); j++) {		
			if(peerConnections[i]->reliablePacketQueue[j].timestamp < CoreServices::getInstance()->getCore()->getTicks() - reliableRetransmissionInverval) {
				peerConnections[i]->reliablePacketQueue[j].timestamp = CoreServices::getInstance()->getCore()->getTicks(); 
				
				Packet *oldPacket = peerConnections[i]->reliablePacketQueue[j].packet;
				peerConnections[i]->reliablePacketQueue[j].packet = createPacket(peerConnections[i]->address, oldPacket->data, oldPacket->header.size, oldPacket->header.type);
				delete oldPacket;
				
				sendPacket(peerConnections[i]->address, peerConnections[i]->reliablePacketQueue[j].packet);
			}
		}
	}
}

void Peer::updateThread() {
	updateReliableDataQueue();
	
	int received = 1;
	while( received > 0) {
		received = socket->receiveData();
	}
}
