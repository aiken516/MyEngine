#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyRenderer.h"

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
		float rotation = transform->GetRotation();
		Vector2 scale = transform->GetScale();
			
		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		if (_texture->GetTextureType() == Graphics::Texture::TextureType::Bmp)
		{
			//https://blog.naver.com/power2845/50147965306
			TransparentBlt(hdc, 
				position.x,
				position.y,
				_texture->GetWidth() * _size.x * scale.x,//size를 지울 필요가 있을 수도
				_texture->GetHeight() * _size.y * scale.y,//size를 지울 필요가 있을 수도
				_texture->GetHdc(),
				0, 0,
				_texture->GetWidth(),
				_texture->GetHeight(),
				RGB(255, 0, 255));//마젠타
		}
		else if (_texture->GetTextureType() == Graphics::Texture::TextureType::Png)
		{
			Gdiplus::ImageAttributes imageAttributes = {};

			//투명 처리하는 범위
			imageAttributes.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphcis(hdc);

			graphcis.TranslateTransform(position.x, position.y);
			graphcis.RotateTransform(transform->GetRotation());
			graphcis.TranslateTransform(-position.x, -position.y);

			graphcis.DrawImage(_texture->GetSprite(), 
				Gdiplus::Rect(
					position.x,
					position.y, 
					_texture->GetWidth() * _size.x * scale.x,//size를 지울 필요가 있을 수도
					_texture->GetHeight() * _size.y * scale.y//size를 지울 필요가 있을 수도
				),
				0, 0,
				_texture->GetWidth(),
				_texture->GetHeight(),
				Gdiplus::UnitPixel, nullptr/* & imageAttributes //애초에 알파 값이 있음*/
			);
		}
	}
}