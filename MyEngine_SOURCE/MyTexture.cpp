#include "MyTexture.h"
#include "MyApplication.h"
#include "MyResources.h"

// �ش� ���������� �������� �˸��� Ű���� extern
extern Source::Application application;

namespace Source::Graphics	
{
	Texture::Texture() :
		Resource(Enums::ResourceType::Texture),
		_width(0),
		_height(0)
	{
	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring path)
	{
		_path = path;

		// GraphicDevice���� WIC ���丮�� ���� Ÿ�� ��������
		ID2D1HwndRenderTarget* renderTarget = application.GetGraphicDevice()->GetRenderTarget();
		IWICImagingFactory* wicFactory = application.GetGraphicDevice()->GetWICFactory();

		if (!renderTarget || !wicFactory)
		{
			return E_FAIL;
		}

		HRESULT result = S_OK;

		// WIC ���ڴ� ����
		// ���ڴ��� ������ Ȯ���ڸ� �ڵ����� �ν��Ͽ� �� ���� ���Ŀ� �´� �����͸� �ؼ�
		ComPtr<IWICBitmapDecoder> decoder;
		result = wicFactory->CreateDecoderFromFilename(
			path.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&decoder
		);

		if (FAILED(result)) 
		{
			return result;
		}

		// ���ڴ����� ù ��° ������ ��������
		// GIF ���� ���� �������� ���� �� ������, �Ϲ����� �̹����� 0��°�� �̿�
		ComPtr<IWICBitmapFrameDecode> frame;
		result = decoder->GetFrame(0, &frame);

		if (FAILED(result))
		{
			return result;
		}

		// ��Ʈ�� �ȼ� ���� ��ȯ
		// D2D�� ȣȯ�Ǵ� �������� ��ȯ�ϴ� ����
		ComPtr<IWICFormatConverter> converter;
		result = wicFactory->CreateFormatConverter(&converter);

		if (FAILED(result))
		{
			return result;
		}

		// WIC_PIXEL_FORMAT_32BPP_PBGRA: Direct2D���� �⺻������ ���Ǵ� �ȼ� ����
		result = converter->Initialize(
			frame.Get(),
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeMedianCut
		);

		if (FAILED(result))
		{
			return result;
		}

		// WIC ��Ʈ���� Direct2D ��Ʈ������ ��ȯ
		result = renderTarget->CreateBitmapFromWicBitmap(
			converter.Get(),
			nullptr,
			&_bitmap
		);

		if (FAILED(result))
		{
			return result;
		}

		// ��Ʈ���� �ʺ�� ���� ����
		if (SUCCEEDED(result))
		{
			D2D1_SIZE_F size = _bitmap.Get()->GetSize();
			_width = static_cast<UINT>(size.width);
			_height = static_cast<UINT>(size.height);
		}

		return result;
	}
}