#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"

#include <windows.h>  // 기본 Windows API 헤더
#include <Shlwapi.h>  // PathFileExists()가 선언된 헤더
#include <iostream>

#pragma comment(lib, "Shlwapi.lib")  // 라이브러리 링크

namespace Source
{
	SpriteRenderer::SpriteRenderer() :
		Component(Enums::ComponentType::Renderer),
		_texture(nullptr),
		_size(Vector2::one)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if (_texture == nullptr)
		{
			assert(false);
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		if (_texture->GetTextureType() == Graphics::Texture::TextureType::Bmp)
		{
			//https://blog.naver.com/power2845/50147965306
			TransparentBlt(hdc, position.x, position.y
				, _texture->GetWidth() * _size.x, _texture->GetHeight() * _size.y
				, _texture->GetHdc(), 0, 0, _texture->GetWidth(), _texture->GetHeight()
				, RGB(255, 0, 255));//마젠타
		}
		else if (_texture->GetTextureType() == Graphics::Texture::TextureType::Png)
		{
			Gdiplus::Graphics graphcis(hdc);
			graphcis.DrawImage(_texture->GetSprite(), 
				Gdiplus::Rect(position.x, position.y, 
					_texture->GetWidth() * _size.x, _texture->GetHeight() * _size.y));
		}
	}
}