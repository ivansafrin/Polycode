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
#include "PolyString.h"
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
		String key;
		String configNamespace;
		float numVal;
		String stringVal;
		bool isString;
	};
	
	class _PolyExport Config {
	public:
		Config();
		~Config();		

		void loadConfig(String configNamespace, String fileName);	
		void saveConfig(String configNamespace, String fileName);
		
		ConfigEntry *getEntry(String configNamespace, String key);
		
		void setStringValue(String configNamespace, String key, String value);
		void setNumericValue(String configNamespace, String key, float value);		
			
		float getNumericValue(String configNamespace, String key);
		String getStringValue(String configNamespace, String key);
		
	private:
		
		vector<ConfigEntry*> entries;
		
	};
}