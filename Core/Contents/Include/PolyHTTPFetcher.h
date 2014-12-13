/*
Copyright (C) 2014 by Joachim Meyer

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
#include <string.h>
#ifdef _WINDOWS
	#include <winsock2.h>
	#include <Ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <netdb.h>
    #include <arpa/inet.h>
    #include <errno.h>
#endif
#include "PolyGlobals.h"
#include "PolyEvent.h"
#include "PolyEventDispatcher.h"

#define HTTP_VERSION 			"HTTP/1.0"
#define DEFAULT_USER_AGENT		"Polycode HTTP Fetcher/1.0"
#define DEFAULT_PAGE_BUF_SIZE 	1024 * 200	/* 200K should hold most things */

namespace Polycode {
	class HTTPFetcherEvent : public Event {
	public:
		HTTPFetcherEvent() { data = (char*)malloc(DEFAULT_PAGE_BUF_SIZE); memset(data, 0, DEFAULT_PAGE_BUF_SIZE); }
		~HTTPFetcherEvent(){}

		char *data;
		
		static const int EVENTBASE_SOCKETEVENT = 0x500;
		static const int EVENT_HTTP_ERROR = EVENTBASE_SOCKETEVENT + 2;
		static const int EVENT_HTTP_DATA_RECEIVED = EVENTBASE_SOCKETEVENT + 3;
	};

	class HTTPFetcher : public EventDispatcher{
	public:
		HTTPFetcher(String address);
		~HTTPFetcher();

		bool receiveHTTPData();

		String getData();

	private:
        int s;
		String address;
		String bodyReturn;
		int pathIndex;
		String host;
	};
}
