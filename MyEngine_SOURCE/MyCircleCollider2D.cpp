#include "MyCircleCollider2D.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyRenderer.h"

namespace Source
{
	CircleCollider2D::CircleCollider2D() :
		Collider(ColliderType::Circle2D),
		_center(Math::Vector2::zero),
		_radius(50.0f)
	{
	}

	CircleCollider2D::~CircleCollider2D()
	{
	}

	void CircleCollider2D::Initialize()
	{
	}

	void CircleCollider2D::Update()
	{
	}

	void CircleCollider2D::LateUpdate()
	{
	}

	void CircleCollider2D::Render(HDC hdc)
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Vector2 offset = GetOffset();

		Vector2 rightBottom;
		rightBottom.x = position.x + offset.x + 100 * GetSize().x;
		rightBottom.y = position.y + offset.y + 100 * GetSize().y;

		Ellipse(hdc, 
			position.x + offset.x,
			position.y + offset.y,
			rightBottom.x,
			rightBottom.y
		);

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}