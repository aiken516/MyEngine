#include "MyTexture.h"
#include "MyApplication.h"
#include "MyResources.h"

// 해당 전역변수가 존재함을 알리는 키워드 extern
extern Source::Application application;

namespace Source::Graphics	
{
	Texture::Texture() :
		Resource(Enums::ResourceType::Texture),
		_hasAlpha(false),
		_sprite(nullptr),
		_bitMap(nullptr),
		_hdc(nullptr),
		_textureType(TextureType::NONE),
		_width(0),
		_height(0)
	{
	}
	
	Texture::~Texture()
	{
	}

	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
	{
		Texture* texture = Resources::Find<Texture>(name);
		if (texture != nullptr)
		{
			return texture;
		}

		texture = new Texture();
		texture->SetName(name);
		texture->SetWidth(width);
		texture->SetHeight(height);

		HDC hdc = application.GetHDC();

		texture->_bitMap = CreateCompatibleBitmap(hdc, width, height);
		texture->_hdc = CreateCompatibleDC(hdc);

		HBITMAP oldBitMap = (HBITMAP)SelectObject(texture->_hdc, texture->_bitMap);
		DeleteObject(oldBitMap);

		Resources::Insert(name + L"Sheet", texture);

		return texture;
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

			if (info.bmBitsPixel == 32)
			{
				_hasAlpha = true;
			}
			else if (info.bmBitsPixel == 24)
			{
				_hasAlpha = false;
			}

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