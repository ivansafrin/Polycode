
#include <Polycode.h>
#include <Awesomium/WebCore.h>

using namespace Polycode;

class PolycodeWebView {
	public:
		PolycodeWebView(unsigned int width, unsigned int height, String url);
		~PolycodeWebView();		
		void Update();
		
		Texture *getRenderTexture();
		
	protected:
	
		int width, height;
	
		Texture *renderTexture;
	
		Awesomium::WebView* webView;
		Awesomium::WebCore* webCore;
};
