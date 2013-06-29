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

#pragma once
#include "PolyGlobals.h"
#include "PolyString.h"

namespace Polycode {

class ConfigEntry : public PolyBase {
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
class _PolyExport Config : public PolyBase {
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
		void loadConfig(const String& configNamespace, const String& fileName);

		/**
		* Save config to a specified file from the specified namespace.
		* @param configNamespace Namespace of the config to save data from.
		* @param fileName Path to the file to save data to.
		*/
		void saveConfig(const String& configNamespace, const String& fileName);

		ConfigEntry *getEntry(const String& configNamespace, const String& key);

		/**
		* Sets a string value into the specified config namespace.
		* @param configNamespace Namespace to set value in.
		* @param key String key of the value.
		* @param value The string value to save.
		*/
		void setStringValue(const String& configNamespace, const String& key, const String& value);

		/**
		* Sets a numeric value into the specified config namespace.
		* @param configNamespace Namespace to set value in.
		* @param key String key of the value.
		* @param value The numeric value to save.
		*/
		void setNumericValue(const String& configNamespace, const String& key, Number value);

		/**
		* Returns a numeric value by a string key.
		* @param configNamespace Namespace to get the value from.
		* @param key String key of the value.
		*/
		Number getNumericValue(const String& configNamespace, const String& key);

		/**
		* Returns a string value by a string key.
		* @param configNamespace Namespace to get the value from.
		* @param key String key of the value.
		*/
		const String& getStringValue(const String& configNamespace, const String& key);

	private:

		std::vector<ConfigEntry*> entries;

};
}
