
#include <Polycode.h>
#include <Awesomium/WebCore.h>

using namespace Polycode;

class PolycodeWebViewEvent : public Event {
	public:
			PolycodeWebViewEvent() : Event() {}
			
			static const int CALLBACK_EVENT = 0;	
			
			String objectName;
			String callbackName;
			std::vector <String> args;

};

class PolycodeWebView : public Awesomium::WebViewListener, public EventDispatcher {
	public:
		PolycodeWebView(unsigned int width, unsigned int height, String url);
		~PolycodeWebView();		
		void Update();
		
		void loadURL(String url);
		
		void Resize(unsigned int width, unsigned int height);
		
		Texture *getRenderTexture();
				
		void mouseMove(Number x, Number y);
		void mouseDown(Number x, Number y);
		void mouseUp(Number x, Number y);
		void keyDown(PolyKEY key);
		
		void injectKey(int keyCode);
		
	// ** The following methods are inherited from WebViewListener:

	virtual void onBeginNavigation(Awesomium::WebView* caller, 
								   const std::string& url, 
								   const std::wstring& frameName) {}
	
	virtual void onBeginLoading(Awesomium::WebView* caller, 
								const std::string& url, 
								const std::wstring& frameName, 
								int statusCode, const std::wstring& mimeType) {}
	
	virtual void onFinishLoading(Awesomium::WebView* caller) {}
	
	virtual void onCallback(Awesomium::WebView* caller, 
							const std::wstring& objectName, 
							const std::wstring& callbackName, 
							const Awesomium::JSArguments& args);
	
	virtual void onReceiveTitle(Awesomium::WebView* caller, 
								const std::wstring& title, 
								const std::wstring& frameName) {}
	
	virtual void onChangeTooltip(Awesomium::WebView* caller, 
								 const std::wstring& tooltip) {}
	
	virtual void onChangeCursor(Awesomium::WebView* caller, 
								Awesomium::CursorType cursor) {}

	virtual void onChangeKeyboardFocus(Awesomium::WebView* caller,
									   bool isFocused) {}
	
	virtual void onChangeTargetURL(Awesomium::WebView* caller, 
								   const std::string& url) {}
	
	virtual void onOpenExternalLink(Awesomium::WebView* caller, 
									const std::string& url, 
									const std::wstring& source) {}

	virtual void onRequestDownload(Awesomium::WebView* caller,
								   const std::string& url) {}
	
	virtual void onWebViewCrashed(Awesomium::WebView* caller) {}
	
	virtual void onPluginCrashed(Awesomium::WebView* caller, 
								 const std::wstring& pluginName) {}
	
	virtual void onRequestMove(Awesomium::WebView* caller, int x, int y) {}
	
	virtual void onGetPageContents(Awesomium::WebView* caller, 
								   const std::string& url, 
								   const std::wstring& contents) {}
	
	virtual void onDOMReady(Awesomium::WebView* caller) {}

	virtual void onRequestFileChooser(Awesomium::WebView* caller,
										  bool selectMultipleFiles,
										  const std::wstring& title,
										  const std::wstring& defaultPath) {}

	virtual void onGetScrollData(Awesomium::WebView* caller,
								 int contentWidth,
								 int contentHeight,
								 int preferredWidth,
								 int scrollX,
								 int scrollY) {}

	virtual void onJavascriptConsoleMessage(Awesomium::WebView* caller,
											const std::wstring& message,
											int lineNumber,
											const std::wstring& source) {}

	virtual void onGetFindResults(Awesomium::WebView* caller,
                                      int requestID,
                                      int numMatches,
                                      const Awesomium::Rect& selection,
                                      int curMatch,
                                      bool finalUpdate) {}

	virtual void onUpdateIME(Awesomium::WebView* caller,
                                 Awesomium::IMEState imeState,
                                 const Awesomium::Rect& caretRect) {}

	virtual void onShowContextMenu(Awesomium::WebView* caller,
                                   int mouseX,
								   int mouseY,
								   Awesomium::MediaType type,
								   int mediaState,
								   const std::string& linkURL,
								   const std::string& srcURL,
								   const std::string& pageURL,
								   const std::string& frameURL,
								   const std::wstring& selectionText,
								   bool isEditable,
								   int editFlags) {}

	virtual void onRequestLogin(Awesomium::WebView* caller,
                                   int requestID,
								   const std::string& requestURL,
								   bool isProxy,
								   const std::wstring& hostAndPort,
								   const std::wstring& scheme,
								   const std::wstring& realm) {}

	virtual void onChangeHistory(Awesomium::WebView* caller,
									int backCount,
									int forwardCount) {}

	virtual void onFinishResize(Awesomium::WebView* caller,
									int width,
									int height) {}

	virtual void onShowJavascriptDialog(Awesomium::WebView* caller,
											int requestID,
											int dialogFlags,
											const std::wstring& message,
											const std::wstring& defaultPrompt,
											const std::string& frameURL) {}	
		
	protected:
	
		int width, height;
	
		Texture *renderTexture;
	
		Awesomium::WebView* webView;
		Awesomium::WebCore* webCore;
};
