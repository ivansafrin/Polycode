/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "PolycodeRemoteDebugger.h"


PolycodeRemoteDebugger::PolycodeRemoteDebugger(PolycodeProjectManager *projectManager) {
	server = new Server(4630, 1);
	
	this->projectManager = projectManager;

	server->addEventListener(this, ServerEvent::EVENT_CLIENT_CONNECTED);
	server->addEventListener(this, ServerEvent::EVENT_CLIENT_DISCONNECTED);		

}

PolycodeRemoteDebugger::~PolycodeRemoteDebugger() {

}

bool PolycodeRemoteDebugger::isConnected() {
	return (debuggerClients.size() > 0);
}

void PolycodeRemoteDebugger::injectCode(String code) {
	server->sendReliableDataToAllClients((char*)code.c_str(), code.length()+1, EVENT_INJECT_CODE);
}

void PolycodeRemoteDebugger::handleEvent(Event *event) {

	for(int i=0; i < debuggerClients.size(); i++) {
		if(event->getDispatcher() == debuggerClients[i]->client) {		
			ServerClientEvent *clientEvent = (ServerClientEvent*) event;
			DebuggerClient *client = debuggerClients[i];
			switch(clientEvent->getEventCode()) {
				case ServerClientEvent::EVENT_CLIENT_DATA:				
					switch(clientEvent->dataType) {			
						case EVENT_DEBUG_PRINT:
						{
							String printStr = String(clientEvent->data);
							PolycodeConsole::print(printStr);		
							PolycodeConsole::print("\n");
						}
						break;	
						case EVENT_DEBUG_ERROR:
						{			
							RemoteErrorData *data = (RemoteErrorData*)clientEvent->data;			
							PolycodeConsole::print("Error in file "+String(data->fileName)+" on line "+String::IntToString(data->lineNumber)+"\n");
							PolycodeConsole::print(String(data->errorMessage)+"\n");
							PolycodeConsole::print("Backtrace:\n");
							
							CoreServices::getInstance()->getCore()->makeApplicationMain();
							
						}
						break;			
						case EVENT_DEBUG_BACKTRACE_INFO:
						{			
							RemoteBacktraceData *data = (RemoteBacktraceData*)clientEvent->data;			
							PolycodeConsole::print("In file "+String(data->fileName)+" on line "+String::IntToString(data->lineNumber)+"\n");
							
							PolycodeConsole::addBacktrace(String(data->fileName), data->lineNumber, projectManager->getActiveProject());
						}
						break;							
										
					}
				break;
			}
		}
	}


	if(event->getDispatcher() == server) {
		ServerEvent *serverEvent = (ServerEvent*) event;
		switch(serverEvent->getEventCode()) {
		
			case ServerEvent::EVENT_CLIENT_DISCONNECTED:		
			{
				for(int i=0;i<debuggerClients.size();i++) {
					if(debuggerClients[i]->client == serverEvent->client) {		
						DebuggerClient *client = debuggerClients[i];
						debuggerClients.erase(debuggerClients.begin()+i);	
						delete client;
						PolycodeConsole::print("Remote debugger client disconnected...\n");						
					}
				}
			}	
			break;
			
			case ServerEvent::EVENT_CLIENT_CONNECTED:
			{
				DebuggerClient *newClient = new DebuggerClient();
				newClient->client = serverEvent->client;
				newClient->client->addEventListener(this, ServerClientEvent::EVENT_CLIENT_DATA);
				PolycodeConsole::print("Remote debugger client connected...\n");printf("CLIENT CONNECTED\n");		
				debuggerClients.push_back(newClient);		
			}
			break;
		}
		
	}

}
