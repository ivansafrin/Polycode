/*
 *  PolyPeer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
// @package Network

#pragma once

#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyThreaded.h"
#include "PolySocket.h"

#include <vector>

using std::vector;

namespace Polycode {	
	
	typedef struct {
		unsigned int headerHash;
		unsigned int sequence;
		unsigned int ack;
		unsigned short reliableID;
		unsigned int ackBitfield;
		unsigned short size;
		unsigned short type;
	} PacketHeader;
	
	typedef struct {
		PacketHeader header;
		char data[MAX_PACKET_SIZE];
	} Packet;
	
	typedef struct {
		Packet *packet;
		unsigned int timestamp;
	} SentPacketEntry; 
	
	class _PolyExport PeerConnection {
	public:
		PeerConnection() { localSequence = 0; remoteSequence = 0; reliableID = 1;}
		~PeerConnection(){}
		
		void ackPackets(unsigned int ack);
		
		unsigned int localSequence;
		unsigned int remoteSequence;
		unsigned int reliableID;
		
		vector<SentPacketEntry> reliablePacketQueue;
		vector<unsigned short> recentReliableIDs;
		Address address;
	};
		
	class _PolyExport Peer : public Threaded, public EventDispatcher {
		public:
			Peer(unsigned int port);
			~Peer();
		
			void handleEvent(Event *event);

			virtual void handlePacket(Packet *packet, PeerConnection *connection){};
			virtual void handlePeerConnection(PeerConnection *connection){};
		
			Packet *createPacket(const Address &target, char *data, unsigned int size, unsigned short type);

			void sendData(const Address &target, char *data, unsigned int size, unsigned short type);
			void sendReliableData(const Address &target, char *data, unsigned int size, unsigned short type);
			void sendReliableDataToAll(char *data, unsigned int size, unsigned short type);
			void sendDataToAll(char *data, unsigned int size, unsigned short type);		
		
			void sendPacket(const Address &target, Packet *packet);
		
			bool checkPacketAcks(PeerConnection *connection, Packet *packet);
		
			PeerConnection *getPeerConnection(const Address &address);
			PeerConnection *addPeerConnection(const Address &address);
		
			virtual void updatePeer(){}
			void updateThread();
		
		protected:
		
			Timer *updateTimer;
			vector<PeerConnection*> peerConnections;		
			Socket *socket;
	};

}