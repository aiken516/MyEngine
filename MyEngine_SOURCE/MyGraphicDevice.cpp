#include "MyGraphicDevice.h"

namespace Source::Graphics
{
	GraphicDevice::GraphicDevice() : 
		_hWnd(nullptr),
		_d2dFactory(nullptr),
		_renderTarget(nullptr),
		_wicFactory(nullptr),
		_writeFactory(nullptr)
	{
	}

	GraphicDevice::~GraphicDevice()
	{
        DiscardDeviceResources();

        if (_d2dFactory)
        {
            _d2dFactory->Release();
        }
        if (_wicFactory)
        {
            _wicFactory->Release();
        }
        if (_writeFactory)
        {
            _writeFactory->Release();
        }

        _d2dFactory = nullptr;
        _wicFactory = nullptr;
        _writeFactory = nullptr;
	}

    HRESULT GraphicDevice::Initialize(HWND hwnd, UINT width, UINT height)
    {
        _hWnd = hwnd;

        HRESULT hr = S_OK;

        // ID2D1Factory 생성
        // Direct2D의 모든 객체를 만들기 위한 팩토리
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);
        if (FAILED(hr))
        {
            // 실패 메시지를 출력하거나 로깅
            MessageBox(nullptr, L"D2D Factory 생성 실패!", L"에러", MB_OK | MB_ICONERROR);
            return hr;
        }

        // IWICImagingFactory 생성
        // 이미지를 로드하여 Direct2D 비트맵으로 변환하는 Windows Imaging Component의 팩토리
        hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"WIC Factory 생성 실패!", L"에러", MB_OK | MB_ICONERROR);
            return hr;
        }

        // IDWriteFactory 생성
        // 고품질 텍스트 렌더링을 위한 DirectWrite의 팩토리
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&_writeFactory));
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"DWrite Factory 생성 실패!", L"에러", MB_OK | MB_ICONERROR);
            return hr;
        }

        // 렌더 타겟 및 장치 리소스 생성
        hr = CreateDeviceResources();
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"Direct2D Device Resources 생성 실패!", L"에러", MB_OK | MB_ICONERROR);
        }
        return hr;
    }

    void GraphicDevice::BeginDraw(D2D1_COLOR_F clearColor)
    {
        if (_renderTarget == nullptr)
        {
            if (FAILED(CreateDeviceResources()))
            {
                return;
            }
        }

        _renderTarget->BeginDraw();
        // 백 버퍼를 배경색으로 정리
        _renderTarget->Clear(clearColor);
    }

    HRESULT  GraphicDevice::EndDraw()
    {
        if (_renderTarget == nullptr)
        {
            return E_FAIL;
        }

        HRESULT hr = _renderTarget->EndDraw();

        if (hr == D2DERR_RECREATE_TARGET)
        {
            DiscardDeviceResources();
        }
        else if (FAILED(hr))
        {
            MessageBox(nullptr, L"Direct2D 렌더링 실패!", L"에러", MB_OK | MB_ICONERROR);
        }

        return hr;
    }

    void GraphicDevice::OnResize(UINT width, UINT height)
    {
        if (_renderTarget != nullptr)
        {
            HRESULT hr = _renderTarget->Resize(D2D1::SizeU(width, height));
            if (FAILED(hr))
            {
                if (hr == D2DERR_RECREATE_TARGET)
                {
                    DiscardDeviceResources();
                }
                else
                {
                    MessageBox(nullptr, L"렌더 타겟 크기 조정 실패!", L"에러", MB_OK | MB_ICONERROR);
                }
            }
        }
        else
        {
            // 렌더 타겟이 없으면 새로 생성 시도
            CreateDeviceResources();
        }
    }

    HRESULT GraphicDevice::CreateDeviceResources()
    {
        HRESULT hr = S_OK;

        if (_renderTarget == nullptr)
        {
            RECT rc;
            GetClientRect(_hWnd, &rc);
            D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

            hr = _d2dFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(_hWnd, size),
                &_renderTarget
            );

            if (SUCCEEDED(hr))
            {
                _renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
                _renderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
            }
        }
        return hr;
    }

    void GraphicDevice::DiscardDeviceResources()
    {
        _renderTarget = nullptr; // 렌더 타겟 해제
        // 다른 장치 종속 리소스 (비트맵, 브러시 등)도 ComPtr이라면 자동으로 처리
        // 직접 생성한 것이 있다면 여기서 Reset() 호출
    }
}