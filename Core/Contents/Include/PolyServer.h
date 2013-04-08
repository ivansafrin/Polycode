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
		
		static const int EVENTBASE_SERVERCLIENTEVENT = 0x780;
		static const int EVENT_CLIENT_DATA = EVENTBASE_SERVERCLIENTEVENT+0;
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
		
		static const int EVENTBASE_SERVEREVENT = 0x700;
		static const int EVENT_CLIENT_CONNECTED = EVENTBASE_SERVEREVENT+0;
		static const int EVENT_CLIENT_DATA = EVENTBASE_SERVEREVENT+1;
		static const int EVENT_CLIENT_DISCONNECTED = EVENTBASE_SERVEREVENT+2;
		// Notice also the SERVERCLIENTEVENT above, which starts with 0x780.
	};

	class _PolyExport Server : public Peer {
		public:
			Server(unsigned int port, unsigned int rate, ServerWorld *world = NULL);
			~Server();
		
			void DisconnectClient(ServerClient *client);
			void handleEvent(Event *event);		
			void handlePeerConnection(PeerConnection *connection);
			ServerClient *getConnectedClient(PeerConnection *connection);
		
			void sendReliableDataToClient(ServerClient *client, char *data, unsigned int size, unsigned short type);
			void sendReliableDataToAllClients(char *data, unsigned int size, unsigned short type);
					
			void handlePacket(Packet *packet, PeerConnection *connection);
		
	protected:
		
		Timer *rateTimer;
		ServerWorld *world;
		vector<ServerClient*> clients;
	};
}
