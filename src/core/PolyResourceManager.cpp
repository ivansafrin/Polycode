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

#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCubemap.h"
#include "polycode/core/PolyMaterialManager.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyFont.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyScript.h"
#include "polycode/core/PolyCore.h"
#include "polycode/bindings/lua/PolycodeLua.h"
#include "tinyxml.h"

using std::vector;
using namespace Polycode;

bool ResourcePool::defaultReloadResourcesOnModify = false;

ResourcePool::ResourcePool(const String &name, ResourcePool *fallbackPool) {
    
    this->name = name;
    this->fallbackPool = fallbackPool;
	dispatchChangeEvents = false;
	reloadResourcesOnModify = ResourcePool::defaultReloadResourcesOnModify;
	ticksSinceCheck = 0;
    resourceSubscribers = 0;
    deleteOnUnsubscribe = false;
}

ResourcePool::~ResourcePool() {
    
    CoreServices::getInstance()->getResourceManager()->removeResourcePool(this);
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]->getResourceType() == Resource::RESOURCE_MATERIAL) {
            delete resources[i];
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]->getResourceType() == Resource::RESOURCE_SHADER) {
            delete resources[i];
        }
    }
    
    for(int i=0; i < resources.size(); i++)	{
        if(resources[i]->getResourceType() == Resource::RESOURCE_PROGRAM) {
            delete resources[i];
        }
    }
    
    resources.clear();
}

String ResourcePool::getName() {
    return name;
}

void ResourcePool::setName(const String &name) {
    this->name = name;
}

void ResourcePool::removeResource(Resource *resource) {
	for(int i=0;i<resources.size();i++) {
		if(resources[i] == resource) {
			resources.erase(resources.begin()+i);
			return;
		}
	}
}

bool ResourcePool::hasResource(Resource *resource) {
	for(int i=0; i < resources.size(); i++) {
		if(resources[i] == resource) {
			return true;
		}
	}
	return false;
}

void ResourcePool::addResource(Resource *resource) {
    resource->addEventListener(this, Event::RESOURCE_CHANGE_EVENT);
    resources.push_back(resource);
    
    // NOCMAKE_TODO: fix this!!
    resource->resourceFileTime = 0; //OSBasics::getFileTime(resource->getResourcePath());
    if(dispatchChangeEvents) {
        dispatchEvent(new Event(), Event::CHANGE_EVENT);
    }
}

void ResourcePool::setFallbackPool(ResourcePool *pool) {
    fallbackPool = pool;
}

bool ResourceLoader::canHandleExtension(const String &extension) {
    for(int i=0; i < extensions.size(); i++) {
        if(extensions[i] == extension) {
            return true;
        }
    }
    return false;
}

TextureResourceLoader::TextureResourceLoader() {
    extensions.push_back("png");
    extensions.push_back("hdr");
    extensions.push_back("jpg");
    extensions.push_back("tga");
    extensions.push_back("psd");
}

Resource *TextureResourceLoader::loadResource(const String &path,  ResourcePool *targetPool) {
    MaterialManager *materialManager = Services()->getMaterialManager();
    Texture *texture = materialManager->createTextureFromFile(path, materialManager->clampDefault, materialManager->mipmapsDefault);
    return texture;
}

void ResourcePool::loadResourcesFromFolderWithLoader(const String &folder, bool recursive, ResourceLoader *loader, const String &containingFolder) {
    vector<OSFileEntry> resourceDir;
    
    resourceDir = Services()->getCore()->parseFolder(folder, false);
    
    for(int i=0; i < resourceDir.size(); i++) {
        if(resourceDir[i].type == OSFileEntry::TYPE_FILE) {
            Resource *newResource = NULL;
            if(loader->canHandleExtension(resourceDir[i].extension)) {
                newResource = loader->loadResource(resourceDir[i].fullPath, this);
            }
            if(newResource) {
                if(newResource->getResourceName() == "") {
                    newResource->setResourceName(resourceDir[i].name);
                }
                newResource->setResourcePath(resourceDir[i].fullPath);
                addResource(newResource);
            }
        } else {
            if(recursive) {
                loadResourcesFromFolderWithLoader(folder+"/"+resourceDir[i].name, true, loader, containingFolder);
            }
        }
    }
}

Resource *ResourcePool::loadResource(const String &path) {
    
    Resource *newResource = getResourceByPath(path);
    if(newResource) {
        return newResource;
    }
    
    OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
    for(int r = 0; r < Services()->getResourceManager()->getNumResourceLoaders(); r++) {
        ResourceLoader *loader = Services()->getResourceManager()->getResourceLoaderAtIndex(r);
        if(loader->canHandleExtension(entry.extension)) {
            newResource = loader->loadResource(entry.fullPath, this);
            if(newResource) {
                newResource->setResourceName(entry.name);
                newResource->setResourcePath(entry.fullPath);
                addResource(newResource);
                break;
            }
        }
    }
    return newResource;
}

Resource *ResourcePool::loadResourceWithName(const String &path, const String &name) {
    
    Resource *newResource = getResourceByPath(path);
    if(newResource) {
        return newResource;
    }
    
    OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
    for(int r = 0; r < Services()->getResourceManager()->getNumResourceLoaders(); r++) {
        ResourceLoader *loader = Services()->getResourceManager()->getResourceLoaderAtIndex(r);
        if(loader->canHandleExtension(entry.extension)) {
            newResource = loader->loadResource(entry.fullPath, this);
            if(newResource) {
                newResource->setResourceName(name);
                newResource->setResourcePath(entry.fullPath);
                addResource(newResource);
                break;
            }
        }
    }
    return newResource;
}

void ResourcePool::loadResourcesFromFolder(const String &folder, bool recursive) {
    for(int r = 0; r < Services()->getResourceManager()->getNumResourceLoaders(); r++) {
        ResourceLoader *loader = Services()->getResourceManager()->getResourceLoaderAtIndex(r);
        loadResourcesFromFolderWithLoader(folder, recursive, loader, "");
    }
}


Resource *ResourcePool::getResourceByPath(const String& resourcePath) const {
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourcePath() == resourcePath) {
			return resources[i];
		}
	}
    
    if(fallbackPool) {
        return fallbackPool->getResourceByPath(resourcePath);
    } else {
        return NULL;
    }
}

std::vector<Resource*> ResourcePool::getResources(int resourceType) {
	std::vector<Resource*> result;
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceType() == resourceType) {
			result.push_back(resources[i]);
		}
	}
    
	return result;
}

Resource *ResourcePool::getResource(int resourceType, const String& resourceName) const {
	for(int i =0; i < resources.size(); i++) {
		if(resources[i]->getResourceName() == resourceName && resources[i]->getResourceType() == resourceType) {
			return resources[i];
		}
	}
	
	if(resourceType == Resource::RESOURCE_TEXTURE && resourceName != "default/default.png") {
		Logger::log("Texture [%s] not found in pool [%s], using default\n", resourceName.c_str(), name.c_str());
		return getResource(Resource::RESOURCE_TEXTURE, "default/default.png");
	}
    
    if(fallbackPool) {
        return fallbackPool->getResource(resourceType, resourceName);
    } else {
        Logger::log("Could not find resource [%s] in pool [%s]\n", resourceName.c_str(), name.c_str());
        
        return NULL;
    }
}

void ResourcePool::checkForChangedFiles() {
	for(int i=0; i < resources.size(); i++) {
		if(resources[i]->reloadOnFileModify == true) {
            
            // NOCMAKE_TODO: fix this!
            time_t newFileTime = 0; //OSBasics::getFileTime(resources[i]->getResourcePath());
            //			printf("%s\n%lld %lld\n", resources[i]->getResourcePath().c_str(), newFileTime, resources[i]->resourceFileTime);
			if((newFileTime != resources[i]->resourceFileTime) && newFileTime != 0) {
				resources[i]->reloadResource();
				resources[i]->resourceFileTime = newFileTime;
			}
		}
	}
}

ResourceManager::ResourceManager() : EventDispatcher() {
    globalPool = new ResourcePool("Global", NULL);
    
    resourceLoaders.push_back(new TextureResourceLoader());
    resourceLoaders.push_back(new ProgramResourceLoader());
    resourceLoaders.push_back(new MaterialResourceLoader());
    resourceLoaders.push_back(new FontResourceLoader());
    resourceLoaders.push_back(new MeshResourceLoader());
    resourceLoaders.push_back(new ScriptResourceLoader());
}

ResourceManager::~ResourceManager() {
    for(int i=0; i < resourceLoaders.size(); i++)	{
        delete resourceLoaders[i];
    }
    
    for(int i=0; i < pools.size(); i++)	{
        delete pools[i];
    }
    pools.clear();
}

void ResourcePool::Update(int elapsed) {
	if(!reloadResourcesOnModify)
		return;
    
	ticksSinceCheck += elapsed;
	if(ticksSinceCheck > RESOURCE_CHECK_INTERVAL) {
		ticksSinceCheck = 0;
		checkForChangedFiles();
	}
}

void ResourceManager::addResourceLoader(ResourceLoader *loader) {
    resourceLoaders.push_back(loader);
}

ResourceLoader *ResourceManager::getResourceLoaderForExtension(const String &extension) {
    for(int i=0; i < resourceLoaders.size(); i++) {
        if(resourceLoaders[i]->canHandleExtension(extension)) {
            return resourceLoaders[i];
        }
    }
    return NULL;
}

void ResourceManager::removeResourceLoader(ResourceLoader *loader) {
    for(int i=0; i < resourceLoaders.size(); i++) {
        if(resourceLoaders[i] == loader) {
            delete resourceLoaders[i];
            resourceLoaders.erase(resourceLoaders.begin() + i);
            return;
        }
    }
}

unsigned int ResourceManager::getNumResourceLoaders() {
    return resourceLoaders.size();
}

ResourceLoader *ResourceManager::getResourceLoaderAtIndex(unsigned int index) {
    if(index <= resourceLoaders.size()) {
        return resourceLoaders[index];
    } else {
        return NULL;
    }
}


MaterialResourceLoader::MaterialResourceLoader() {
    extensions.push_back("mat");
}

Resource *MaterialResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    Services()->getMaterialManager()->loadMaterialLibraryIntoPool(targetPool, path);
    return NULL;
}

ProgramResourceLoader::ProgramResourceLoader() {
    extensions.push_back("frag");
    extensions.push_back("vert");
}

Resource *ProgramResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    ShaderProgram *newProgram = Services()->getMaterialManager()->createProgramFromFile(path);
    return newProgram;
}

duk_ret_t entity_Roll(duk_context *context) {
    Entity *entity = (Entity*)duk_to_pointer(context, 0);
    Number amt = duk_to_number(context, 1);
    entity->Roll(amt);
    return 0;
}

static int customError(lua_State *L) {
    std::vector<DebugBackTraceEntry> backTrace;
    lua_Debug entry;
    int depth = 0;
    while (lua_getstack(L, depth, &entry)) {
        lua_getinfo(L, "Sln", &entry);
        
        std::vector<String> bits = String(entry.short_src).split("\"");
        if(bits.size() > 1) {
            String fileName = bits[1];
            if(fileName != "class.lua") {
                
                DebugBackTraceEntry trace;
                trace.lineNumber = entry.currentline;
                trace.fileName = fileName;
                backTrace.push_back(trace);
            }
        }
        depth++;
    }
    
    // horrible hack to determine the filenames of things
    bool stringThatIsTheMainFileSet = false;
    String stringThatIsTheMainFile;
    
    if(backTrace.size() == 0) {
        DebugBackTraceEntry trace;
        trace.lineNumber = 0;
        trace.fileName = "TODO: Figure out full pathHere";
        backTrace.push_back(trace);
        
    } else {
        stringThatIsTheMainFileSet = true;
        stringThatIsTheMainFile = backTrace[backTrace.size()-1].fileName;
        backTrace[backTrace.size()-1].fileName = "TODO: Figure out full pathHere";
    }
    
    if(stringThatIsTheMainFileSet) {
        for(int i=0; i < backTrace.size(); i++) {
            if(backTrace[i].fileName == stringThatIsTheMainFile) {
                backTrace[i].fileName = "TODO: Figure out full pathHere";
            }
        }
    }
    
    const char *msg = lua_tostring(L, -1);
    if (msg == NULL) msg = "(error with no message)";
    lua_pop(L, 1);
    printf("%s\n", msg);
    
    return 0;
}

int customLuaLoader(lua_State* pState)
{
    std::string module = lua_tostring(pState, 1);
    
    module += ".lua";
    
    std::string defaultPath = "default/";
    defaultPath.append(module);
    
    const char* fullPath = module.c_str();
    Logger::log("Loading custom class: %s\n", module.c_str());
    
    Polycode::CoreFile *inFile = Services()->getCore()->openFile(module, "r");
    
    if(!inFile) {
        inFile =  Services()->getCore()->openFile(defaultPath, "r");
    }
    
    if(inFile) {
        inFile->seek(0, SEEK_END);
        long progsize = inFile->tell();
        inFile->seek(0, SEEK_SET);
        char *buffer = (char*)malloc(progsize+1);
        memset(buffer, 0, progsize+1);
        inFile->read(buffer, progsize, 1);
        int status = luaL_loadbuffer(pState, (const char*)buffer, progsize, fullPath);
        if(status) {
            const char *msg;
            msg = lua_tostring(pState, -1);
            if (msg == NULL) msg = "(error with no message)";
            Logger::log("status=%d, (%s)\n", status, msg);
            lua_pop(pState, 1);
        }
        free(buffer);
        Services()->getCore()->closeFile(inFile);
    } else {
        std::string err = "\n\tError - Could could not find ";
        err += module;
        err += ".";			
        lua_pushstring(pState, err.c_str());			
    }
    return 1;
}

void ScriptResourceLoader::initLua() {
    luaState =  luaL_newstate();
    luaL_openlibs(luaState);
    luaopen_debug(luaState);
    luaopen_Polycode(luaState);
    
    /* install custom loader function */
    
    lua_getglobal(luaState, "package");
    lua_getfield(luaState, -1, "searchers");
    lua_remove(luaState, -2);
    
    int numLoaders = 0;
    lua_pushnil(luaState);
    while (lua_next(luaState, -2) != 0)
    {
        lua_pop(luaState, 1);
        numLoaders++;
    }
    
    lua_pushinteger(luaState, numLoaders + 1);
    lua_pushcfunction(luaState, customLuaLoader);
    lua_rawset(luaState, -3);
    lua_pop(luaState, 1);
    
    /* install custom error function */
    
    lua_register(luaState, "__customError", customError);
    lua_getglobal(luaState, "__customError");
    int errH = lua_gettop(luaState);
    
    /* require default lua files */
    
    lua_getglobal(luaState, "require");
    lua_pushstring(luaState, "class");
    lua_pcall(luaState, 1, 0, errH);

    lua_getglobal(luaState, "require");
    lua_pushstring(luaState, "Polycode");
    lua_pcall(luaState, 1, 0, errH);
    
    lua_getglobal(luaState, "require");
    lua_pushstring(luaState, "tweens");
    lua_pcall(luaState, 1, 0, errH);
    
    lua_getglobal(luaState, "require");
    lua_pushstring(luaState, "defaults");
    lua_pcall(luaState, 1, 0, errH);
}

void ScriptResourceLoader::initJavascript() {
    duktapeContext = duk_create_heap_default();
    
    duk_push_c_function(duktapeContext, entity_Roll, 2);
    duk_put_global_string(duktapeContext, "entity_Roll");
}

ScriptResourceLoader::ScriptResourceLoader() {
    luaState = NULL;
    duktapeContext = NULL;
    
    extensions.push_back("lua");
    extensions.push_back("js");
}

ScriptResourceLoader::~ScriptResourceLoader() {
    lua_close(luaState);
    duk_destroy_heap(duktapeContext);
}

Resource *ScriptResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    OSFileEntry entry(path, OSFileEntry::TYPE_FILE);
    Script *newScript = NULL;
    if(entry.extension == "lua") {
        if(!luaState) {
            initLua();
        }
        newScript = new LuaScript(luaState, path);
    } else if(entry.extension == "js") {
        if(!duktapeContext) {
            initJavascript();
        }
        newScript = new JSScript(duktapeContext, path);
    }
    return newScript;
}

FontResourceLoader::FontResourceLoader() {
    
    FT_Init_FreeType(&FTLibrary);
    FT_Library_SetLcdFilter(FTLibrary, FT_LCD_FILTER_LIGHT);
    
    extensions.push_back("ttf");
    extensions.push_back("otf");
}

FontResourceLoader::~FontResourceLoader() {
    FT_Done_FreeType(FTLibrary);
}

MeshResourceLoader::MeshResourceLoader() {
    extensions.push_back("mesh");
}

Resource *MeshResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    Mesh *mesh = Services()->getRenderer()->createMesh(path);
    return mesh;
}


Resource *FontResourceLoader::loadResource(const String &path, ResourcePool *targetPool) {
    OSFileEntry entry = OSFileEntry(path, OSFileEntry::TYPE_FILE);
    Font *font = new Font(path, FTLibrary);
    font->setResourceName(entry.nameWithoutExtension);
    return font;
}

void ResourceManager::handleEvent(Event *event) {
	if(event->getEventCode() == Event::RESOURCE_CHANGE_EVENT) {
		dispatchEvent(new Event(), Event::CHANGE_EVENT);	
	}
}

ResourcePool *ResourceManager::getGlobalPool() {
    return globalPool;
}

void ResourceManager::Update(int elapsed) {
    globalPool->Update(elapsed);
    for(int i=0; i < pools.size(); i++) {
        pools[i]->Update(elapsed);
    }
}

void ResourceManager::removeResource(Resource *resource) {
    globalPool->removeResource(resource);
    for(int i=0; i < pools.size(); i++) {
        pools[i]->removeResource(resource);
    }
}

void ResourceManager::addResourcePool(ResourcePool *pool) {
    pools.push_back(pool);
}

ResourcePool *ResourceManager::getResourcePoolByName(const String &name) {
    printf("request resource pool [%s]\n", name.c_str());
    for(int i=0; i < pools.size(); i++) {
        if(pools[i]->getName() == name) {
            return pools[i];
        }
    }
    printf("resource pool not found!\n");
    return NULL;
}

void ResourceManager::removeResourcePool(ResourcePool *pool) {
    for(int i=0; i < pools.size(); i++) {
        if(pools[i] == pool) {
            pools.erase(pools.begin()+i);
            return;
        }
    }
}

void ResourceManager::subscribeToResourcePool(ResourcePool *pool) {
    pool->resourceSubscribers++;
}

void ResourceManager::unsubscibeFromResourcePool(ResourcePool *pool) {
    pool->resourceSubscribers--;
    if(pool->deleteOnUnsubscribe && pool->resourceSubscribers < 1) {
        delete pool;
    }
}

std::vector<Resource*> ResourceManager::getResources(int resourceType) {
	std::vector<Resource*> result;

    std::vector<Resource*> subresult = globalPool->getResources(resourceType);
    result.insert(result.end(), subresult.begin(), subresult.end());
    
	for(int i =0; i < pools.size(); i++) {
        subresult = pools[i]->getResources(resourceType);
        result.insert(result.end(), subresult.begin(), subresult.end());
	}
    
	return result;
}
