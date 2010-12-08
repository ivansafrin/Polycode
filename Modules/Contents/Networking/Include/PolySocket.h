// @package Network

#pragma once

#include "PolyGlobals.h"
#include "PolyUtil.h"
#include "stdio.h"

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#endif

#include <string>

#include "PolyEventDispatcher.h"

using std::string;

#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

namespace Polycode {
		
	class _PolyExport Address  {
		public:
		Address(string ipAsString, unsigned int port);
		Address(unsigned int ip, unsigned int port);
		Address();
		~Address();
		
		inline void operator = (const Address &add2) {
			setAddress(add2.uintAddress, add2.port);
		}
		
		inline bool operator == ( const Address& add2)  {
			return (uintAddress == add2.uintAddress && port == add2.port);
		}
			
		
		void setAddress(string ipAsString, unsigned int port);
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
		
			void socketError(string error);
		
		private:
			
			
			int sockId;
	};
}
