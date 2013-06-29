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

#pragma once

#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyThreaded.h"
#include "PolySocket.h"

#include <vector>


namespace Polycode {

class Timer;

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
		
		std::vector<SentPacketEntry> reliablePacketQueue;
		std::vector<unsigned short> recentReliableIDs;
		Address address;
};

/** 
* A network actor that can send and receive data.
*
* Peers are comparable to UDP sockets, but with extended functionality
* to optionally allow for some of TCP's features(ordering, reliability).
*
* WARNING: Reliability(packets being resent on loss) is currently not
* implemented, but is planned.
*
* @see PeerConnection
*/
#if USE_THREADED_SOCKETS == 1

class _PolyExport Peer : public Threaded {

#else

class _PolyExport Peer : public EventDispatcher {

#endif
	public:
		/**
		* Create a peer. The peer will immediately start listening on the given 
		* port and accept incoming packets.
		*
		* @param port The UDP port to listen for packets. Can not be omitted,
		*             this will be the actual port this peer will use to send
		*             and receive packets.
		*/
		Peer(unsigned int port);
		~Peer();

		void handleEvent(Event *event);

		virtual void handlePacket(Packet *packet, PeerConnection *connection){};
		virtual void handlePeerConnection(PeerConnection *connection){};

		Packet *createPacket(const Address &target, char *data, unsigned int size, unsigned short type);

		/**
		* Send raw binary data to the target address.
		*
		* @param target The network Address to send the data to.
		* @param data The binary data to send as a C byte array. Length must be supplied by size parameter.
		* @param size The size in bytes of the sent binary data.
		* @param type A number representing the packet type, used to define the purpose of the packet.
		*/
		void sendData(const Address &target, char *data, unsigned int size, unsigned short type);

		/**
		* Send raw binary data to the target address, making sure it arrives in the right order.
		*
		* @param target The network address to send the data to.
		* @param data The binary data to send as a C byte array. Length must be supplied by size parameter.
		* @param size The size in bytes of the sent binary data.
		* @param type A number representing the packet type, used to define the purpose of the packet.
		*/
		void sendReliableData(const Address &target, char *data, unsigned int size, unsigned short type);

		/**
		* Broadcast raw binary data to all connected peers, making sure it arrives in the right order.
		*
		* @param data The binary data to send as a C byte array. Length must be supplied by size parameter.
		* @param size The size in bytes of the sent binary data.
		* @param type A number representing the packet type, used to define the purpose of the packet.
		*/
		void sendReliableDataToAll(char *data, unsigned int size, unsigned short type);

		/**
		* Broadcast raw binary data to all connected peers.
		*
		* @param data The binary data to send as a C byte array. Length must be supplied by size parameter.
		* @param size The size in bytes of the sent binary data.
		* @param type A number representing the packet type, used to define the purpose of the packet.
		*/
		void sendDataToAll(char *data, unsigned int size, unsigned short type);

		void sendPacket(const Address &target, Packet *packet);

		bool checkPacketAcks(PeerConnection *connection, Packet *packet);

		PeerConnection *getPeerConnection(const Address &address);
		PeerConnection *addPeerConnection(const Address &address);
		void removePeerConnection(PeerConnection* connection);

		void updateReliableDataQueue();

		virtual void updatePeer(){}
		void updateThread();

	protected:

		Timer *updateTimer;
		std::vector<PeerConnection*> peerConnections;
		Socket *socket;
};

}
