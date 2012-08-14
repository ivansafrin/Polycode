#pragma once

#include <Polycode.h>
#include <curl/curl.h>

using namespace Polycode;

class PolycodeDownloader : public Threaded {
	public:
		PolycodeDownloader(String url);
		~PolycodeDownloader();		
		
		void runThread();
		
		String getDataAsString();
		
		char *data;
		size_t size;
				
	protected:
		String url;		
		CURL *curl;
};