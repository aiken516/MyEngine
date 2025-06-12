#include "MyUIImage.h"

namespace Source
{
	UIImage::UIImage() :
		UIBase(UIType::Image),
		_texture(nullptr)
	{
	}

	UIImage::~UIImage()
	{
	}

	void UIImage::OnInitialize()
	{
	}

	void UIImage::OnActive()
	{
	}

	void UIImage::OnInActive()
	{
	}

	void UIImage::OnUpdate()
	{
	}

	void UIImage::OnLateUpdate()
	{
	}

	void UIImage::OnRender(HDC hdc)
	{
		TransparentBlt(hdc,
			0, 0,
			_texture->GetWidth(),
			_texture->GetHeight(),
			_texture->GetHdc(),
			0, 0,
			_texture->GetWidth(),
			_texture->GetHeight(),
			RGB(255, 0, 255));
	}

	void UIImage::OnClear()
	{
	}
}