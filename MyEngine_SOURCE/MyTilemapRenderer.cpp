#include "MyTilemapRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MyTexture.h"
#include "MyRenderer.h"

#include <windows.h>  // �⺻ Windows API ���
#include <Shlwapi.h>  // PathFileExists()�� ����� ���
#include <iostream>

#pragma comment(lib, "Shlwapi.lib")  // ���̺귯�� ��ũ

namespace Source
{
	Vector2 TilemapRenderer::TileSize = Vector2::one;

	Vector2 TilemapRenderer::OriginTileSize = Vector2::one;
	Vector2 TilemapRenderer::SelectedIndex = Vector2(-1.0f, -1.0f);

	TilemapRenderer::TilemapRenderer() :
		Component(Enums::ComponentType::Renderer),
		_texture(nullptr),
		_size(Vector2::one),
		_index(Vector2::zero),
		_tileSize(Vector2(16.0f, 16.0f))
	{
		TileSize = Vector2(_tileSize.x * _size.x, _tileSize.y * _size.y); // TileSize�� �ʱ�ȭ

		OriginTileSize = _tileSize;
	}

	TilemapRenderer::~TilemapRenderer()
	{
	}

	void TilemapRenderer::Initialize()
	{
	}

	void TilemapRenderer::Update()
	{
	}

	void TilemapRenderer::LateUpdate()
	{
	}

	void TilemapRenderer::Render(HDC hdc)
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
					_tileSize.x * _size.x * scale.x,//size�� ���� �ʿ䰡 ���� ����
					_tileSize.y * _size.y * scale.y,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHdc(),
					_index.x * _tileSize.x,
					_index.y * _tileSize.y,
					_tileSize.x,
					_tileSize.y,
					func);//����Ÿ�� ���� �����������
			}
			else
			{
				//https://blog.naver.com/power2845/50147965306
				TransparentBlt(hdc,
					position.x,
					position.y,
					_tileSize.x * _size.x * scale.x,//size�� ���� �ʿ䰡 ���� ����
					_tileSize.y * _size.y * scale.y,//size�� ���� �ʿ䰡 ���� ����
					_texture->GetHdc(),
					_index.x * _tileSize.x,
					_index.y * _tileSize.y,
					_tileSize.x,
					_tileSize.y,
					RGB(255, 0, 255));//����Ÿ
			}
		}
		// png ������ �̿��ϸ� ������ ������
		//else if (_texture->GetTextureType() == Graphics::Texture::TextureType::Png)
		//{
		//	Gdiplus::ImageAttributes imageAttributes = {};
		//
		//	//���� ó���ϴ� ����
		//	imageAttributes.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));
		//
		//	Gdiplus::Graphics graphcis(hdc);
		//
		//	graphcis.TranslateTransform(position.x, position.y);
		//	graphcis.RotateTransform(transform->GetRotation());
		//	graphcis.TranslateTransform(-position.x, -position.y);
		//
		//	graphcis.DrawImage(_texture->GetSprite(),
		//		Gdiplus::Rect(
		//			position.x,
		//			position.y,
		//			_texture->GetWidth() * _size.x * scale.x,//size�� ���� �ʿ䰡 ���� ����
		//			_texture->GetHeight() * _size.y * scale.y//size�� ���� �ʿ䰡 ���� ����
		//		),
		//		0, 0,
		//		_texture->GetWidth(),
		//		_texture->GetHeight(),
		//		Gdiplus::UnitPixel, nullptr/* & imageAttributes //���ʿ� ���� ���� ����*/
		//	);
		//}
	}
}