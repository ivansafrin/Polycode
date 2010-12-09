
#include "PolyString.h"

using namespace Polycode;

String::String() {
	
}

String::String(const wchar_t *str) {
	contents = wstring(str);
}

String::String(const char *str) {
	string sstr = string(str);
	contents.assign(sstr.begin(), sstr.end());
}

String::String(string str) {
	contents.assign(str.begin(), str.end());	
}

String::String(wstring str) {
	contents = str;
}

String::~String() {
	
}


vector<String> String::split(const String &delims) {
	wstring::size_type lastPos = contents.find_first_not_of(delims.contents, 0);
	wstring::size_type pos     = contents.find_first_of(delims.contents, lastPos);
	
	vector<String> tokens;
	
	while (wstring::npos != pos || wstring::npos != lastPos) {
		tokens.push_back(String(contents.substr(lastPos, pos - lastPos)));
		lastPos = contents.find_first_not_of(delims.contents, pos);
		pos = contents.find_first_of(delims.contents, lastPos);
    }
	
	return tokens;
}

String String::replace(const String &what, const String &withWhat) {
	vector<String> arr = split(what);
	String retString = "";
	for(int i= 0; i < arr.size(); i++) {
		retString += arr[i];
		if(i < arr.size()-1)
			retString += withWhat;
	}
	
	return retString;
}

String String::toLowerCase() {
	wstring str = contents;
	std::transform(str.begin(), str.end(), str.begin(),std::tolower);	
	return String(str);
}

String String::floatToString(float value) {
	char temp[128];
	sprintf(temp, "%f", value);
	return String(temp);
}


string String::getSTLString() {
	s_contents.assign(contents.begin(),contents.end());
	return s_contents;
}

wstring String::getSTLWString() {
	return contents;
}

const char *String::c_str() {
	s_contents.assign(contents.begin(),contents.end());	
	return s_contents.c_str();
}

const wchar_t *String::wc_str() {
	return contents.c_str();
}