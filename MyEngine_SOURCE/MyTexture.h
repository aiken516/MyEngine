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

		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring path) override;
		UINT GetWidth() { return _width; }
		void SetWidth(UINT width) { _width = width; }
		UINT GetHeight() { return _height; }
		void SetHeight(UINT height) { _height = height; }
		HDC GetHdc() { return _hdc; }
		TextureType GetTextureType() { return _textureType; }
		Gdiplus::Image* GetSprite() { return _sprite; }
		bool HasAlpha() { return _hasAlpha; }

	private:
		bool _hasAlpha;
		Gdiplus::Image* _sprite;
		HBITMAP _bitMap;
		HDC _hdc;

		TextureType _textureType;

		UINT _width;
		UINT _height;
	};
}