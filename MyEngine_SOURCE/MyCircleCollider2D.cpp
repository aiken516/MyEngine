#include "MyCircleCollider2D.h"
#include "MyBoxCollider2D.h"
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

	bool CircleCollider2D::Intersect(Collider* other)
	{
		return other->IntersectWithCircle(this);// 더블 디스패치 구조
	}

	bool CircleCollider2D::IntersectWithCircle(CircleCollider2D* other)
	{
		//Circle과 Circle
		Transform* ownerTransform = this->GetOwner()->GetComponent<Transform>();
		Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

		Vector2 ownerPosition = ownerTransform->GetPosition() + this->GetOffset();
		Vector2 otherPosition = otherTransform->GetPosition() + other->GetOffset();

		// size 1,1 일 기본크기가 100픽셀이라고 가정, 추후 확인 필요
		Vector2 ownerSize = this->GetSize() * 100.0f;
		Vector2 otherSize = other->GetSize() * 100.0f;

		Vector2 ownerCirclePosition = ownerPosition + (ownerSize / 2.0f);
		Vector2 otherCirclePosition = otherPosition + (otherSize / 2.0f);

		float distance = (ownerCirclePosition - otherCirclePosition).Length();

		if (distance <= (ownerSize.x / 2.0f + otherSize.x / 2.0f))
		{
			return true;
		}

		return false; // 충돌 없음
	}

	bool CircleCollider2D::IntersectWithBox(BoxCollider2D* other)
	{
		//Circle과 Box
		Transform* ownerTransform = this->GetOwner()->GetComponent<Transform>();
		Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

		Vector2 ownerPosition = ownerTransform->GetPosition() + this->GetOffset();
		Vector2 otherPosition = otherTransform->GetPosition() + other->GetOffset();

		// size 1,1 일 기본크기가 100픽셀이라고 가정, 추후 확인 필요
		Vector2 ownerSize = this->GetSize() * 100.0f;
		Vector2 otherSize = other->GetSize() * 100.0f;

		Vector2 circlePosition; //원의 중점
		Vector2	boxPosition;
		Vector2 boxSize;

		float circleRadius;

		circlePosition = ownerPosition + (ownerSize / 2.0f);
		circleRadius = ownerSize.x / 2.0f;
		boxPosition = otherPosition;
		boxSize = otherSize;

		Vector2 boxCenter = boxPosition + boxSize / 2.0f;

		//사각형 내부에서 원과 가장 가까운 점
		Vector2 closestPoint;
		float halfWidth = boxSize.x / 2.0f;
		float halfHeight = boxSize.y / 2.0f;

		float boxMinX = boxCenter.x - halfWidth;
		float boxMaxX = boxCenter.x + halfWidth;
		float boxMinY = boxCenter.y - halfHeight;
		float boxMaxY = boxCenter.y + halfHeight;

		closestPoint.x = std::clamp(circlePosition.x, boxMinX, boxMaxX);
		closestPoint.y = std::clamp(circlePosition.y, boxMinY, boxMaxY);

		Vector2 difference = circlePosition - closestPoint;
		if (difference.x * difference.x + difference.y * difference.y <= circleRadius * circleRadius)
		{
			return true;// 충돌 발생
		}

		return false;// 충돌 없음
	}
}