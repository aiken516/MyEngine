#include "MyBoxCollider2D.h"
#include "MyCircleCollider2D.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyRenderer.h"

namespace Source
{
	BoxCollider2D::BoxCollider2D() :
		Collider(ColliderType::Box2D),
		_size(Math::Vector2::one)
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

	void BoxCollider2D::Render()
	{
		/*

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
		
		Rectangle(hdc, 
			position.x + offset.x - GetSize().x * 0.5f * PIXELS_PER_UNIT,
			position.y + offset.y - GetSize().y * 0.5f * PIXELS_PER_UNIT,
			position.x + offset.x + GetSize().x * 0.5f * PIXELS_PER_UNIT,
			position.y + offset.y + GetSize().y * 0.5f * PIXELS_PER_UNIT
		);

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
		*/
	}

	void BoxCollider2D::OnDrawGizmos()
	{
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

		Vector2 ownerSize = this->GetSize() * PIXELS_PER_UNIT;
		Vector2 otherSize = other->GetSize() * PIXELS_PER_UNIT;

		if (fabs(ownerPosition.x - otherPosition.x) < fabs(ownerSize.x * 0.5f + otherSize.x * 0.5f) &&
			fabs(ownerPosition.y - otherPosition.y) < fabs(ownerSize.y * 0.5f + otherSize.y * 0.5f))
		{
			return true;//충돌 발생
		}

		return false;//충돌 없음
	}

	Vector2 BoxCollider2D::ResolveCollision(Collider* other, RigidBody2D* rigidBody)
	{
		return other->ResolveWithBox(this, rigidBody);// 더블 디스패치 구조
	}

	Vector2 BoxCollider2D::ResolveWithCircle(CircleCollider2D* other, RigidBody2D* rigidBody)
	{
		//Circle과 Box
		return other->ResolveWithBox(this, rigidBody) * -1.0f; // Circle의 처리로 위임해서 -1로 방향을 변경
	}

	Vector2 BoxCollider2D::ResolveWithBox(BoxCollider2D* other, RigidBody2D* rigidBody)
	{
		//Box와 Box
		auto owner = this->GetOwner();
		BoxCollider2D* ownerCollider = owner->GetComponent<BoxCollider2D>();
		BoxCollider2D* otherCollider = other;

		Transform* ownerTransform = owner->GetComponent<Transform>();
		Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

		Vector2 ownerPosition = ownerTransform->GetPosition();
		Vector2 otherPosition = otherTransform->GetPosition();

		Vector2 ownerHalf = ownerCollider->GetSize() * PIXELS_PER_UNIT * 0.5f;
		Vector2 otherHalf = otherCollider->GetSize() * PIXELS_PER_UNIT * 0.5f;

		Vector2 distance = ownerPosition - otherPosition;
		Vector2 overlap = ownerHalf + otherHalf - Vector2(fabs(distance.x), fabs(distance.y));

		Vector2 correction = Vector2::zero;

		if (overlap.x > 0.0f && overlap.y > 0.0f)
		{
			// 최소 침투 축 기준으로 위치 보정
			if (overlap.x < overlap.y)
			{
				//x축이 더 좁은 경우
				correction.x = ( distance.x < 0) ? -overlap.x - 0.1f : overlap.x + 0.1f;
			}
			else
			{
				//y축이 더 좁은 경우
				correction.y = (distance.y < 0) ? -overlap.y - 0.1f : overlap.y + 0.1f;
			}
		}
		
		return correction;
	}
}
