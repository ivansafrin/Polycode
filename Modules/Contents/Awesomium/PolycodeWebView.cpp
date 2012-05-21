
#include "PolycodeWebView.h"

PolycodeWebView::PolycodeWebView(unsigned int width, unsigned int height, String url) : Awesomium::WebViewListener(), EventDispatcher() {

	this->width = width;
	this->height = height;

	char *testData = (char*)malloc(width*height*4);
	renderTexture = CoreServices::getInstance()->getMaterialManager()->createTexture(width, height, (char*)testData, false, Image::IMAGE_RGBA);
	delete testData;

	webCore = new Awesomium::WebCore();
	webView = webCore->createWebView(width, height);
	
	webView->setListener(this);
	
	webView->createObject(L"Polycode");
	webView->setObjectCallback(L"Polycode", L"showNotice");
	webView->setObjectCallback(L"Polycode", L"showGlowAreas");
	
	webView->loadURL(url.c_str());
	webView->focus();
}

void PolycodeWebView::onCallback(Awesomium::WebView* caller, 
							const std::wstring& objectName, 
							const std::wstring& callbackName, 
							const Awesomium::JSArguments& args) {

	PolycodeWebViewEvent *event = new PolycodeWebViewEvent();
	event->objectName = objectName;
	event->callbackName = callbackName;
	
	for(int i=0; i < args.size(); i++) {
		event->args.push_back(String(args[i].toString()));
	}
	
	dispatchEvent(event, PolycodeWebViewEvent::CALLBACK_EVENT);
}



void PolycodeWebView::Resize(unsigned int width, unsigned int height) {
	webView->resize(width, height);
	this->width = width;
	this->height = height;
}


PolycodeWebView::~PolycodeWebView() {
	webView->destroy();
	delete webCore;	
	delete renderTexture;
}

void PolycodeWebView::loadURL(String url) {
	webView->loadURL(url.c_str());
}

void PolycodeWebView::Update() {
	webCore->update();
	if(webView->isDirty()) {
		const Awesomium::RenderBuffer* renderBuffer = webView->render();
		if(renderBuffer) {		
			char *dest = (char*)malloc(width*height*4);	
			renderBuffer->copyTo((unsigned char*)dest, width * 4, 4, true, true);
		
			Image *newImage = new Image(dest, width, height, Image::IMAGE_RGBA);
			renderTexture->setImageData(newImage);
			renderTexture->recreateFromImageData();
			delete newImage;				
			delete dest;
		}
	}
}

void PolycodeWebView::mouseMove(Number x, Number y) {
	webView->injectMouseMove(x, y);
}

void PolycodeWebView::mouseDown(Number x, Number y) {
	webView->injectMouseDown(Awesomium::LEFT_MOUSE_BTN);
}

void PolycodeWebView::mouseUp(Number x, Number y) {
	webView->injectMouseUp(Awesomium::LEFT_MOUSE_BTN);
}

void PolycodeWebView::injectKey(int keyCode) {
	Awesomium::WebKeyboardEvent keyEvent;

	char* buf = new char[20];
	keyEvent.virtualKeyCode = keyCode;
	Awesomium::getKeyIdentifierFromVirtualKeyCode(keyEvent.virtualKeyCode, 
												  &buf);
	strcpy(keyEvent.keyIdentifier, buf);
	delete[] buf;
	
	keyEvent.modifiers = 0;
	keyEvent.nativeKeyCode = 0;
	keyEvent.type = Awesomium::WebKeyboardEvent::TYPE_KEY_DOWN;

	webView->injectKeyboardEvent(keyEvent);

	keyEvent.type = Awesomium::WebKeyboardEvent::TYPE_KEY_UP;

	webView->injectKeyboardEvent(keyEvent);
}

void PolycodeWebView::keyDown(PolyKEY key) {
	injectKey(key);
}


Texture *PolycodeWebView::getRenderTexture() {
	return renderTexture;
}

