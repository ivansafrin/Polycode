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
		
		static const int EVENTBASE_CLIENTEVENT = 0x600;
		static const int EVENT_SERVER_DATA = EVENTBASE_CLIENTEVENT+0;
		static const int EVENT_CLIENT_READY = EVENTBASE_CLIENTEVENT+1;
		static const int EVENT_SERVER_DISCONNECTED = EVENTBASE_CLIENTEVENT+2;
	};		
	
	class _PolyExport Client : public Peer {
	public:
		Client(unsigned int port, int rate);
		~Client();
		
		void updatePeer();
		void Connect(std::string ipAddress, unsigned int port);
		void Disconnect();
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
