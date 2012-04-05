
#include "PolycodeWebView.h"

PolycodeWebView::PolycodeWebView(unsigned int width, unsigned int height, String url) {

	this->width = width;
	this->height = height;

	char *testData = (char*)malloc(width*height*4);
	renderTexture = CoreServices::getInstance()->getMaterialManager()->createTexture(width, height, (char*)testData, false, Image::IMAGE_RGBA);
	delete testData;

	webCore = new Awesomium::WebCore();
	webView = webCore->createWebView(width, height);
	
	webView->loadURL(url.c_str());
	webView->focus();
}

PolycodeWebView::~PolycodeWebView() {
	webView->destroy();
	delete webCore;	
	delete renderTexture;
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

Texture *PolycodeWebView::getRenderTexture() {
	return renderTexture;
}

