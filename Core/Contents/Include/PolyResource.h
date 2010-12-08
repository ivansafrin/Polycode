/*
 *  PolyResource.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/19/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package BasicTypes

#pragma once
#include "PolyGlobals.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace Polycode {
	class _PolyExport Resource {
		public:
			Resource(int type);
			virtual ~Resource();
			
			string getResourceName();
			int getResourceType();
			void setResourceName(string newName);
			void setResourcePath(string path);
			string getResourcePath();		

			static const int RESOURCE_TEXTURE = 0;
			static const int RESOURCE_MATERIAL = 1;
			static const int RESOURCE_SHADER = 2;
			static const int RESOURCE_PROGRAM = 3;
			static const int RESOURCE_MESH = 5;
			static const int RESOURCE_CUBEMAP = 6;				
			
		protected:
			
			int type;
			string resourcePath;
			string name;
	
					
	};
}