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

extern "C" {	
//	extern int luaopen_Tau(lua_State* L); // declare the wrapped module
		//	loadFileIntoState(L, "Polycode Player.app/Contents/Resources/API/class.lua");
	
	int MyLoader(lua_State* pState)
	{		
		std::string module = lua_tostring(pState, 1);
		module += ".lua";
		
		string defaultPath = "API/";
		defaultPath.append(module);
		
		const char* fullPath = module.c_str();		
		printf("Loading custom class: %s\n", module.c_str());
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
			luaL_loadbuffer(pState, (const char*)buffer, progsize, fullPath);		
			//free(buffer);
			OSBasics::close(inFile);	
		} else {
			std::string err = "\n\tError - Could could not find ";
			err += module;
			err += ".";			
			lua_pushstring(pState, err.c_str());			
		}
		return 1;
	}
	
	static int debugPrint(lua_State *L)
	{
		const char *msg = lua_tostring(L, 1);
		PolycodeDebugEvent *event = new PolycodeDebugEvent();			
		if(msg)
			event->errorString = string(msg);
		else
			event->errorString = string("<invalid string>");
		
		Logger::log(">> %s\n", event->errorString.c_str());
		PolycodePlayer *player = (PolycodePlayer*)CoreServices::getInstance()->getCore()->getUserPointer();
		player->dispatchEvent(event, PolycodeDebugEvent::EVENT_PRINT);
		return 0;
	}	
	
	int PolycodePlayer::report (lua_State *L, int status) {
		const char *msg;
			
		printf("Error status: %d\n", status);
		if (status) {
			msg = lua_tostring(L, -1);
			if (msg == NULL) msg = "(error with no message)";
			printf("status=%d, %s\n", status, msg);
			lua_pop(L, 1);
			
			vector<String> info = String(msg).split(":");
			
			PolycodeDebugEvent *event = new PolycodeDebugEvent();			
			if(info.size() > 2) {
				event->errorString = info[2];
				event->lineNumber = atoi(info[1].c_str());
			} else {
				event->errorString = string(msg);
				event->lineNumber = 0;
			}
			dispatchEvent(event, PolycodeDebugEvent::EVENT_ERROR);
			
		}
		return status;
	}	
	
	void PolycodePlayer::runFile(String fileName) {
		
		printf("Running %s\n", fileName.c_str());
		
		L=lua_open();
		
		/*
		 luaopen_base(L);	// load basic libs (eg. print)
		 luaopen_math(L);
		 luaopen_table(L);
		 luaopen_package(L);
		 */
		luaL_openlibs(L);
		
		luaopen_Polycode(L);
		//luaopen_Tau(L);	// load the wrappered module
		
		
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
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "class");		
		lua_call(L, 1, 0);

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "Polycode");		
		lua_call(L, 1, 0);		
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "defaults");		
		lua_call(L, 1, 0);
		
		for(int i=0; i < loadedModules.size(); i++) {
			String moduleName = loadedModules[i];
			String moduleDestPath = String("/tmp/") + moduleName+ String(".dylib");
			String moduleLoadCall = String("luaopen_") + moduleName;
			lua_getfield(L, LUA_GLOBALSINDEX, "require");
			lua_pushstring(L, moduleName.c_str());		
			lua_call(L, 1, 0);

			lua_getfield(L, LUA_GLOBALSINDEX, "package");
			lua_getfield(L, -1, "loadlib");	
			lua_pushstring(L, moduleDestPath.c_str());
			lua_pushstring(L, moduleLoadCall.c_str());			
			lua_call(L, 2, 1);
			lua_setfield(L, LUA_GLOBALSINDEX, "f");			
			
			lua_getfield(L, LUA_GLOBALSINDEX, "f");
			lua_getfield(L, LUA_GLOBALSINDEX, "__core__services__instance");						
			lua_call(L, 1, 0);			
			//local f = package.loadlib("/Users/ivansafrin/Desktop/Workshop/HelloPolycodeLUA/libPolycode2DPhysicsModule.dylib", "luaopen_Physics2D")
			//f(Polycore.CoreServices_getInstance())
					
		}

		String fileData = "";

		OSFILE *inFile = OSBasics::open(fileName, "r");	
		if(inFile) {
			Logger::log("Opened entrypoint file...");
			OSBasics::seek(inFile, 0, SEEK_END);	
			long progsize = OSBasics::tell(inFile);
			OSBasics::seek(inFile, 0, SEEK_SET);
			char *buffer = (char*)malloc(progsize+1);
			memset(buffer, 0, progsize+1);
			OSBasics::read(buffer, progsize, 1, inFile);
			fileData = String(buffer);		
			free(buffer);
			OSBasics::close(inFile);	
		} else {
			Logger::log("Error opening entrypoint file (%s)\n", fileName.c_str());
		}
		
		
		String postpend = ""; //" \nif update == nil then\nfunction update(e)\nend\nend\nwhile CORE:Update() do\nupdate(CORE:getElapsed())\nend";
		
		//String fullScript = prepend + prepend2 + prepend3 + fileData;// + postpend;
		String fullScript = fileData;
		//String fullScript = fileData;// + postpend;
		
		doneLoading = true;
		
		//lua_gc(L, LUA_GCSTOP, 0);
		
		
/*
		lua_pushliteral(L, "debug");
		lua_gettable(L, LUA_GLOBALSINDEX);
		lua_pushliteral(L, "traceback");  // correct fn name?
		lua_gettable(L, -2);

*/				
		
		CoreServices::getInstance()->getCore()->lockMutex(CoreServices::getRenderMutex());			
		if (report(L, luaL_loadstring(L, fullScript.c_str()) || lua_pcall(L, 0,0,0))) {
			
			CoreServices::getInstance()->getCore()->unlockMutex(CoreServices::getRenderMutex());			
			printf("CRASH LOADING SCRIPT FILE\n");
//			exit(1);				
		} else  {
			CoreServices::getInstance()->getCore()->unlockMutex(CoreServices::getRenderMutex());			
			if (report(L, luaL_loadstring(L, postpend.c_str()) || lua_pcall(L, 0,0,0))) {	
//				exit(1);
				printf("CRASH IN SCRIPT EXECUTION FILE\n");			
			} else  {

			}
		}

	}
}

PolycodeDebugEvent::PolycodeDebugEvent() : Event() {
	
}

PolycodeDebugEvent::~PolycodeDebugEvent() {
	
}


PolycodePlayer::PolycodePlayer(String fileName, bool knownArchive) : EventDispatcher()  {
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
	
	String nameString = fileName;
	String ext = nameString.substr(nameString.length() - 8, nameString.length());
	
	printf("Loading %s\n", fileName);
	
	bool loadingArchive = false;
	
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
		vector<String> bits = String(fileName).split("/");
		for(int i=0; i < bits.size()-1; i++) {
			fileDir += "/"+bits[i];
		}
		
		rman->addArchive(fileDir);
		configPath = fileName;
		Logger::log("Reading configuration from .polycode file directly... (%s)\n", fileName);		
	}
	
	String mainFile = "";
	String basePath = fileName;
	
	Number red = 0.2f;
	Number green = 0.2f;
	Number blue = 0.2f;
	
	frameRate = 60;
	
	Object configFile;
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
		if(configFile.root["fullScreen"]) {
			fullScreen = configFile.root["fullScreen"]->boolVal;
		}		
		if(configFile.root["backgroundColor"]) {
			ObjectEntry *color = configFile.root["backgroundColor"];
			if((*color)["red"] && (*color)["green"] && (*color)["blue"]) {
				red = (*color)["red"]->NumberVal;
				green = (*color)["green"]->NumberVal;
				blue = (*color)["blue"]->NumberVal;
				
			}			
		}
		ObjectEntry *modules = configFile.root["modules"];			
		if(modules) {
			for(int i=0; i < modules->length; i++) {			
				String moduleName = (*modules)[i]->stringVal;
				printf("Loading module: %s\n", moduleName.c_str());				
				String moduleFileName = String("__lib/osx/") + moduleName+ String(".dylib");
				String moduleDestPath = String("/tmp/") + moduleName+ String(".dylib");
				
				OSFILE *inFile = OSBasics::open(moduleFileName, "r");	
				if(inFile) {
					OSBasics::seek(inFile, 0, SEEK_END);	
					long progsize = OSBasics::tell(inFile);
					OSBasics::seek(inFile, 0, SEEK_SET);
					char *buffer = (char*)malloc(progsize+1);
					memset(buffer, 0, progsize+1);
					OSBasics::read(buffer, progsize, 1, inFile);
					
					OSFILE *outFile = OSBasics::open(moduleDestPath, "w");						
					OSBasics::write(buffer, progsize, 1, outFile);
					OSBasics::close(outFile);	
					
					free(buffer);
					OSBasics::close(inFile);	
					
					loadedModules.push_back(moduleName);
				} else {
					printf("Error loading module: %s\n", (*modules)[i]->stringVal.c_str());									
				}
			}

		}			
	}
	
	Logger::log("Mainfile: %s\n", mainFile.c_str());
	
	PolycodeDebugEvent *event = new PolycodeDebugEvent();			
	event->xRes = xRes;
	event->yRes = yRes;	
	
	createCore();
	
	Logger::log("Core created...\n");
	
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");
	
	
	CoreServices::getInstance()->installModule(new GLSLShaderModule());	
	
	
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
	core->setVideoMode(xRes, yRes, fullScreen, aaLevel);
		
//	dispatchEvent(event, PolycodeDebugEvent::EVENT_RESIZE);		
	
	CoreServices::getInstance()->getRenderer()->setClearColor(red, green, blue);
//	CoreServices::getInstance()->getRenderer()->setClearColor(1,0,0);
	srand(core->getTicks());
	
	String fullPath;
	
	if(loadingArchive) {
		fullPath = mainFile;
	} else {
		int lindex = basePath.find_last_of("/");
		fullPath = basePath.substr(0, lindex);	
		fullPath += mainFile;	
		Logger::log(fullPath.c_str());
	}
	
	runFile(fullPath);
}

void PolycodePlayer::runPlayer() {
	Logger::log("Running player\n");	
	loadFile(fileToRun.c_str());
}

PolycodePlayer::~PolycodePlayer() {
	printf("deleting core...\n");
	delete core;
	PolycodeDebugEvent *event = new PolycodeDebugEvent();			
	dispatchEvent(event, PolycodeDebugEvent::EVENT_REMOVE);	
//	lua_close(L);
}

void PolycodePlayer::handleEvent(Event *event) {	
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
}


bool PolycodePlayer::Update() {
	
	lua_getfield(L, LUA_GLOBALSINDEX, "Update");
	lua_pushnumber(L, core->getElapsed());
	lua_call(L, 1, 0);
	
	return core->Update();
}
