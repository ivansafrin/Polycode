/*
 *  PolyServer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// @package Network

#pragma once

#include "PolyGlobals.h"
#include "PolyPeer.h"
#include "PolyEvent.h"
#include "PolyServerWorld.h"
#include <vector>

using std::vector;

namespace Polycode {

	class _PolyExport ServerClientEvent : public Event {
	public:
		ServerClientEvent() {}
		~ServerClientEvent() {}
		
		char *data;
		unsigned int dataSize;
		unsigned short dataType;
		
		static const int EVENT_CLIENT_DATA = 0;
	};
	
	class _PolyExport ServerClient : public EventDispatcher {
	public:
		ServerClient();
		~ServerClient();
		
		void handlePacket(Packet *packet);
		
		unsigned int clientID;
		PeerConnection *connection;
	};
		
	class _PolyExport ServerEvent : public Event {
	public:
		ServerEvent(){client = NULL; }
		~ServerEvent(){}
		
		ServerClient *client;
		
		static const int EVENT_CLIENT_CONNECTED = 0;
		static const int EVENT_CLIENT_DATA = 1;
	};

	class _PolyExport Server : public Peer {
		public:
			Server(unsigned int port, unsigned int rate, ServerWorld *world);
			~Server();
		
			void handleEvent(Event *event);		
			void handlePeerConnection(PeerConnection *connection);
			ServerClient *getConnectedClient(PeerConnection *connection);
		
			void sendReliableDataToClient(ServerClient *client, char *data, unsigned int size, unsigned short type);
		
			void handlePacket(Packet *packet, PeerConnection *connection);
		
	protected:
		
		Timer *rateTimer;
		ServerWorld *world;
		vector<ServerClient*> clients;
	};
}