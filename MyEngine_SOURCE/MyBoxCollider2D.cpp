#include "MyBoxCollider2D.h"
#include "MyCircleCollider2D.h"
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

	bool BoxCollider2D::Intersect(Collider* other)
	{
		return other->IntersectWithBox(this);// 더블 디스패치 구조
	}

	bool BoxCollider2D::IntersectWithCircle(CircleCollider2D* other)
	{
		//Circle과 Box
		return other->IntersectWithBox(this); // Circle의 처리로 위임
	}

	bool BoxCollider2D::IntersectWithBox(BoxCollider2D* other)
	{
		//Box과 Box
		Transform* ownerTransform = this->GetOwner()->GetComponent<Transform>();
		Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

		Vector2 ownerPosition = ownerTransform->GetPosition() + this->GetOffset();
		Vector2 otherPosition = otherTransform->GetPosition() + other->GetOffset();

		// size 1,1 일 기본크기가 100픽셀이라고 가정, 추후 확인 필요
		Vector2 ownerSize = this->GetSize() * 100.0f;
		Vector2 otherSize = other->GetSize() * 100.0f;

		if (fabs(ownerPosition.x - otherPosition.x) < fabs(ownerSize.x / 2.0f + otherSize.x / 2.0f) &&
			fabs(ownerPosition.y - otherPosition.y) < fabs(ownerSize.y / 2.0f + otherSize.y / 2.0f))
		{
			return true;//충돌 발생
		}

		return false;//충돌 없음
	}
}
