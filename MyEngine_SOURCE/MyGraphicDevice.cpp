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

        // ID2D1Factory ����
        // Direct2D�� ��� ��ü�� ����� ���� ���丮
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);
        if (FAILED(hr))
        {
            // ���� �޽����� ����ϰų� �α�
            MessageBox(nullptr, L"D2D Factory ���� ����!", L"����", MB_OK | MB_ICONERROR);
            return hr;
        }

        // IWICImagingFactory ����
        // �̹����� �ε��Ͽ� Direct2D ��Ʈ������ ��ȯ�ϴ� Windows Imaging Component�� ���丮
        hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"WIC Factory ���� ����!", L"����", MB_OK | MB_ICONERROR);
            return hr;
        }

        // IDWriteFactory ����
        // ��ǰ�� �ؽ�Ʈ �������� ���� DirectWrite�� ���丮
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&_writeFactory));
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"DWrite Factory ���� ����!", L"����", MB_OK | MB_ICONERROR);
            return hr;
        }

        // ���� Ÿ�� �� ��ġ ���ҽ� ����
        hr = CreateDeviceResources();
        if (FAILED(hr))
        {
            MessageBox(nullptr, L"Direct2D Device Resources ���� ����!", L"����", MB_OK | MB_ICONERROR);
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
        // �� ���۸� �������� ����
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
            MessageBox(nullptr, L"Direct2D ������ ����!", L"����", MB_OK | MB_ICONERROR);
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
                    MessageBox(nullptr, L"���� Ÿ�� ũ�� ���� ����!", L"����", MB_OK | MB_ICONERROR);
                }
            }
        }
        else
        {
            // ���� Ÿ���� ������ ���� ���� �õ�
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
        _renderTarget = nullptr; // ���� Ÿ�� ����
        // �ٸ� ��ġ ���� ���ҽ� (��Ʈ��, �귯�� ��)�� ComPtr�̶�� �ڵ����� ó��
        // ���� ������ ���� �ִٸ� ���⼭ Reset() ȣ��
    }
}