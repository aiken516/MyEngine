#include "MyTexture.h"
#include "MyApplication.h"

// 해당 전역변수가 존재함을 알리는 키워드 extern
extern Source::Application application;

namespace Source::Graphics	
{
	Texture::Texture() : 
	Resource(Enums::ResourceType::Texture)
	{
	}
	
	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring path)
	{
		//파일 확장자 받아오기
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		//이미지가 bmp일 때
		if (ext == L"bmp")
		{
			_textureType = TextureType::Bmp;
			_bitMap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (_bitMap == nullptr)
			{
				return S_FALSE;
			}

			BITMAP info = {};
			GetObject(_bitMap, sizeof(BITMAP), &info);

			_width = info.bmWidth;
			_height = info.bmHeight;

			HDC mainDC = application.GetHDC();
			_hdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(_hdc, _bitMap);
			DeleteObject(oldBitmap);
		}
		//이미지가 png일 때
		else if (ext == L"png")
		{
			_textureType = TextureType::Png;
			_sprite = Gdiplus::Image::FromFile(path.c_str());
			if (_sprite == nullptr)
			{
				return S_FALSE;
			}

			_width = _sprite->GetWidth();
			_height = _sprite->GetHeight();
		}

		return S_OK;
	}
}