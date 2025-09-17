#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "ole32.lib")

#include "CommonInclude.h"

namespace Source::Graphics
{
    class GraphicDevice
    {
    public:
        GraphicDevice();
        ~GraphicDevice();

        HRESULT Initialize(HWND hwnd, UINT width, UINT height);
        
        void BeginDraw(D2D1_COLOR_F clearColor);
        HRESULT EndDraw();

        void OnResize(UINT width, UINT height);

        ID2D1HwndRenderTarget* GetRenderTarget() const { return _renderTarget; }
        IWICImagingFactory* GetWICFactory() const { return _wicFactory; }
        IDWriteFactory* GetDWriteFactory() const { return _writeFactory; }
    private:
        HWND _hWnd;

        ID2D1Factory* _d2dFactory;
        ID2D1HwndRenderTarget* _renderTarget;
        IWICImagingFactory* _wicFactory;
        IDWriteFactory* _writeFactory;

        HRESULT CreateDeviceResources();
        void DiscardDeviceResources();

    };
}