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

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyClient.h"
#include <string.h>

using namespace Polycode;

Client::Client(Core *core, unsigned int port, int rate) : Peer(core, port) {
	connected = false;
	clientID = -1;
}

Client::~Client() {
	
}

void Client::sendClientData(char *data, uint32_t datasize) {
	if(connected) {
		sendData(serverAddress, (char*)data, dataSize, PACKET_TYPE_CLIENT_DATA);
	}
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
				sendReliableData(serverAddress, (char*)&clientID, sizeof(unsigned short), PACKET_TYPE_CLIENT_READY);
				dispatchEvent(newEvent, ClientEvent::EVENT_CLIENT_READY);				
			} break;
			case PACKET_TYPE_DISONNECT:
			{
				ClientEvent *newEvent = new ClientEvent();
				dispatchEvent(newEvent, ClientEvent::EVENT_SERVER_DISCONNECTED);
				connected = false;
			}
			break;
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

void Client::Connect(std::string ipAddress, unsigned int port) {
	serverAddress.setAddress(ipAddress, port);
	connected = true;		
}

void Client::Disconnect() {
	sendReliableData(serverAddress, (char*)&clientID, sizeof(unsigned short), PACKET_TYPE_DISONNECT);
}

