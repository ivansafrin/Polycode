/*
 *  PolyConfig.h
 *  Poly
 *
 *  Created by Ivan Safrin on 4/15/09.
 *  Copyright 2009 Ivan Safrin. All rights reserved.
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
		Number numVal;
		String stringVal;
		bool isString;
	};
	
	/**
	* Saves and loads simple config files. Config stores, loads and saves string and number values associated by string keys. You can use to easily save and load settings and preferences and other data. Configs are separated by namespaces, so you can have multiple configs with the same keys.
	*/
	class _PolyExport Config {
	public:
		/**
		* Default constructor.
		*/ 
		Config();
		~Config();		

		/**
		* Load config from a specified file into the specified namespace.
		* @param configNamespace Namespace of the config to load data into.
		* @param fileName Path to the file to load.
		*/
		void loadConfig(String configNamespace, String fileName);	
		
		/**
		* Save config to a specified file from the specified namespace.
		* @param configNamespace Namespace of the config to save data from.
		* @param fileName Path to the file to save data to.
		*/		
		void saveConfig(String configNamespace, String fileName);

		ConfigEntry *getEntry(String configNamespace, String key);

		/**
		* Sets a string value into the specified config namespace.
		* @param configNamespace Namespace to set value in.
		* @param key String key of the value.
		* @param value The string value to save.
		*/
		void setStringValue(String configNamespace, String key, String value);
		
		/**
		* Sets a numeric value into the specified config namespace.
		* @param configNamespace Namespace to set value in.
		* @param key String key of the value.
		* @param value The numeric value to save.
		*/		
		void setNumericValue(String configNamespace, String key, Number value);		
		
		/**
		* Returns a numeric value by a string key.
		* @param configNamespace Namespace to get the value from.
		* @param key String key of the value.
		*/				
		Number getNumericValue(String configNamespace, String key);
		
		/**
		* Returns a string value by a string key.
		* @param configNamespace Namespace to get the value from.
		* @param key String key of the value.
		*/						
		String getStringValue(String configNamespace, String key);
		
	private:
		
		vector<ConfigEntry*> entries;
		
	};
}