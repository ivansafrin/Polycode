/*
 *  PolyUtil.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/23/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyUtil.h"

using namespace Polycode;

vector<std::string> StringUtil::split(const std::string &str, const std::string &delims) {
	string::size_type lastPos = str.find_first_not_of(delims, 0);
	string::size_type pos     = str.find_first_of(delims, lastPos);
	
	vector<string> tokens;
	
	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delims, pos);
		pos = str.find_first_of(delims, lastPos);
    }
	
	return tokens;
}

string StringUtil::replace(const std::string &str, const std::string &what, const std::string &withWhat) {
	vector<std::string> arr = StringUtil::split(str, what);
	string retString = "";
	for(int i= 0; i < arr.size(); i++) {
		retString += arr[i];
		if(i < arr.size()-1)
			retString += withWhat;
	}
		
	return retString;
}

string StringUtil::toLowerCase(const std::string &str) {
	string retString = str;
	std::transform(retString.begin(), retString.end(), retString.begin(),std::tolower);	
	return retString;
}

string StringUtil::floatToString(float value) {
	char temp[128];
	sprintf(temp, "%f", value);
	return string(temp);
}