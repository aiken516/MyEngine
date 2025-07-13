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
		UINT GetWidth() const { return _width; }
		void SetWidth(UINT width) { _width = width; }
		UINT GetHeight() const { return _height; }
		void SetHeight(UINT height) { _height = height; }
		TextureType GetTextureType() const { return _textureType; }
		bool HasAlpha() const { return _hasAlpha; }

	private:
		bool _hasAlpha;
		TextureType _textureType;

		UINT _width;
		UINT _height;
	};
}