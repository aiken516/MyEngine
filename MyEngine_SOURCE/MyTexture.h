#pragma once
#include "MyResource.h"

#include <d2d1.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

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

		UINT GetWidth() const { return _width; }
		UINT GetHeight() const { return _height; }

		ID2D1Bitmap* GetBitmap() const { return _bitmap.Get(); }

	private:
		std::wstring _path;
		UINT _width;
		UINT _height;

		ComPtr<ID2D1Bitmap> _bitmap;
	};
}