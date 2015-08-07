
#include "polycode/core/PolyCoreFileProvider.h"

using namespace Polycode;

CoreFileProvider::CoreFileProvider() {
    canListFiles = false;
}

OSFileEntry::OSFileEntry(const Polycode::String& fullPath, int type) {
    std::vector<String> parts = fullPath.split("/");
    
    if(parts.size() > 1) {
        String path = parts[0];
        
        if(parts.size() > 1) {
            for(int i=1; i < parts.size()-1; i++) {
                path += "/" + parts[i];
            }
            init(path, parts[parts.size()-1], type);
        }
    } else {
        init("", fullPath, type);
    }
    
}

OSFileEntry::OSFileEntry(const String& path, const String& name, int type) {
    init(path, name, type);
}

void OSFileEntry::init(const Polycode::String& path, const Polycode::String& name, int type) {
    this->basePath = path;
    
    if(path == "") {
        this->fullPath = name;
    } else if(path == "/") {
        this->fullPath = "/" + name;
    } else {
        this->fullPath = path + "/" + name;
    }
    this->name = name;
    this->type = type;
    
    size_t found;
    found=this->name.rfind(".");
    if (found != -1) {
        extension = this->name.substr(found+1);
        nameWithoutExtension = this->name.substr(0, found);
    } else {
        extension = "";
        nameWithoutExtension = name;
    }
}

bool CoreFileProvider::parseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {
    return false;
}