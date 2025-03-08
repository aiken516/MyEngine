#pragma once
#include "MyResource.h"

namespace Source::Graphics
{
	class Texture : public Resource
	{
	public:
		enum class TextureType
		{
			Bmp,
			Png,
			NONE,
		};

		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring path) override;
		UINT GetWidth() { return _width; }
		UINT GetHeight() { return _height; }
		HDC GetHdc() { return _hdc; }
		TextureType GetTextureType() { return _textureType; }
		Gdiplus::Image* GetSprite() { return _sprite; }

	private:
		Gdiplus::Image* _sprite;
		HBITMAP _bitMap;
		HDC _hdc;

		TextureType _textureType;

		UINT _width;
		UINT _height;


	};
}