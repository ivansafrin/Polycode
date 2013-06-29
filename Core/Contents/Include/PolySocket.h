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
// DO NOT USE FOR PRODUCTION
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

/**
* A typical network address, defined by IP and port.
*/
class _PolyExport Address  {
	public:

		/**
		* Constructor.
		* @param ipAsString An IP address represented as string,
		*                   for example "127.0.0.1"
		* @param port The UDP/TCP port of the address, given in
		*             host byte order.
		*/
		Address(String ipAsString, unsigned int port);

		/**
		* Constructor.
		* @param ip An IP address given as integer in host byte
		*           order.
		* @param port The UDP/TCP port of the address, given in
		*             host byte order.
		*/
		Address(unsigned int ip, unsigned int port);

		/**
		* Constructor, leaving the address uninitalized.
		*
		* Address IP and port will default to 0.
		*/
		Address();
		~Address();

		/**
		* Copy the address IP and port from add2 into this.
		* @param add2 The address to copy into this.
		*/
		inline void operator = (const Address &add2) {
			setAddress(add2.uintAddress, add2.port);
		}

		/**
		* @return 1 if the address IP and port match, 0 otherwise.
		*/
		inline bool operator == ( const Address& add2)  {
			return (uintAddress == add2.uintAddress && port == add2.port);
		}

		/**
		* Update the address IP and port.
		* @param ipAsString An IP address represented as string,
		*                   for example "197.0.0.1"
		* @param port The UDP/TCP port of the address, given in
		*             host byte order.
		*/
		void setAddress(String ipAsString, unsigned int port);

		/**
		* Update the address IP and port.
		* @param ip An IP address given as integer in host byte
		*           order.
		* @param port The UDP/TCP port of the address, given in
		*             host byte order.
		*/
		void setAddress(unsigned int ip, unsigned int port);
		
		// TODO: A way to get the IP/port without exposing internal members.
		//       The problem here is that the IP internally is converted to
		//       network byte order, but the API seems to work with host byte
		//       order, so I'm unsure in which byte order the IP/port should
		//       be returned.

	protected:
		unsigned int uintAddress;
		unsigned int port;

		sockaddr_in sockAddress;

		// This class already uses socket API structs internally,
		// so it's no far stretch to make it tied to the Socket class.
		friend class Socket;
};


class _PolyExport SocketEvent : public Event {
	public:
		SocketEvent(){}
		~SocketEvent(){}

		char data[MAX_PACKET_SIZE];
		unsigned int dataSize;
		Address fromAddress;

		static const int EVENTBASE_SOCKETEVENT = 0x500;
		static const int EVENT_ERROR = EVENTBASE_SOCKETEVENT+0;
		static const int EVENT_DATA_RECEIVED = EVENTBASE_SOCKETEVENT+1;
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
