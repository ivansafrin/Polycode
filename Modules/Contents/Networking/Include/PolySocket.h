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
#include "PolyEvent.h"
#include "stdio.h"


#define MAX_PACKET_SIZE 1400

// if set to 1, will create a thread for each network socket
#define USE_THREADED_SOCKETS 0

// Socket poll interval time in msecs
#define SOCKET_POLL_INTERVAL 5

#define PACKET_TYPE_USERDATA 0
#define PACKET_TYPE_SETCLIENT_ID 1
#define PACKET_TYPE_CLIENT_READY 2
#define PACKET_TYPE_DISONNECT 3
#define PACKET_TYPE_CLIENT_DATA 4
#define PACKET_TYPE_SERVER_DATA 5

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#endif

#include "PolyEventDispatcher.h"

#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

namespace Polycode {
		
	class _PolyExport Address  {
		public:
		Address(String ipAsString, unsigned int port);
		Address(unsigned int ip, unsigned int port);
		Address();
		~Address();
		
		inline void operator = (const Address &add2) {
			setAddress(add2.uintAddress, add2.port);
		}
		
		inline bool operator == ( const Address& add2)  {
			return (uintAddress == add2.uintAddress && port == add2.port);
		}
			
		
		void setAddress(String ipAsString, unsigned int port);
		void setAddress(unsigned int ip, unsigned int port);
		
		unsigned int uintAddress;
		unsigned int port;
		sockaddr_in sockAddress;		
	};
	
	
	class _PolyExport SocketEvent : public Event {
	public:
		SocketEvent(){}
		~SocketEvent(){}
		
		char data[MAX_PACKET_SIZE];
		unsigned int dataSize;
		Address fromAddress;
		
		static const int EVENT_ERROR = 0;
		static const int EVENT_DATA_RECEIVED = 1;
	};
	
	
	class _PolyExport Socket : public EventDispatcher {
		public:
			Socket(int port);
			~Socket();

			int receiveData();		
			bool sendData(const Address &address, char *data, unsigned int packetSize);
		
			void socketError(String error);
		
		private:
			
			
			int sockId;
	};
}
