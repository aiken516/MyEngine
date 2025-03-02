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
		graphcis.DrawImage(sprite_, Gdiplus::Rect(position.x, position.y, width_, height_));
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		sprite_ = Gdiplus::Image::FromFile(path.c_str());
		width_ = sprite_->GetWidth();
		height_ = sprite_->GetHeight();
	}
}