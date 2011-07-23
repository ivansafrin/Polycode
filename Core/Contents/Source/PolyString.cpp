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

#include "PolyString.h"

using namespace Polycode;

String::String() {
	contents = L"";
	s_contents = "";
}

String::String(const wchar_t *str) {
	contents = wstring(str);
}

String::String(const char *str) {
	string sstr = string(str);
	utf8toWStr(contents, sstr);	
//	contents.assign(sstr.begin(), sstr.end());
}

String::String(const wchar_t *str, size_t n) {
	contents = wstring(str, n);
}

String::String(const string& str) {
	contents.assign(str.begin(), str.end());	
}

String::String(const wstring& str) {
	contents = str;
}

String::~String() {
	
}

size_t String::getDataSizeWithEncoding(int encoding) const {
	switch(encoding) {
		case ENCODING_UTF8: {
			string dest;
			wstrToUtf8(dest, contents);
			return dest.size();
		}
		default:
			return NULL;
	}
}

const char *String::getDataWithEncoding(int encoding) const {
	switch(encoding) {
		case ENCODING_UTF8: {
			string dest;
			wstrToUtf8(dest, contents);
			return dest.data();
		}
		break;
		default:
			return NULL;
	}
}

void String::setDataWithEncoding(char *data, int encoding) {
	switch(encoding) {
		case ENCODING_UTF8: {
			string str = string(data);
			utf8toWStr(contents, str);
		}
		default:
			break;
	}
}


vector<String> String::split(const String &delim) const {
	
	vector<String> tokens;
	bool trimEmpty = false;
	
		std::wstring::size_type pos, lastPos = 0;
		while(true)
		{
			pos = contents.find_first_of(delim.contents, lastPos);
			if(pos == std::wstring::npos)
			{
				pos = contents.length();
				
				if(pos != lastPos || !trimEmpty)
					tokens.push_back(vector<String>::value_type(contents.data()+lastPos, (wstring::size_type)pos-lastPos ));
				
				break;
			}
			else
			{
				if(pos != lastPos || !trimEmpty)
					tokens.push_back(vector<String>::value_type(contents.data()+lastPos, (wstring::size_type)pos-lastPos ));
			}
			
			lastPos = pos + 1;
		}	
	
	return tokens;
}

String String::replace(const String &what, const String &withWhat) const {
	vector<String> arr = split(what);
	String retString = "";
	for(int i= 0; i < arr.size(); i++) {
		retString += arr[i];
		if(i < arr.size()-1)
			retString += withWhat;
	}
	
	return retString;
}

String String::toLowerCase() const {
	wstring str = contents;
	std::transform(str.begin(), str.end(), str.begin(),::tolower);	
	return String(str);
}

String String::toUpperCase() const {
	wstring str = contents;
	std::transform(str.begin(), str.end(), str.begin(),::toupper);	
	return String(str);
}


String String::NumberToString(Number value) {
	char temp[128];
	sprintf(temp, "%f", value);
	return String(temp);
}


const string& String::getSTLString() {
	s_contents.assign(contents.begin(),contents.end());
	return s_contents;
}

const wstring& String::getSTLWString() const {
	return contents;
}

const char *String::c_str() {
	s_contents.assign(contents.begin(),contents.end());	
	return s_contents.c_str();
}

const wchar_t *String::wc_str() const {
	return contents.c_str();
}


void utf8toWStr(WStr& dest, const Str& src){
	dest.clear();
	wchar_t w = 0;
	int bytes = 0;
	wchar_t err = L'�';
	for (size_t i = 0; i < src.size(); i++){
		unsigned char c = (unsigned char)src[i];
		if (c <= 0x7f){//first byte
			if (bytes){
				dest.push_back(err);
				bytes = 0;
			}
			dest.push_back((wchar_t)c);
		}
		else if (c <= 0xbf){//second/third/etc byte
			if (bytes){
				w = ((w << 6)|(c & 0x3f));
				bytes--;
				if (bytes == 0)
					dest.push_back(w);
			}
			else
				dest.push_back(err);
		}
		else if (c <= 0xdf){//2byte sequence start
			bytes = 1;
			w = c & 0x1f;
		}
		else if (c <= 0xef){//3byte sequence start
			bytes = 2;
			w = c & 0x0f;
		}
		else if (c <= 0xf7){//3byte sequence start
			bytes = 3;
			w = c & 0x07;
		}
		else{
			dest.push_back(err);
			bytes = 0;
		}
	}
	if (bytes)
		dest.push_back(err);
}

void wstrToUtf8(Str& dest, const WStr& src){
	dest.clear();
	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff){
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff){
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0x10ffff){
			dest.push_back(0xf0 | ((w >> 18)& 0x07));
			dest.push_back(0x80| ((w >> 12) & 0x3f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}
