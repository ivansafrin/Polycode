
#include "polycode/core/PolyUWPCore.h"
#include <ppltasks.h>

using namespace concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;

UWPCore::UWPCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) 
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

	m_Window = view->window;

	renderer = new Renderer();
	graphicsInterface = new DX11GraphicsInterface();
	renderer->setGraphicsInterface(this, graphicsInterface);
	services->setRenderer(renderer);
	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);
}

UWPCore::~UWPCore() {

}

void UWPCore::Render() {
	renderer->beginFrame();
	services->Render(Polycode::Rectangle(0, 0, 640, 480));
	renderer->endFrame();
}

bool UWPCore::systemUpdate() {
	if (!running) {
		return false;
	}
	doSleep();
	updateCore();
	return running;
}

void UWPCore::setCursor(int cursorType) {

}

void launchThread(Threaded *target) {
	target->runThread();
	target->scheduledForRemoval = true;
}

void UWPCore::createThread(Threaded * target) {
	Core::createThread(target);
	std::thread *thread = new std::thread(launchThread, target);

}

void UWPCore::lockMutex(CoreMutex *mutex) {
	((UWPCoreMutex*)mutex)->mutex.lock();
}

void UWPCore::unlockMutex(CoreMutex *mutex) {
	((UWPCoreMutex*)mutex)->mutex.unlock();
}

CoreMutex *UWPCore::createMutex() {
	UWPCoreMutex *mutex = new UWPCoreMutex();
	return mutex;
}

void UWPCore::copyStringToClipboard(const String& str) {

}

String UWPCore::getClipboardString() {
	return "";
}

void UWPCore::createFolder(const String& folderPath) {

}

void UWPCore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void UWPCore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void UWPCore::removeDiskItem(const String& itemPath) {

}

String UWPCore::openFolderPicker() {
	return "";
}

std::vector<String> UWPCore::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	std::vector<String> ret;
	return ret;
}

String UWPCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
	return "";
}

void UWPCore::handleVideoModeChange(VideoModeChangeInfo *modeInfo) {
	
	if (m_d3dContext == nullptr) {
		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		HRESULT hr = D3D11CreateDevice(
			nullptr,					// Specify nullptr to use the default adapter.
			D3D_DRIVER_TYPE_HARDWARE,	// Create a device using the hardware graphics driver.
			0,							// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			0,				// Set debug and Direct2D compatibility flags.
			featureLevels,				// List of feature levels this app can support.
			ARRAYSIZE(featureLevels),	// Size of the list above.
			D3D11_SDK_VERSION,			// Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&device,					// Returns the Direct3D device created.
			&m_d3dFeatureLevel,			// Returns feature level of device created.
			&context					// Returns the device immediate context.
			);

		if (FAILED(hr)) {
			D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
				0,
				0,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&device,
				&m_d3dFeatureLevel,
				&context
				);
		}

		device.As(&m_d3dDevice);
		context.As(&m_d3dContext);
	}

	// ---------------- window stuff

	// Clear the previous window size specific context.
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
	m_d3dRenderTargetView = nullptr;
	m_d3dDepthStencilView = nullptr;
	m_d3dContext->Flush();


	if (m_swapChain != nullptr) {
		HRESULT hr = m_swapChain->ResizeBuffers(
			2,
			modeInfo->xRes,
			modeInfo->yRes,
			DXGI_FORMAT_B8G8R8A8_UNORM,
			0
			);
	} else {
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

		swapChainDesc.Width = lround(modeInfo->xRes);
		swapChainDesc.Height = lround(modeInfo->yRes);
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // This is the most common swap chain format.
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1; // Don't use multi-sampling.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2; // Use double-buffering to minimize latency.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // All Windows Store apps must use this SwapEffect.
		swapChainDesc.Flags = 0;
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		// This sequence obtains the DXGI factory that was used to create the Direct3D device above.
		ComPtr<IDXGIDevice3> dxgiDevice;
		m_d3dDevice.As(&dxgiDevice);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		ComPtr<IDXGIFactory2> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		dxgiFactory->CreateSwapChainForCoreWindow(
			m_d3dDevice.Get(),
			m_Window,
			&swapChainDesc,
			nullptr,
			&m_swapChain
			);

		dxgiDevice->SetMaximumFrameLatency(1);
	}


	// Create a render target view of the swap chain back buffer.
	ComPtr<ID3D11Texture2D> backBuffer;
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	m_d3dDevice->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			&m_d3dRenderTargetView
		);

	// Create a depth stencil view for use with 3D rendering if needed.
	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		modeInfo->xRes,
		modeInfo->yRes,
		1, // This depth stencil view has only one texture.
		1, // Use a single mipmap level.
		D3D11_BIND_DEPTH_STENCIL
		);

	ComPtr<ID3D11Texture2D> depthStencil;
	m_d3dDevice->CreateTexture2D(
		&depthStencilDesc,
		nullptr,
		&depthStencil
		);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	m_d3dDevice->CreateDepthStencilView(
		depthStencil.Get(),
		&depthStencilViewDesc,
		&m_d3dDepthStencilView
		);

	// Set the 3D rendering viewport to target the entire window.
	CD3D11_VIEWPORT m_screenViewport = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		modeInfo->xRes,
		modeInfo->yRes
		);

	m_d3dContext->RSSetViewports(1, &m_screenViewport);

	graphicsInterface->setContext(m_d3dContext.Get());
	graphicsInterface->setViews(m_d3dRenderTargetView.Get(), m_d3dDepthStencilView.Get());

}

void UWPCore::flushRenderContext() {
	HRESULT hr = m_swapChain->Present(1, 0);
	m_d3dContext->DiscardView(m_d3dRenderTargetView.Get());
	m_d3dContext->DiscardView(m_d3dDepthStencilView.Get());
}

void UWPCore::resizeTo(int xRes, int yRes) {

}

void UWPCore::openURL(String url) {

}

unsigned int UWPCore::getTicks() {
	return 0;
}

String UWPCore::executeExternalCommand(String command, String args, String inDirectory) {
	return "";
}

bool UWPCore::systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {

	
	return false;
}

void Core::getScreenInfo(int *width, int *height, int *hz) {

}