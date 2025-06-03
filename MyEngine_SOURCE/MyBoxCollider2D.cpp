#include "MyBoxCollider2D.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyRenderer.h"

namespace Source
{
	BoxCollider2D::BoxCollider2D() :
		Collider(ColliderType::Box2D)
	{
	}

	BoxCollider2D::~BoxCollider2D()
	{
	}

	void BoxCollider2D::Initialize()
	{
	}

	void BoxCollider2D::Update()
	{
	}

	void BoxCollider2D::LateUpdate()
	{
	}

	void BoxCollider2D::Render(HDC hdc)
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		Vector2 offset = GetOffset();

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Rectangle(hdc, 
			position.x + offset.x,
			position.y + offset.y,
			position.x + offset.x + 100,
			position.y + offset.y + 100);

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}
