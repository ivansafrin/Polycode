/*
 *  PolyConfig.h
 *  Poly
 *
 *  Created by Ivan Safrin on 4/15/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// @package Services

#pragma once

#include "PolyGlobals.h"
#include <string>
#include <vector>
#include "tinyxml.h"
#include "PolyUtil.h"

using std::string;
using std::vector;

namespace Polycode {

	class ConfigEntry {
	public:
		string key;
		string configNamespace;
		float numVal;
		string stringVal;
		bool isString;
	};
	
	class _PolyExport Config {
	public:
		Config();
		~Config();		

		void loadConfig(string configNamespace, string fileName);	
		void saveConfig(string configNamespace, string fileName);
		
		ConfigEntry *getEntry(string configNamespace, string key);
		
		void setStringValue(string configNamespace, string key, string value);
		void setNumericValue(string configNamespace, string key, float value);		
			
		float getNumericValue(string configNamespace, string key);
		string getStringValue(string configNamespace, string key);
		
	private:
		
		vector<ConfigEntry*> entries;
		
	};
}