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

	/**
	* Stores, saves and loads data. This class can save and load arbitrary data to and from disk and convert it to strings.
	*/	
	class _PolyExport Data : public PolyBase {
		public:
			/**
			* Default constructor
			*/
			Data();
			~Data();
		
		/**
		* Loads data from a file.
		* @param fileName Path to the file to load data from.
		* @return True if susccessful, false if not
		*/						
		bool loadFromFile(const String& fileName);
		
		/**
		* Retuns data as a string with the specified encoding.
		* @param encoding The encoding to use. Currently only supports String::ENCODING_UTF8
		* @return String of the specified encoding.
		*/						
		String getAsString(int encoding) const;

		/**
		* Sets the data from a string with the specified encoding.
		* @param str The string to create the data from.
		* @param encoding The encoding to use. Currently only supports String::ENCODING_UTF8
		*/								
		void setFromString(const String& str, int encoding);
		
		/**
		* Saves the data to a file.
		* @param fileName Path to the file to save data to.
		* @return Returns true if successful or false if otherwise.
		*/								
		bool saveToFile(const String& fileName) const;
		
		/**
		* Returns pointer to the data.
		* @return Pointer to the data buffer.
		*/										
		char *getData() const { return data; }
				
		protected:

			long dataSize;
			char *data;
		
	};

}
