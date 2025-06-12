#include "MyUIButton.h"
#include "MyInput.h"

namespace Source
{
	UIButton::UIButton() :
		UIBase(UIType::Button),
		_texture(nullptr),
		_onClickEvent(Event())
	{
	}

	UIButton::~UIButton()
	{
	}

	void UIButton::OnInitialize()
	{
	}

	void UIButton::OnActive()
	{
	}

	void UIButton::OnInActive()
	{
	}

	void UIButton::OnUpdate()
	{
		Vector2 mousePosition = Input::GetMousePosition();
		_isMouseHover = (_position.x <= mousePosition.x && mousePosition.x <= _position.x + _size.x &&
			_position.y <= mousePosition.y && mousePosition.y <= _position.y + _size.y);

		if (Input::GetKeyDown(KeyCode::LBUTTON))
		{
			if (_isMouseHover)
			{
				OnClick();
			}
		}
	}

	void UIButton::OnLateUpdate()
	{
	}

	void UIButton::OnRender(HDC hdc)
	{
	}

	void UIButton::OnClear()
	{
	}

	void UIButton::OnClick()
	{
	}
}