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

#include "PolyServer.h"
#include "PolyTimer.h"
#include "PolyLogger.h"

using namespace Polycode;
using std::vector;

ServerClient::ServerClient() {
    clientReady	= false;
}

ServerClient::~ServerClient() {
	
}

ServerClientEvent *ServerClient::handlePacket(Packet *packet) {
	ServerClientEvent *event = new ServerClientEvent();	
	event->data = packet->data;
	event->dataSize = packet->header.size;
	event->dataType = packet->header.type;
	event->client = this;
	dispatchEvent(event, ServerClientEvent::EVENT_CLIENT_DATA);	
	return event;
}

Server::Server(unsigned int port,  unsigned int rate, ServerWorld *world) : Peer(port) {
	this->world = world;
	rateTimer = new Timer(true, 1000/rate);
	rateTimer->addEventListener(this, Timer::EVENT_TRIGGER);	
}

Server::~Server() {
}

ServerClient *Server::getConnectedClient(PeerConnection *connection) {
	ServerClient *client;
	for(int i=0; i < clients.size(); i++) {
		client = clients[i];
		if(client->connection == connection) {
			return client;
		}
	}
	return NULL;
}

void Server::handleEvent(Event *event) {
	
	ServerClient *client;		
	if(event->getDispatcher() == rateTimer) {
		if(world) {
			world->updateWorld(rateTimer->getElapsedf());		
			for(int i=0; i < clients.size(); i++) {
				client = clients[i];
				unsigned int worldDataSize;
				char *worldData;
				world->getWorldState(client, &worldData, &worldDataSize);			
				sendData(client->connection->address, (char*)worldData, worldDataSize, PACKET_TYPE_SERVER_DATA);			
			}
		} else {
			for(int i=0; i < clients.size(); i++) {
				client = clients[i];
				sendData(client->connection->address, 0, 0, PACKET_TYPE_SERVER_DATA);			
			}
		}
	}	
	
	Peer::handleEvent(event);
}

void Server::sendReliableDataToAllClients(char *data, unsigned int size, unsigned short type) {
	for(unsigned int i=0; i < clients.size(); i++) {
		sendReliableDataToClient(clients[i], data, size, type);
	}
}

void Server::sendReliableDataToClient(ServerClient *client, char *data, unsigned int size, unsigned short type) {
	sendReliableData(client->connection->address, data, size, type);	
}

void Server::handlePeerConnection(PeerConnection *connection) {
	ServerClient *newClient = new ServerClient();
	newClient->connection = connection;
	newClient->clientID = clients.size();
	clients.push_back(newClient);	

	unsigned short clientID = newClient->clientID;
    printf("SENDING PACKET_TYPE_SETCLIENT_ID\n");
	sendReliableData(newClient->connection->address, (char*)&clientID, sizeof(unsigned short), PACKET_TYPE_SETCLIENT_ID);

}

int Server::getNumServerClients() {
	return clients.size();
}

ServerClient *Server::getServerClient(int index) {
	if(index >= 0 && index < clients.size()) {
		return clients[index];
	} else {
		return NULL;
	}
}	

void Server::DisconnectClient(ServerClient *client) {
	sendReliableDataToClient(client, NULL, 0, PACKET_TYPE_DISONNECT);

	for(unsigned int i=0;i<clients.size();i++) {
		if(clients[i] == client) {			
			clients.erase(clients.begin()+i);
		}
	}
	ServerEvent *event = new ServerEvent();
	event->client = client;
	dispatchEvent(event, ServerEvent::EVENT_CLIENT_DISCONNECTED);
	removePeerConnection(client->connection);
	delete client;
}

void Server::handlePacket(Packet *packet, PeerConnection *connection) {
	ServerClient *client = getConnectedClient(connection);
	if(!client) {
		Logger::log("Packet from unknown client!\n");
		return;
	}

	switch (packet->header.type) {
		case PACKET_TYPE_CLIENT_READY:
		{
            if(!client->clientReady) {
                client->clientReady = true;
                ServerEvent *event = new ServerEvent();
                event->client = client;
                dispatchEvent(event, ServerEvent::EVENT_CLIENT_CONNECTED);
            }
		}
		break;
		case PACKET_TYPE_DISONNECT:
		{
			DisconnectClient(client);
		}
		break;		
		default:
		{
			client->handlePacket(packet);
			ServerEvent *serverEvent = new ServerEvent();
			serverEvent->client = client;
			serverEvent->data = packet->data;
			serverEvent->dataSize = packet->header.size;
			serverEvent->dataType = packet->header.type;
			dispatchEvent(serverEvent, ServerEvent::EVENT_CLIENT_DATA);
		}
		break;
	}
}
