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

#include "PolySocket.h"
#include "PolyLogger.h"

#ifndef _WINDOWS
	#include <unistd.h>
#endif

using namespace Polycode;
using std::vector;

Address::Address(String ipAsString, unsigned int port) {
	setAddress(ipAsString, port);
}

Address::Address(unsigned int ip, unsigned int port) {
	setAddress(ip, port);
}

Address::Address()  : uintAddress(0), port(0) {
}

void Address::setAddress(unsigned int ip, unsigned int port) {
	unsigned short destination_port = port;

	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = htonl(ip);
	sockAddress.sin_port = htons( destination_port );

	uintAddress = ip;
	this->port = port;
}

void Address::setAddress(String ipAsString, unsigned int port) {
	unsigned int a = 127;
	unsigned int b = 0;
	unsigned int c = 0;
	unsigned int d = 1;

	vector<String> values = ipAsString.split(".");
	if(values.size() == 4) {
		a = atoi(values[0].c_str());
		b = atoi(values[1].c_str());
		c = atoi(values[2].c_str());
		d = atoi(values[3].c_str());
	} else {
		Logger::log("Invalid IP address!\n");
	}

	unsigned int destination_address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
	unsigned short destination_port = port;

	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = htonl( destination_address );
	sockAddress.sin_port = htons( destination_port );

	uintAddress = destination_address;
	this->port = port;
}

Address::~Address() {

}

Socket::Socket(int port) : EventDispatcher() {
	sockId = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

	if (sockId < 0) {
		socketError("Error creating socket");
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( (unsigned short) port );

	if( bind(sockId, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 ) {
		socketError( "failed to bind socket");
	}

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	int nonBlocking = 1;
	if ( fcntl( sockId, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 ) {
		socketError( "failed to set non-blocking socket");
	}
#elif PLATFORM == PLATFORM_WINDOWS
	DWORD nonBlocking = 1;
	if ( ioctlsocket( sockId, FIONBIO, &nonBlocking ) != 0 ) {
		socketError( "failed to set non-blocking socket");
	}
#endif
}

bool Socket::sendData(const Address &address, char *data, unsigned int packetSize) {
	int sent_bytes = sendto(sockId, (const char*)data, packetSize, 0, (sockaddr*)&address.sockAddress, sizeof(sockaddr_in));

	if ( sent_bytes != packetSize ) {
		socketError("failed to send packet");
		return false;
	}
	return true;
}

int Socket::receiveData() {

	SocketEvent *event = new SocketEvent();	
	sockaddr_in from;
	socklen_t fromLength = sizeof( from );

	int received_bytes = recvfrom( sockId, (char*)event->data, MAX_PACKET_SIZE,
								  0, (sockaddr*)&from, &fromLength );

	if ( received_bytes <= 0 ) {
		delete event;
		return received_bytes; 
	}

	event->dataSize = received_bytes;
	event->fromAddress = Address(ntohl( from.sin_addr.s_addr ), ntohs( from.sin_port ));
	dispatchEvent(event, SocketEvent::EVENT_DATA_RECEIVED);
	return received_bytes;
}

Socket::~Socket() {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	close( sockId );
#elif PLATFORM == PLATFORM_WINDOWS
	closesocket( sockId );
#endif
}

void Socket::socketError(String error) {
	Logger::log("%s\n",error.c_str());
}
