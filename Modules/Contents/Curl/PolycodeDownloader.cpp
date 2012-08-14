
#include "PolycodeDownloader.h"

size_t DownloaderCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {

	PolycodeDownloader *downloader = (PolycodeDownloader*) userdata;
	
	size_t newSize = downloader->size + (size*nmemb);
	downloader->data = (char*)realloc((void*)downloader->data, newSize);
	
	memcpy(downloader->data+downloader->size, ptr, (size*nmemb));
	
	downloader->size = newSize;	
	return size * nmemb;
}

String PolycodeDownloader::getDataAsString() {	
	char *ndata = (char*)malloc(size);
	memcpy(ndata, data, size);
	ndata[size-1] = '\0';
	String ret = String(ndata);
	free(ndata);
	return ret;
}
		
PolycodeDownloader::PolycodeDownloader(String url) : Threaded() {
	this->url = url;
	data = (char*)malloc(0);
	size = 0;
}

void PolycodeDownloader::runThread() {
	curl = curl_easy_init();
		
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloaderCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
			
	CURLcode curl_res = curl_easy_perform(curl);
	
	curl_easy_cleanup(curl);	
	
	dispatchEvent(new Event(Event::COMPLETE_EVENT), Event::COMPLETE_EVENT);
}

PolycodeDownloader::~PolycodeDownloader() {
	free(data);
}
