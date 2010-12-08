/*
 *  PolyClient.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// @package Network

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyPeer.h"
#include "PolyTimer.h"
#include "PolyEvent.h"

namespace Polycode {
	
	typedef struct {
		char dummy;
	} DummyData;
	
	class _PolyExport ClientEvent : public Event {
	public:
		ClientEvent(){}
		~ClientEvent(){}

		char data[MAX_PACKET_SIZE];
		unsigned int dataSize;
		unsigned short dataType;
				
		static const int EVENT_SERVER_DATA = 0;
		static const int EVENT_CLIENT_READY = 1;		
	};		
	
	class _PolyExport Client : public Peer {
	public:
		Client(unsigned int port, int rate);
		~Client();
		
		void updatePeer();
		void connect(string ipAddress, unsigned int port);		
		void setPersistentData(void *data, unsigned int size);
		
		unsigned int getClientID();
		
		void sendReliableDataToServer(char *data, unsigned int size, unsigned short type);
		
		void handlePacket(Packet *packet, PeerConnection *connection);
		
		void handleEvent(Event *event);
	private:
		
		int clientID;
		
		void *data;
		unsigned int dataSize;
		Timer *rateTimer;
		Address serverAddress;
		bool connected;
	};
}