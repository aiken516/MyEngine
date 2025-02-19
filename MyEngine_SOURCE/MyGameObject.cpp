#include "MyGameObject.h"
#include "MyInput.h"

namespace Source
{
	GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
	}
	
	void GameObject::Update()
	{
		if (Input::GetKey(KeyCode::A) || Input::GetKey(KeyCode::LEFT))
		{
			X -= 0.1f;
		}
		if (Input::GetKey(KeyCode::D) || Input::GetKey(KeyCode::RIGHT))
		{
			X += 0.1f;
		}
		if (Input::GetKey(KeyCode::W) || Input::GetKey(KeyCode::UP))
		{
			Y -= 0.1f;
		}
		if (Input::GetKey(KeyCode::S) || Input::GetKey(KeyCode::DOWN))
		{
			Y += 0.1f;
		}
	}

	void GameObject::LateUpdate()
	{
	
	}

	void GameObject::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		// 파랑 브러쉬 DC에 선택 그리고 흰색 브러쉬 반환값 반환
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldBrush);

		Rectangle(hdc, X + 100, Y + 100, X + 200, Y + 200);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}

	void GameObject::SetPosition(float x, float y)
	{
		X = x;
		Y = y;
	}

	int GameObject::GetPositionX()
	{
		return X;
	}

	int GameObject::GetPositionY()
	{
		return Y;
	}
}