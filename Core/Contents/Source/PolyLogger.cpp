
#include "PolyLogger.h"

using namespace Polycode;

void Logger::logw(const char *str) {
	std::wcout << str << std::endl;
}

void Logger::log(const char *format, ...) {
	va_list args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);

#ifdef MSVC
#ifdef _DEBUG
	
	char buffer[4096];
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	WCHAR wbuf[4096];
	int i = 0;
	while(buffer[i] != '\0') {
		wbuf[i] = (WCHAR)buffer[i];
		++i;
	}
	wbuf[i] = L'\0';
	OutputDebugString(wbuf);
	
#endif
#endif

}