
#pragma once

#include "PolyCore.h"
#include "polycode/core/PolyDX11GraphicsInterface.h"

#include <wrl.h>
#include <wrl/client.h>
#include <d3d11_2.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <concrt.h>

#include <ppltasks.h>

using namespace concurrency;
using namespace Polycode;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;


#define POLYCODE_CORE UWPCore

class PolycodeView {
	public:
		IUnknown *window;
};

class UWPCoreMutex : public CoreMutex {
	public:
		std::mutex mutex;
};


class _PolyExport UWPCore : public Core {
	public:
	
		UWPCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex = -1, bool retinaSupport = false);
		~UWPCore();

		void Render();
		bool systemUpdate();
		void setCursor(int cursorType);
		void createThread(Threaded *target);
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();
		void copyStringToClipboard(const String& str);
		String getClipboardString();
		void createFolder(const String& folderPath);
		void copyDiskItem(const String& itemPath, const String& destItemPath);
		void moveDiskItem(const String& itemPath, const String& destItemPath);
		void removeDiskItem(const String& itemPath);
		String openFolderPicker();
		std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple);
		String saveFilePicker(std::vector<CoreFileExtension> extensions);
		void handleVideoModeChange(VideoModeChangeInfo *modeInfo);
		void flushRenderContext();
		void resizeTo(int xRes, int yRes);
		void openURL(String url);
		unsigned int getTicks();
		String executeExternalCommand(String command, String args, String inDirectory);
		bool systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector);

	

	private:

		DX11GraphicsInterface *graphicsInterface;


		D3D_FEATURE_LEVEL								m_d3dFeatureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device2>			m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext2>	m_d3dContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain1>			m_swapChain;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_d3dRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_d3dDepthStencilView;

		IUnknown *m_Window;

};