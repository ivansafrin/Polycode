/*
 *  PolyServer.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyServer.h"

using namespace Polycode;

ServerClient::ServerClient() {
	
}

ServerClient::~ServerClient() {
	
}

void ServerClient::handlePacket(Packet *packet) {
	ServerClientEvent *event = new ServerClientEvent();	
	event->data = packet->data;
	event->dataSize = packet->header.size;
	event->dataType = packet->header.type;	
	dispatchEvent(event, ServerClientEvent::EVENT_CLIENT_DATA);	
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
		world->updateWorld(rateTimer->getElapsedf());		
		for(int i=0; i < clients.size(); i++) {
			client = clients[i];
			unsigned int worldDataSize;
			char *worldData;
			world->getWorldState(client, &worldData, &worldDataSize);			
			sendData(client->connection->address, (char*)worldData, worldDataSize, PACKET_TYPE_USERDATA);			
		}
	}	
	
	Peer::handleEvent(event);
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
	sendReliableData(newClient->connection->address, (char*)&clientID, sizeof(unsigned short), PACKET_TYPE_SETCLIENT_ID);

}

void Server::handlePacket(Packet *packet, PeerConnection *connection) {
	ServerClient *client = getConnectedClient(connection);
	if(packet->header.type == PACKET_TYPE_CLIENT_READY && client) {
		ServerEvent *event = new ServerEvent();
		event->client = client;
		dispatchEvent(event, ServerEvent::EVENT_CLIENT_CONNECTED);		
	} else {
		if(client != NULL) {
			client->handlePacket(packet);
		} else {
		}
	}
}