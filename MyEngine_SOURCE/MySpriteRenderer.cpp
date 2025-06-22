#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyRenderer.h"
#include "MyApplication.h"

#include <windows.h>  // �⺻ Windows API ���
#include <Shlwapi.h>  // PathFileExists()�� ����� ���
#include <iostream>

#pragma comment(lib, "Shlwapi.lib")  // ���̺귯�� ��ũ

extern Source::Application application;

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

		int worldHeight = application.GetHeight();
		int worldWidth = application.GetWidth();

		if (position.x > worldWidth || position.x + _texture->GetWidth() * _size.x * scale.x < 0.0f ||
			position.y > worldHeight || position.y + _texture->GetWidth() * _size.y * scale.y < 0.0f)
		{
			return; // ȭ�� �ۿ� �ִ� ��� �ø�
		}

		if (_texture->GetTextureType() == Graphics::Texture::TextureType::Bmp)
		{
			if (_texture->HasAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(���� ����) ~ 255(���� ������)

				AlphaBlend(hdc,
					position.x,
					position.y,
					_texture->GetWidth() * _size.x * scale.x,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHeight() * _size.y * scale.y,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHdc(),
					0, 0,
					_texture->GetWidth(),
					_texture->GetHeight(),
					func);//����Ÿ�� ���� �����������
			}
			else
			{
				//https://blog.naver.com/power2845/50147965306
				TransparentBlt(hdc,
					position.x,
					position.y,
					_texture->GetWidth() * _size.x * scale.x,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHeight() * _size.y * scale.y,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHdc(),
					0, 0,
					_texture->GetWidth(),
					_texture->GetHeight(),
					RGB(255, 0, 255));//����Ÿ
			}
		}
		else if (_texture->GetTextureType() == Graphics::Texture::TextureType::Png)
		{
			Gdiplus::ImageAttributes imageAttributes = {};

			//���� ó���ϴ� ����
			imageAttributes.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphcis(hdc);

			graphcis.TranslateTransform(position.x, position.y);
			graphcis.RotateTransform(transform->GetRotation());
			graphcis.TranslateTransform(-position.x, -position.y);

			graphcis.DrawImage(_texture->GetSprite(), 
				Gdiplus::Rect(
					position.x,
					position.y, 
					_texture->GetWidth() * _size.x * scale.x,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHeight() * _size.y * scale.y//size�� ���� �ʿ䰡 ���� ����
				),
				0, 0,
				_texture->GetWidth(),
				_texture->GetHeight(),
				Gdiplus::UnitPixel, nullptr/* & imageAttributes //���ʿ� ���� ���� ����*/
			);
		}
	}
}