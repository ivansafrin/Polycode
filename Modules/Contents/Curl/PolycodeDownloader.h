
#include <Polycode.h>
#include <curl/curl.h>

using namespace Polycode;

class PolycodeDownloader : public EventDispatcher {
	public:
		PolycodeDownloader(String url);
		~PolycodeDownloader();		
		
		String getDataAsString();
		
		char *data;
		size_t size;
				
	protected:
		
		CURL *curl;
};