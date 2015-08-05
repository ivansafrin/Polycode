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

#include "PolycodePlayer.h"
#include <string>

PolycodeRemoteDebuggerClient::PolycodeRemoteDebuggerClient() : EventDispatcher() {
	client = new Client(0, 1);
	client->Connect("127.0.0.1", 4630);	
	client->addEventListener(this, ClientEvent::EVENT_SERVER_DISCONNECTED);
}

void PolycodeRemoteDebuggerClient::handleEvent(Event *event) {

	if(event->getDispatcher() == client) {
		switch(event->getEventCode()) {
			case ClientEvent::EVENT_SERVER_DISCONNECTED:
				dispatchEvent(new Event(), Event::COMPLETE_EVENT);
			break;
		}
	} else {

	PolycodeDebugEvent *debugEvent = (PolycodeDebugEvent*) event;
	switch(event->getEventCode()) {
		case PolycodeDebugEvent::EVENT_PRINT:
			client->sendReliableDataToServer((char*)debugEvent->errorString.c_str(), debugEvent->errorString.length()+1, EVENT_DEBUG_PRINT);
		break;
		case PolycodeDebugEvent::EVENT_ERROR:
			RemoteErrorData data;
			
			if(debugEvent->errorString.length() > 254) {
				debugEvent->errorString = debugEvent->errorString.substr(0,254);
			}

			if(debugEvent->fileName.length() > 254) {
				debugEvent->fileName = debugEvent->fileName.substr(0,254);
			}

			
			strcpy(data.errorMessage, debugEvent->errorString.c_str());
			strcpy(data.fileName, debugEvent->fileName.c_str());
			data.lineNumber = debugEvent->lineNumber;
			data.backTraceSize = debugEvent->backTrace.size();
			
			client->sendReliableDataToServer((char*)&data, sizeof(data), EVENT_DEBUG_ERROR);
			
			for(int i=0; i < debugEvent->backTrace.size(); i++) {
				RemoteBacktraceData btData;
				
			if(debugEvent->backTrace[i].fileName.length() > 254) {
				debugEvent->backTrace[i].fileName = debugEvent->backTrace[i].fileName.substr(0,254);
			}
				
				
				strcpy(btData.fileName, debugEvent->backTrace[i].fileName.c_str());
				btData.lineNumber = debugEvent->backTrace[i].lineNumber;
				
				client->sendReliableDataToServer((char*)&btData, sizeof(btData), EVENT_DEBUG_BACKTRACE_INFO);				
			}
		break;		
	}
	}
}

PolycodeRemoteDebuggerClient::~PolycodeRemoteDebuggerClient() {
	printf("disconnecting debugger\n");
	client->Disconnect();
}

extern "C" {

//	extern int luaopen_Tau(lua_State* L); // declare the wrapped module
		//	loadFileIntoState(L, "Polycode Player.app/Contents/Resources/API/class.lua");
	
	int MyLoader(lua_State* pState)
	{		
		std::string module = lua_tostring(pState, 1);

		module += ".lua";
		
		std::string defaultPath = "API/";
		defaultPath.append(module);
		
		const char* fullPath = module.c_str();		
        Logger::log("Loading custom class: %s\n", module.c_str());

		OSFILE *inFile = OSBasics::open(module, "r");	
		
		if(!inFile) {
			inFile =  OSBasics::open(defaultPath, "r");	
		}
		
		if(inFile) {
			OSBasics::seek(inFile, 0, SEEK_END);	
			long progsize = OSBasics::tell(inFile);
			OSBasics::seek(inFile, 0, SEEK_SET);
			char *buffer = (char*)malloc(progsize+1);
			memset(buffer, 0, progsize+1);
			OSBasics::read(buffer, progsize, 1, inFile);
	
			PolycodePlayer *player = (PolycodePlayer*)CoreServices::getInstance()->getCore()->getUserPointer();	
			player->report(pState, luaL_loadbuffer(pState, (const char*)buffer, progsize, fullPath));		
			free(buffer);
			OSBasics::close(inFile);	
		} else {
			std::string err = "\n\tError - Could could not find ";
			err += module;
			err += ".";			
			lua_pushstring(pState, err.c_str());			
		}
		return 1;
	}

	static int customError(lua_State *L) {
		
		
		PolycodePlayer *player = (PolycodePlayer*)CoreServices::getInstance()->getCore()->getUserPointer();		
		player->crashed = true;
		
		std::vector<BackTraceEntry> backTrace;
		lua_Debug entry;
		int depth = 0;		
		while (lua_getstack(L, depth, &entry)) {
			lua_getinfo(L, "Sln", &entry);
			std::vector<String> bits = String(entry.short_src).split("\"");
			if(bits.size() > 1) {
				String fileName = bits[1];
				if(fileName != "class.lua") {
					
					BackTraceEntry trace;
					trace.lineNumber = entry.currentline;
					trace.fileName = fileName;
					backTrace.push_back(trace);
					
					//printf(">>>> In file: %s on line %d\n", fileName.c_str(), trace.lineNumber);
					//backTrace += "In file: " + fileName + " on line " + String::IntToString(entry.currentline)+"\n";
				}
			}
			depth++;
		}

		// horrible hack to determine the filenames of things
		bool stringThatIsTheMainFileSet = false;
		String stringThatIsTheMainFile;
		
		if(backTrace.size() == 0) {
					
					BackTraceEntry trace;
					trace.lineNumber = 0;
					trace.fileName = player->fullPath;
					backTrace.push_back(trace);
		
		} else {
			stringThatIsTheMainFileSet = true;
			stringThatIsTheMainFile = backTrace[backTrace.size()-1].fileName;
			backTrace[backTrace.size()-1].fileName = player->fullPath;
		}
		
		if(stringThatIsTheMainFileSet) {
			for(int i=0; i < backTrace.size(); i++) {
				if(backTrace[i].fileName == stringThatIsTheMainFile) {
					backTrace[i].fileName = player->fullPath;
				}
			}
		}
		
		const char *msg = lua_tostring(L, -1);		
		if (msg == NULL) msg = "(error with no message)";
		lua_pop(L, 1);
		
		printf("\n%s\n", msg);
		
		String errorString;
		std::vector<String> info = String(msg).split(":");
			
		if(info.size() > 2) {
			errorString = info[2];
		} else {
			errorString = msg;
		}
						
		PolycodeDebugEvent *event = new PolycodeDebugEvent();			
		event->errorString = errorString;
		event->backTrace = backTrace;		
		event->fileName = backTrace[0].fileName;
		event->lineNumber = backTrace[0].lineNumber;

		printf("\n---------------------\n");
		printf("Error: %s\n", errorString.c_str());
		printf("In file: %s\n", backTrace[0].fileName.c_str());
		printf("On line: %d\n", backTrace[0].lineNumber);
		printf("---------------------\n");
		printf("Backtrace\n");
		for(int i=0; i < backTrace.size(); i++) {
			printf("* %s on line %d", backTrace[i].fileName.c_str(), backTrace[i].lineNumber);
		}
		printf("\n---------------------\n");
				
		player->dispatchEvent(event, PolycodeDebugEvent::EVENT_ERROR);
				
		return 0;
	}
	
	static int areSameCClass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase *classOne = *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		PolyBase *classTwo = *((PolyBase**)lua_touserdata(L, 2));
		
		if(classOne == classTwo) {
			lua_pushboolean(L, true);
		} else {
			lua_pushboolean(L, false);		
		}		
		return 1;
	}
	
	static int debugPrint(lua_State *L)
	{
		const char *msg = lua_tostring(L, 1);
		PolycodeDebugEvent *event = new PolycodeDebugEvent();			
		if(msg)
			event->errorString = std::string(msg);
		else
			event->errorString = std::string("<invalid string>");
		
		Logger::log(">> %s\n", event->errorString.c_str());
		PolycodePlayer *player = (PolycodePlayer*)CoreServices::getInstance()->getCore()->getUserPointer();
		player->dispatchEvent(event, PolycodeDebugEvent::EVENT_PRINT);
		return 0;
	}	
	
	
	int PolycodePlayer::report (lua_State *L, int status) {
		const char *msg;		
		
		PolycodePlayer *player = (PolycodePlayer*)CoreServices::getInstance()->getCore()->getUserPointer();					
			
//		Logger::log("Error status: %d\n", status);
		if (status) {		
		
			std::vector<BackTraceEntry> backTrace;
					
			msg = lua_tostring(L, -1);
			if (msg == NULL) msg = "(error with no message)";
			Logger::log("status=%d, (%s)\n", status, msg);
			lua_pop(L, 1);
			
			std::vector<String> info = String(msg).split(":");
			
			BackTraceEntry trace;
						
			PolycodeDebugEvent *event = new PolycodeDebugEvent();			
			if(info.size() > 2) {
				event->errorString = info[2];
				event->lineNumber = atoi(info[1].c_str());
				event->fileName = info[0].replace("string ", "").replace("\"", "").replace("[", "").replace("]", "");
				
				trace.lineNumber = event->lineNumber;
				trace.fileName = event->fileName;
				
				printf(">>>> In file: %s on line %d\n", trace.fileName.c_str(), trace.lineNumber);				
			} else {
				event->errorString = std::string(msg);
				event->lineNumber = 0;
				event->fileName = player->fullPath; 								
				trace.fileName = event->fileName;
				trace.lineNumber = 0;
			}
			
			
			backTrace.push_back(trace);
			
			event->backTrace = backTrace;
			
			dispatchEvent(event, PolycodeDebugEvent::EVENT_ERROR);
			
		}
		return status;
	}	

	
	void PolycodePlayer::runFile(String fileName) {
		
		Logger::log("Running %s\n", fileName.c_str());
		
		L=lua_open();
		
		luaL_openlibs(L);		
		luaopen_debug(L);		
		luaopen_Polycode(L);
				
		lua_getfield(L, LUA_GLOBALSINDEX, "package");	// push "package"
		lua_getfield(L, -1, "loaders");					// push "package.loaders"
		lua_remove(L, -2);								// remove "package"
		
		// Count the number of entries in package.loaders.
		// Table is now at index -2, since 'nil' is right on top of it.
		// lua_next pushes a key and a value onto the stack.
		int numLoaders = 0;
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) 
		{
			lua_pop(L, 1);
			numLoaders++;
		}
		
		lua_pushinteger(L, numLoaders + 1);
		lua_pushcfunction(L, MyLoader);
		lua_rawset(L, -3);
		
		// Table is still on the stack.  Get rid of it now.
		lua_pop(L, 1);		
		
		lua_register(L, "debugPrint", debugPrint);
		lua_register(L, "__customError", customError);					

		lua_register(L, "__are_same_c_class", areSameCClass);
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "class");		
		lua_call(L, 1, 0);

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "Polycode");		
		lua_call(L, 1, 0);		

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "Physics2D");		
		lua_call(L, 1, 0);		

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "Physics3D");		
		lua_call(L, 1, 0);		

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "UI");		
		lua_call(L, 1, 0);		

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "tweens");		
		lua_call(L, 1, 0);
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "defaults");		
		lua_call(L, 1, 0);
		
		luaopen_Physics2D(L);
		luaopen_Physics3D(L);
		luaopen_UI(L);
        
        printf("CORE SERVICES: %d\n", CoreServices::getInstance());

		for(int i=0; i < loadedModules.size(); i++) {
			String moduleName = loadedModules[i];
#ifdef _WINDOWS
			TCHAR _tempPath[4098];
			TCHAR tempPath[4098];
			GetTempPathW(4098, _tempPath);
			GetLongPathNameW(_tempPath, tempPath, 4098);
			String moduleDestPath = String(tempPath) + String("\\") + moduleName+ String(".dll");
#else

	#if defined(__APPLE__) && defined(__MACH__)
			String moduleDestPath = String("/tmp/") + moduleName+ String(".dylib");
	#else
			String moduleDestPath = String("/tmp/") + moduleName+ String(".so");
	#endif
#endif
			String moduleLoadCall = String("luaopen_") + moduleName;
			lua_getfield(L, LUA_GLOBALSINDEX, "require");
			lua_pushstring(L, moduleName.c_str());		
			lua_call(L, 1, 0);

			printf("LOADING MODULE %s\n", moduleDestPath.c_str());
			lua_getfield(L, LUA_GLOBALSINDEX, "package");
			lua_getfield(L, -1, "loadlib");	
			lua_pushstring(L, moduleDestPath.c_str());
			lua_pushstring(L, moduleLoadCall.c_str());			
			lua_call(L, 2, 2);
			
			lua_setfield(L, LUA_GLOBALSINDEX, "err");
			lua_setfield(L, LUA_GLOBALSINDEX, "f");
			printf("SETTING CORE SERVICES\n");			
			lua_getfield(L, LUA_GLOBALSINDEX, "f");
			lua_getfield(L, LUA_GLOBALSINDEX, "__core__services__instance");
			lua_call(L, 1, 0);			
			
			printf("DONE LOADING MODULE...\n");
		}

		doneLoading = true;
		
		lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
		errH = lua_gettop(L);

		// MyLoader appends '.lua' so strip it if already present
		int pos = fileName.rfind(".lua");
		String stripped = fileName;
		if (pos > -1 && pos == fileName.length() - 4) stripped = fileName.substr(0, pos);
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, stripped.c_str());		
		if (lua_pcall(L, 1,0,errH)) {
			Logger::log("CRASH EXECUTING FILE\n");
		}

	}
}

PolycodeDebugEvent::PolycodeDebugEvent() : Event() {
	
}

PolycodeDebugEvent::~PolycodeDebugEvent() {
	
}


PolycodePlayer::PolycodePlayer(String fileName, bool knownArchive, bool useDebugger) : EventDispatcher()  {
	L = NULL;
	remoteDebuggerClient = NULL;

	crashed = false;
	doCodeInject = false;
	this->useDebugger = useDebugger;
	fileToRun = fileName;
	core = NULL;
	doneLoading = false;	
	_knownArchive = knownArchive;
	xRes = 640;
	yRes = 480;
	aaLevel = 6;
	fullScreen = false;	
	
}

void PolycodePlayer::loadFile(const char *fileName) {
	
	String mainFile = "";
	String basePath = fileName;
	
	Number red = 0.2f;
	Number green = 0.2f;
	Number blue = 0.2f;
	
	String textureFiltering = "linear";
	
	frameRate = 60;
	
	Object configFile;

	String nameString = fileName;
		
	bool loadingArchive = false;

	if(nameString != "") {
	String ext = nameString.substr(nameString.length() - 8, nameString.length());
	
	Logger::log("Loading %s\n", fileName);
	
	String configPath;
	
	if(ext == ".polyapp" || _knownArchive) {
		ResourceManager *rman = CoreServices::getInstance()->getResourceManager();
		rman->addArchive(nameString);
		configPath = "runinfo.polyrun";
		loadingArchive = true;
		Logger::log("Reading configuration from POLYAPP file... (%s)\n", nameString.c_str());
	} else {
		ResourceManager *rman = CoreServices::getInstance()->getResourceManager();
		
		String fileDir = "";
		std::vector<String> bits = String(fileName).split("/");
		for(int i=0; i <	 bits.size()-1; i++) {
			fileDir += "/"+bits[i];
		}
		
		rman->addArchive(fileDir);
		configPath = fileName;
		Logger::log("Reading configuration from .polycode file directly... (%s)\n", fileName);		
	}
	

	if(!configFile.loadFromXML(configPath)) {
		Logger::log("Error loading config file\n");
	} else {		
		
		if(configFile.root["entryPoint"]) {
			mainFile = configFile.root["entryPoint"]->stringVal;
		}		
		if(configFile.root["defaultWidth"]) {
			xRes = configFile.root["defaultWidth"]->intVal;
		}		
		if(configFile.root["defaultHeight"]) {
			yRes = configFile.root["defaultHeight"]->intVal;
		}		
		if(configFile.root["frameRate"]) {
			frameRate = configFile.root["frameRate"]->intVal;
		}		
		if(configFile.root["antiAliasingLevel"]) {
			aaLevel = configFile.root["antiAliasingLevel"]->intVal;
		}
		if(configFile.root["anisotropyLevel"]) {
			anisotropyLevel = configFile.root["anisotropyLevel"]->intVal;
		}		
		if(configFile.root["vSync"]) {
			vSync = configFile.root["vSync"]->boolVal;
		}						
		if(configFile.root["fullScreen"]) {
			fullScreen = configFile.root["fullScreen"]->boolVal;
		}				
		if(configFile.root["textureFiltering"]) {
			textureFiltering = configFile.root["textureFiltering"]->stringVal;
		}		
	
		
		if(configFile.root["backgroundColor"]) {
			ObjectEntry *color = configFile.root["backgroundColor"];
			if((*color)["red"] && (*color)["green"] && (*color)["blue"]) {
				red = (*color)["red"]->NumberVal;
				green = (*color)["green"]->NumberVal;
				blue = (*color)["blue"]->NumberVal;
				
			}			
		}
		
		ObjectEntry *fonts = configFile.root["fonts"];
		if(fonts) {
			for(int i=0; i < fonts->length; i++) {			
				ObjectEntry *fontName = (*(*fonts)[i])["name"];				
				ObjectEntry *fontPath = (*(*fonts)[i])["path"];
				
				if(fontName && fontPath) {
					printf("REGISTERING FONT %s %s\n", fontName->stringVal.c_str(), fontPath->stringVal.c_str());
					CoreServices::getInstance()->getFontManager()->registerFont(fontName->stringVal, fontPath->stringVal);
				}

			}
		}
		
		ObjectEntry *modules = configFile.root["modules"];			
		if(modules) {
			for(int i=0; i < modules->length; i++) {			
				String moduleName = (*modules)[i]->stringVal;
				Logger::log("Loading module: %s\n", moduleName.c_str());				

#ifdef _WINDOWS
			TCHAR _tempPath[4098];
			TCHAR tempPath[4098];
			GetTempPathW(4098, _tempPath);
			GetLongPathNameW(_tempPath, tempPath, 4098);
			String moduleDestPath = String(tempPath) + String("\\") + moduleName+ String(".dll");
			String moduleFileName = String("__lib/win/") + moduleName+ String(".dll");

#else
	#if defined(__APPLE__) && defined(__MACH__)
				String moduleFileName = String("__lib/osx/") + moduleName+ String(".dylib");
				String moduleDestPath = String("/tmp/") + moduleName+ String(".dylib");
	#else
				String moduleFileName = String("__lib/linux/") + moduleName+ String(".so");
				String moduleDestPath = String("/tmp/") + moduleName+ String(".so");
	#endif
#endif				
				OSFILE *inFile = OSBasics::open(moduleFileName, "rb");	
				if(inFile) {
					OSBasics::seek(inFile, 0, SEEK_END);	
					long progsize = OSBasics::tell(inFile);
					OSBasics::seek(inFile, 0, SEEK_SET);
					char *buffer = (char*)malloc(progsize+1);
					memset(buffer, 0, progsize+1);
					OSBasics::read(buffer, progsize, 1, inFile);
					
					OSFILE *outFile = OSBasics::open(moduleDestPath, "wb");						
					OSBasics::write(buffer, progsize, 1, outFile);
					OSBasics::close(outFile);	
					
					free(buffer);
					OSBasics::close(inFile);	
					
					loadedModules.push_back(moduleName);
				} else {
					Logger::log("Error loading module: %s\n", (*modules)[i]->stringVal.c_str());									
				}
			}

		}			
	}
	
	Logger::log("Mainfile: %s\n", mainFile.c_str());
	
	PolycodeDebugEvent *event = new PolycodeDebugEvent();			
	event->xRes = xRes;
	event->yRes = yRes;	
	
	}
	createCore();

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_JOYBUTTON_DOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_JOYBUTTON_UP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_JOYAXIS_MOVED);
					
	if(nameString == "") {
		return;
	}
	
	Logger::log("Core created...\n");

	CoreServices::getInstance()->getResourceManager()->addArchive("UIThemes.pak");
	CoreServices::getInstance()->getConfig()->loadConfig("Polycode", "UIThemes/default/theme.xml");
	
	CoreServices::getInstance()->getResourceManager()->addArchive("api.pak");
	CoreServices::getInstance()->getResourceManager()->addArchive("Physics2D.pak");
	CoreServices::getInstance()->getResourceManager()->addArchive("Physics3D.pak");
	CoreServices::getInstance()->getResourceManager()->addArchive("UI.pak");			
	if(configFile.root["packedItems"]) {
		ObjectEntry *packed = configFile.root["packedItems"];
		if(packed) {
			for(int i=0; i < packed->length; i++) {
				ObjectEntry *entryIsResource = (*(*packed)[i])["isResource"];				
				ObjectEntry *entryPath = (*(*packed)[i])["path"];
				if(entryIsResource && entryPath) {
					if(entryIsResource->boolVal == true) {
						CoreServices::getInstance()->getResourceManager()->addDirResource(entryPath->stringVal, true);
					}
				}
			}
		}
	}
	
	
	core->setUserPointer(this);
	//core->addEventListener(this, Core::EVENT_CORE_RESIZE);
	core->setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
	
	if(textureFiltering == "nearest") {
		CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	} else {
		CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_LINEAR);
	}
				
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);


//	dispatchEvent(event, PolycodeDebugEvent::EVENT_RESIZE);		
	
	CoreServices::getInstance()->getRenderer()->setClearColor(red, green, blue);
//	CoreServices::getInstance()->getRenderer()->setClearColor(1,0,0);
	srand(core->getTicks());
	
	if(loadingArchive) {
		fullPath = mainFile;
	} else {
		int lindex = basePath.find_last_of("/");
		fullPath = basePath.substr(0, lindex);	
		fullPath += mainFile;	
		Logger::log(fullPath.c_str());
	}

	if(useDebugger) {
	
			
		remoteDebuggerClient = new PolycodeRemoteDebuggerClient();
		remoteDebuggerClient->addEventListener(this, Event::COMPLETE_EVENT);
		
		this->addEventListener(remoteDebuggerClient, PolycodeDebugEvent::EVENT_PRINT);
		this->addEventListener(remoteDebuggerClient, PolycodeDebugEvent::EVENT_ERROR);		
		remoteDebuggerClient->client->addEventListener(this, ClientEvent::EVENT_CLIENT_READY);
		remoteDebuggerClient->client->addEventListener(this, ClientEvent::EVENT_SERVER_DATA);
		
		debuggerTimer = new Timer(true, 5000);
		debuggerTimer->addEventListener(this, Timer::EVENT_TRIGGER);
	} else{
		runFile(fullPath);
	}
}

void PolycodePlayer::runPlayer() {
	Logger::log("Running player\n");	
	loadFile(fileToRun.c_str());
}

PolycodePlayer::~PolycodePlayer() {
	this->removeAllHandlers();
	delete remoteDebuggerClient;
	Logger::log("deleting core...\n");
	delete core;
	PolycodeDebugEvent *event = new PolycodeDebugEvent();			
	dispatchEvent(event, PolycodeDebugEvent::EVENT_REMOVE);	
//	lua_close(L);
}

void PolycodePlayer::handleEvent(Event *event) {	


	if(event->getDispatcher() == debuggerTimer) {
		runFile(fullPath);
		debuggerTimer->Pause(true);
	}
	
	if(remoteDebuggerClient) {	
	
	if(event->getDispatcher() == remoteDebuggerClient) {
		if(event->getEventCode() == Event::COMPLETE_EVENT) {
			dispatchEvent(new PolycodeDebugEvent(), PolycodeDebugEvent::EVENT_CLOSE);
		}
	}

	if(event->getDispatcher() == remoteDebuggerClient->client) {
		ClientEvent *clientEvent = (ClientEvent*) event;
			
		switch(event->getEventCode()) {
			case ClientEvent::EVENT_CLIENT_READY:
				debuggerTimer->Pause(true);			
				runFile(fullPath);			
			break;
			
			case ClientEvent::EVENT_SERVER_DATA:
			{
				switch(clientEvent->dataType) {
					case PolycodeRemoteDebuggerClient::EVENT_INJECT_CODE:
					{
						char *code = (char*) clientEvent->data;
						injectCodeString = String(code);
						doCodeInject = true;
					}
					break;										
				}
			}
			break;			
		}
	}
	}
	
	if(event->getDispatcher() == core) {
		switch(event->getEventCode()) {
			case Core::EVENT_CORE_RESIZE:
				PolycodeDebugEvent *event = new PolycodeDebugEvent();			
				event->xRes = core->getXRes();
				event->yRes = core->getYRes();				
				dispatchEvent(event, PolycodeDebugEvent::EVENT_RESIZE);								
			break;		
		}
	}
	
	if(event->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*) event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);					
					lua_getfield(L, LUA_GLOBALSINDEX, "onKeyDown");
					lua_pushinteger(L, inputEvent->keyCode());
					lua_pcall(L, 1,0,errH);
					lua_settop(L, 0);
				}
			}
			break;
			case InputEvent::EVENT_KEYUP:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onKeyUp");
					lua_pushinteger(L, inputEvent->keyCode());
					lua_pcall(L, 1,0,errH);
					lua_settop(L, 0);								
				}
			}
			break;
			case InputEvent::EVENT_MOUSEDOWN:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onMouseDown");
					lua_pushinteger(L, inputEvent->mouseButton);
					lua_pushnumber(L, inputEvent->mousePosition.x);
					lua_pushnumber(L, inputEvent->mousePosition.y);	
					lua_pcall(L, 3,0,errH);					
					lua_settop(L, 0);					
				}
			}
			break;	
			case InputEvent::EVENT_MOUSEUP:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onMouseUp");
					lua_pushinteger(L, inputEvent->mouseButton);
					lua_pushnumber(L, inputEvent->mousePosition.x);
					lua_pushnumber(L, inputEvent->mousePosition.y);		
					lua_pcall(L, 3,0,errH);					
					lua_settop(L, 0);					
				}
			}
			break;	
			case InputEvent::EVENT_MOUSEMOVE:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onMouseMove");
					lua_pushnumber(L, inputEvent->mousePosition.x);
					lua_pushnumber(L, inputEvent->mousePosition.y);	
					lua_pcall(L, 2,0,errH);					
					lua_settop(L, 0);					
				}
			}
			break;																			
			case InputEvent::EVENT_JOYBUTTON_DOWN:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onJoystickButtonDown");
					lua_pushnumber(L, inputEvent->joystickIndex);
					lua_pushnumber(L, inputEvent->joystickButton);
					lua_pcall(L, 2,0,errH);	
					lua_settop(L, 0);					
				}
			}
			break;																			
			case InputEvent::EVENT_JOYBUTTON_UP:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onJoystickButtonUp");
					lua_pushnumber(L, inputEvent->joystickIndex);
					lua_pushnumber(L, inputEvent->joystickButton);
					lua_pcall(L, 2,0,errH);	
					lua_settop(L, 0);
				}
			}
			break;																			
			case InputEvent::EVENT_JOYAXIS_MOVED:
			{
				if(L && !crashed) {
					lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
					errH = lua_gettop(L);									
					lua_getfield(L, LUA_GLOBALSINDEX, "onJoystickAxisMoved");
					lua_pushnumber(L, inputEvent->joystickIndex);
					lua_pushnumber(L, inputEvent->joystickAxis);
					lua_pushnumber(L, inputEvent->joystickAxisValue);
					lua_pcall(L, 3,0,errH);	
					lua_settop(L, 0);
				}
			}
			break;																			
		}
	}
}


bool PolycodePlayer::Update() {
	bool retVal = core->systemUpdate();
	if(L) {
		lua_getfield (L, LUA_GLOBALSINDEX, "__customError");
		errH = lua_gettop(L);	
		if(doCodeInject) {
			printf("INJECTING CODE:[%s]\n", injectCodeString.c_str());
			doCodeInject = false;			
			report(L, luaL_loadstring(L, injectCodeString.c_str()));
			lua_pcall(L, 0,0,errH);		
		}	
		if(!crashed) {
			lua_getfield(L, LUA_GLOBALSINDEX, "__process_safe_delete");
			lua_pcall(L, 0,0,errH);	
		
			lua_getfield(L, LUA_GLOBALSINDEX, "__update");
			lua_pushnumber(L, core->getElapsed());
			lua_pcall(L, 1,0,errH);
		}
        
        while(core->fixedUpdate()) {
			lua_getfield(L, LUA_GLOBALSINDEX, "fixedUpdate");
			lua_pcall(L, 0,0,errH);
        }
        
		lua_settop(L, 0);
	}
	core->Render();
	return retVal;
}
