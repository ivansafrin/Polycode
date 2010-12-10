
#pragma once

#include "PolyGlobals.h"
#include <string>
#include <vector>

using std::vector;

using namespace std;

typedef std::string Str;
typedef std::wstring WStr;

void utf8toWStr(WStr& dest, const Str& src);
void wstrToUtf8(Str& dest, const WStr& src);	

namespace Polycode {

	class _PolyExport String {
		public:
			String();
			String(const wchar_t *str);
			String(const wchar_t *str, size_t n);		
			String(const char *str);
			String(string str);
			String(wstring str);
		
			virtual ~String();
		
			size_t size() { return contents.size(); }
			size_t length() { return contents.size(); }
		
			string getSTLString();
			wstring getSTLWString();
		
			String substr(size_t pos = 0, size_t n = wstring::npos) const { return String(contents.substr(pos,n)); }
		
			size_t rfind ( const String &str, size_t pos = wstring::npos ) const { return contents.rfind(str.contents, pos); }
			size_t find ( const String &str, size_t pos = 0 ) const { return contents.find(str.contents, pos); }

			inline String operator + (const char *str) const { return String(contents + String(str).contents); }
		
			inline String operator + (const String &str) const { return String(contents + str.contents); }
		
			String operator += (const String &str) { contents = contents + str.contents; return *this; }		
			String operator = (const String &str) {  contents = str.contents; return *this;}
		
		
			inline bool operator == (const String &str) const {  return (str.contents == contents); }		
			inline bool operator != (const String &str) const {  return (str.contents != contents); }		
		
			String toLowerCase();
		
			inline wchar_t operator [] ( const size_t i ) const { return contents[i]; }
		
			vector<String> split(const String &delims);
			String replace(const String &what, const String &withWhat);
			
			static String floatToString(float value);
		
			const char *c_str();
			const wchar_t *wc_str();
		
			const wchar_t *data(){ return contents.data(); }

			const char *getDataWithEncoding(int encoding);
			void setDataWithEncoding(char *data, int encoding);	
			size_t getDataSizeWithEncoding(int encoding);
		
			wstring contents;	
			string s_contents;
		
			static const int ENCODING_UTF8 = 0; 
			
		
		private:
		
	};

	static inline String operator+ (const char *str, const String &rstr) { return String(String(str).contents + rstr.contents); }
	static inline String operator+ (const wchar_t *str, const String &rstr) { return String(String(str).contents + rstr.contents); }	
	static inline String operator+ (const wchar_t str, const String &rstr) { wstring tmp=L" "; tmp[0] = str; return String(tmp + rstr.contents); }		
}
