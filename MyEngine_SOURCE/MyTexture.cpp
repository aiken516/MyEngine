#include "MyTexture.h"
#include "MyApplication.h"
#include "MyResources.h"

// 해당 전역변수가 존재함을 알리는 키워드 extern
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

		// GraphicDevice에서 WIC 팩토리와 렌더 타겟 가져오기
		ID2D1HwndRenderTarget* renderTarget = application.GetGraphicDevice()->GetRenderTarget();
		IWICImagingFactory* wicFactory = application.GetGraphicDevice()->GetWICFactory();

		if (!renderTarget || !wicFactory)
		{
			return E_FAIL;
		}

		HRESULT result = S_OK;

		// WIC 디코더 생성
		// 디코더는 파일의 확장자를 자동으로 인식하여 그 파일 형식에 맞는 데이터를 해석
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

		// 디코더에서 첫 번째 프레임 가져오기
		// GIF 등은 여러 프레임을 가질 수 있으나, 일반적인 이미지는 0번째를 이용
		ComPtr<IWICBitmapFrameDecode> frame;
		result = decoder->GetFrame(0, &frame);

		if (FAILED(result))
		{
			return result;
		}

		// 비트맵 픽셀 포맷 변환
		// D2D와 호환되는 포맷으로 변환하는 과정
		ComPtr<IWICFormatConverter> converter;
		result = wicFactory->CreateFormatConverter(&converter);

		if (FAILED(result))
		{
			return result;
		}

		// WIC_PIXEL_FORMAT_32BPP_PBGRA: Direct2D에서 기본적으로 사용되는 픽셀 포맷
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

		// WIC 비트맵을 Direct2D 비트맵으로 변환
		result = renderTarget->CreateBitmapFromWicBitmap(
			converter.Get(),
			nullptr,
			&_bitmap
		);

		if (FAILED(result))
		{
			return result;
		}

		// 비트맵의 너비와 높이 저장
		if (SUCCEEDED(result))
		{
			D2D1_SIZE_F size = _bitmap.Get()->GetSize();
			_width = static_cast<UINT>(size.width);
			_height = static_cast<UINT>(size.height);
		}

		return result;
	}
}