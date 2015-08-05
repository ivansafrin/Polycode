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
		
		ServerClient *client;
		
		static const int EVENTBASE_SERVERCLIENTEVENT = 0x780;
		static const int EVENT_CLIENT_DATA = EVENTBASE_SERVERCLIENTEVENT+0;
	};
	
	class _PolyExport ServerClient : public EventDispatcher {
	public:
		ServerClient();
		~ServerClient();
		
		ServerClientEvent *handlePacket(Packet *packet);
		
		unsigned int    clientID;
		PeerConnection *connection;
        bool clientReady;
	};
		
	class _PolyExport ServerEvent : public Event {
	public:
		ServerEvent(){client = NULL; }
		~ServerEvent(){}
		
		ServerClient *client;
		
		char *data;
		unsigned int dataSize;
		unsigned short dataType;		
		
		static const int EVENTBASE_SERVEREVENT = 0x700;
		static const int EVENT_CLIENT_CONNECTED = EVENTBASE_SERVEREVENT+0;
		static const int EVENT_CLIENT_DATA = EVENTBASE_SERVEREVENT+1;
		static const int EVENT_CLIENT_DISCONNECTED = EVENTBASE_SERVEREVENT+2;
		// Notice also the SERVERCLIENTEVENT above, which starts with 0x780.
	};

	/** 
	* A network server, accepting incoming connections and keeping track of connected clients.
	*
	* As the Peer class already provides all connectivity functionality required, the Server class
	* merely provides another abstraction layer to treat clients separately from mere connections.
	*
	* The Server will send the data provided by the ServerWorld class to all clients at defined rate and dispatch events when clients connect, disconnect and send data.
	*/
	class _PolyExport Server : public Peer {
		public:
			/**
			* Constructor.
			* @param port The local port to listen for client connections on.
			* @param rate How many times per second to send out server data to clients.
			* @param world An instance of the server data provider. @see ServerWorld
			*/
			Server(unsigned int port, unsigned int rate, ServerWorld *world = NULL);
			~Server();
		
			void handlePacket(Packet *packet, PeerConnection *connection);
			void handleEvent(Event *event);	
			void handlePeerConnection(PeerConnection *connection);
			void DisconnectClient(ServerClient *client);

			/**
			* Get a connected client from its associated peer connection, if any.
			* @param connection The PeerConnection through which we're communicating 
			*                   with the client to obtain.
			* @return The connected client or NULL if doesn't exist.
			*/
			ServerClient *getConnectedClient(PeerConnection *connection);
		
			int getNumServerClients();
			
			ServerClient *getServerClient(int index);
			
			/**
			* @see Peer::sendReliableData
			*/
			void sendReliableDataToClient(ServerClient *client, char *data, unsigned int size, unsigned short type);

			/**
			* @see Peer::sendReliableDataToAll
			*/
			void sendReliableDataToAllClients(char *data, unsigned int size, unsigned short type);
		
	protected:
		
		Timer *rateTimer;
		ServerWorld *world;
		vector<ServerClient*> clients;
	};
}
