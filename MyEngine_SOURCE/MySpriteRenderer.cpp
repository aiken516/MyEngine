#include "MySpriteRenderer.h"
#include "MyGameObject.h"
#include "MyTransform.h"

#include <windows.h>  // �⺻ Windows API ���
#include <Shlwapi.h>  // PathFileExists()�� ����� ���
#include <iostream>

#pragma comment(lib, "Shlwapi.lib")  // ���̺귯�� ��ũ

namespace Source
{
	SpriteRenderer::SpriteRenderer()
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
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		Gdiplus::Graphics graphcis(hdc);
		graphcis.DrawImage(_sprite, Gdiplus::Rect(position.x, position.y, _width, _height));
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		_sprite = Gdiplus::Image::FromFile(path.c_str());
		_width = _sprite->GetWidth();
		_height = _sprite->GetHeight();
	}
}