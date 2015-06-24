/*
Copyright (C) 2015 by Joachim Meyer

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

#ifdef _WINDOWS
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#endif

#include "PolyHTTPFetcher.h"
#include "PolyLogger.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"

using namespace Polycode;

HTTPFetcher::HTTPFetcher(String address, bool saveToPath, String savePath) : Threaded() {
	core = CoreServices::getInstance()->getCore();
	eventMutex = core->getEventMutex();

	storeInFile = saveToPath;
	this->savePath = savePath;

	this->address = address;
	int protocolIndex = address.find_first_of("://");
    if (protocolIndex != 0){
		protocolIndex += strlen("://");
		protocol = address.substr(0, protocolIndex - strlen("://"));
		int pathIndex = address.find_first_of("/", protocolIndex);
		path = address.substr(pathIndex+1, address.length());
		
		if (pathIndex != 0){
			host = address.substr(protocolIndex, pathIndex - protocolIndex);
		} else {
			host = address.substr(protocolIndex, address.length());
		}
	} else {
		int pathIndex = address.find_first_of("/");
		path = address.substr(pathIndex+1, address.length());

		if (pathIndex != 0){
			host = address.substr(0, pathIndex);
		} else {
			host = address;
		}
	}

	if (!createSocket())
		return;

	threadRunning = true;
	CoreServices::getInstance()->getCore()->createThread(this);
}

HTTPFetcher::~HTTPFetcher(){
#ifdef _WINDOWS
	closesocket(s);
#else
	close(s);
#endif
}

bool HTTPFetcher::createSocket(){
	struct sockaddr_in server;

	addrinfo *result = NULL;
	addrinfo hints;

	//Create a socket
#if PLATFORM == PLATFORM_WINDOWS
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		Logger::log("HTTP Fetcher: Could not create socket: %d\n", WSAGetLastError());
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		Logger::log("HTTP Fetcher: Could not create socket: %s\n", strerror(errno));
#endif
		return false;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(host.c_str(), protocol.c_str(), &hints, &result) != 0) {
#if PLATFORM == PLATFORM_WINDOWS
		Logger::log("HTTP Fetcher: Address resolve error: %d\n", WSAGetLastError());
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		Logger::log("HTTP Fetcher: Address resolve error: %s\n", strerror(errno));
#endif
		return false;
	}

	server.sin_addr = ((sockaddr_in*)result->ai_addr)->sin_addr;
	server.sin_family = AF_INET;
	server.sin_port = ((sockaddr_in*)result->ai_addr)->sin_port;

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
#if PLATFORM == PLATFORM_WINDOWS
		Logger::log("HTTP Fetcher: connect error code: %d\n", WSAGetLastError());
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		Logger::log("HTTP Fetcher: connect error code: %s\n", strerror(errno));
#endif
		return false;
	}
	return true;
}

void HTTPFetcher::updateThread(){
	int protocolIndex = path.find_first_of("://");
	if (protocolIndex != 0){
		protocolIndex += strlen("://");
		protocol = path.substr(0, protocolIndex - strlen("://"));
		int pathIndex = path.find_first_of("/", protocolIndex);
		path = path.substr(pathIndex + 1, path.length());
	} else if (path.find_first_of("/") == 0) {
		path = path.substr(1, path.length());
	}

	//Send some data
	String request;
	if (path != "") {
		request = "GET /" + path + " " + String(HTTP_VERSION) + "\r\nHost: " + host + "\r\nUser-Agent: " + DEFAULT_USER_AGENT + "\r\nConnection: close\r\n\r\n";
	} else {
		request = "GET / " + String(HTTP_VERSION) + "\r\nHost: " + host + "\r\nUser-Agent: " + DEFAULT_USER_AGENT + "\r\nConnection: close\r\n\r\n";
	}

	HTTPFetcherEvent *event = new HTTPFetcherEvent();

	if (send(s, request.c_str(), strlen(request.c_str()), 0) < 0) {
#if PLATFORM == PLATFORM_WINDOWS
        Logger::log("HTTP Fetcher: Send failed: %d\n", WSAGetLastError());
		event->errorCode = WSAGetLastError();
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        Logger::log("HTTP Fetcher: Send failed: %s\n",strerror(errno));
		event->errorCode = errno;
#endif
		createSocket();
		dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_ERROR);
		return;
	}

	char *server_reply = (char*)malloc(1);
	char *rec = server_reply;
	unsigned long recv_size = 0, totalRec = 0;
	do {
		//Receive a reply from the server
#if PLATFORM == PLATFORM_WINDOWS
		if ((recv_size = recv(s, rec, 1, 0)) == SOCKET_ERROR) {
			Logger::log("HTTP Fetcher: recv failed: %d\n", WSAGetLastError());
			event->errorCode = WSAGetLastError();
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		if ((recv_size = recv(s, rec, DEFAULT_PAGE_BUF_SIZE, 0)) == -1) {
			Logger::log("HTTP Fetcher: recv failed: %s\n", strerror(errno));
			event->errorCode = errno;
#endif
			dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_ERROR);
			killThread();
			return;
		}

		
		totalRec += recv_size;
		server_reply = (char*)realloc(server_reply, totalRec + 1);
		rec = server_reply + totalRec;
	} while (recv_size != 0 && strstr(server_reply, "\r\n\r\n") == NULL);

	server_reply[totalRec] = '\0';
	event->data = server_reply;

	if (strlen(event->data) == 0){
		createSocket();
		return;
	}

	char *charIndex = strstr(event->data, "HTTP/");
    if(charIndex == NULL){
		killThread();
		return;
    }
    int i;
	if (sscanf(charIndex + strlen("HTTP/1.1"), "%d", &i) != 1 || i < 200 || i>299) {
		event->errorCode = i;
		dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_ERROR);
		killThread();
		return;
	}
	charIndex = strstr(event->data, "Content-Length:");
	if (charIndex == NULL)
		charIndex = strstr(event->data, "Content-length:");
	if (sscanf(charIndex + strlen("content-length: "), "%d", &i) != 1) {
		dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_ERROR);
		killThread();
		return;
	}

	FILE* tempFile;
	if (storeInFile){
		if (savePath == "")
			savePath = path;
		tempFile = fopen(savePath.c_str(), "wb");
	}

	free(server_reply);
	server_reply = (char*)malloc(DEFAULT_PAGE_BUF_SIZE);
	rec = server_reply;
	recv_size = 0, totalRec = 0;

	do {
		//Receive a reply from the server
#if PLATFORM == PLATFORM_WINDOWS
		if ((recv_size = recv(s, rec, DEFAULT_PAGE_BUF_SIZE, 0)) == SOCKET_ERROR) {
			Logger::log("HTTP Fetcher: recv failed: %d\n", WSAGetLastError());
			event->errorCode = WSAGetLastError();
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		if ((recv_size = recv(s, rec, DEFAULT_PAGE_BUF_SIZE, 0)) == -1) {
			Logger::log("HTTP Fetcher: recv failed: %s\n", strerror(errno));
			event->errorCode = errno;
#endif
			dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_ERROR);
			killThread();
			return;
		}


		totalRec += recv_size;
		if (!storeInFile){
			server_reply = (char*)realloc(server_reply, totalRec + DEFAULT_PAGE_BUF_SIZE);
			rec = server_reply + totalRec;
		} else {
			server_reply[recv_size] = '\0';
			fwrite(server_reply, 1, recv_size, tempFile);
		}
	} while (recv_size !=0 && totalRec < i);

	if (totalRec > i){
		event->errorCode = HTTPFetcher::HTTPFETCHER_ERROR_WRONG_SIZE;
		dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_ERROR);
		killThread();
		return;
	}
	if (storeInFile){
		event->storedInFile = true;
		event->data = (char*)malloc(sizeof(char)*(savePath.length() + 1));
		strcpy(event->data, savePath.c_str());
		fclose(tempFile);
	} else {
		event->data = server_reply;
	}

	event->contentSize = totalRec;
	bodyReturn = event->data;
    dispatchEvent(event, HTTPFetcherEvent::EVENT_HTTP_DATA_RECEIVED);
	killThread();
}

void HTTPFetcher::fetchFile(String pathToFile, bool saveToPath, String savePath){
	path = pathToFile;
	this->savePath = savePath;
	this->storeInFile = saveToPath;
	threadRunning = true;
	CoreServices::getInstance()->getCore()->createThread(this);
}

String HTTPFetcher::getData(){
	return this->bodyReturn;
}
