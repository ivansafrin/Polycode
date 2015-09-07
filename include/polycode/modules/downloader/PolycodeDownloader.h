#pragma once

#include <Polycode.h>
#include <curl/curl.h>

using namespace Polycode;

class PolycodeDownloader : public Threaded {
	public:
		PolycodeDownloader(String url);
		virtual ~PolycodeDownloader();		
		
		void runThread();
		
		String getDataAsString();
		
		bool writeToFile(String fileName);
		
		char *data;
		size_t size;
		
		bool returned;
		
		void *userData;
		
	protected:
		String url;		
		CURL *curl;
};