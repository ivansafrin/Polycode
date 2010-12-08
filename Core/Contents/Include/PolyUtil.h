/*
 *  PolyUtil.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/23/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Services

#pragma once

#include "PolyGlobals.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using std::string;
using std::vector;

namespace Polycode {

	class _PolyExport StringUtil {
		public:
			static string toLowerCase(const std::string &str);
			static vector<std::string> split(const std::string &str, const std::string &delims);
			static string replace(const std::string &str, const std::string &what, const std::string &withWhat);
			static string floatToString(float value);
	};
}