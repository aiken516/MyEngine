#include "MyCircleCollider2D.h"
#include "MyBoxCollider2D.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyRenderer.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	CircleCollider2D::CircleCollider2D() :
		Collider(ColliderType::Circle2D),
		_center(Math::Vector2::zero),
		_radius(1.0f)
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

	void CircleCollider2D::Render()
	{
	}

	void CircleCollider2D::OnDrawGizmos()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		if (Renderer::MainCamera != nullptr)
		{
			position = Renderer::MainCamera->CalculatePostion(position);
		}

		Vector2 offset = GetOffset();

		ID2D1HwndRenderTarget* renderTarget = application.GetGraphicDevice()->GetRenderTarget();

		ID2D1SolidColorBrush* brush = nullptr;
		HRESULT hr = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Green, 1.0f),
			&brush
		);

		if (SUCCEEDED(hr))
		{
			D2D1_ELLIPSE ellipse = D2D1::Ellipse(
				D2D1::Point2F(position.x + offset.x, position.y + offset.y), // 중심점 (x, y)
				GetRadius() * PIXELS_PER_UNIT, // 반지름 x
				GetRadius() * PIXELS_PER_UNIT  // 반지름 y
			);

			renderTarget->DrawEllipse(ellipse, brush, 2.0f/* 굵기 */);

			brush->Release();
		}
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

		float ownerRadius = this->GetRadius() * PIXELS_PER_UNIT;
		float otherRadius = other->GetRadius() * PIXELS_PER_UNIT;

		float distance = (ownerPosition - otherPosition).Length();

		if (distance <= (ownerRadius + otherRadius))
		{
			return true;//충돌 발생
		}

		return false;//충돌 없음
	}

	bool CircleCollider2D::IntersectWithBox(BoxCollider2D* other)
	{
		//Circle과 Box
		Transform* ownerTransform = this->GetOwner()->GetComponent<Transform>();
		Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

		Vector2 ownerPosition = ownerTransform->GetPosition() + this->GetOffset();
		Vector2 otherPosition = otherTransform->GetPosition() + other->GetOffset();

		float circleRadius = this->GetRadius() * PIXELS_PER_UNIT;
		Vector2 boxSize = other->GetSize() * PIXELS_PER_UNIT;

		Vector2 circlePosition = ownerPosition;
		Vector2 boxPosition = otherPosition;

		float boxMinX = boxPosition.x - boxSize.x * 0.5f;
		float boxMaxX = boxPosition.x + boxSize.x * 0.5f;
		float boxMinY = boxPosition.y - boxSize.y * 0.5f;
		float boxMaxY = boxPosition.y + boxSize.y * 0.5f;

		//사각형 내부에서 원과 가장 가까운 점
		Vector2 closestPoint;
		closestPoint.x = std::clamp(circlePosition.x, boxMinX, boxMaxX);
		closestPoint.y = std::clamp(circlePosition.y, boxMinY, boxMaxY);

		Vector2 difference = circlePosition - closestPoint;
		if (difference.x * difference.x + difference.y * difference.y <= circleRadius * circleRadius)
		{
			return true;// 충돌 발생
		}

		return false;// 충돌 없음
	}

	Vector2 CircleCollider2D::ResolveCollision(Collider* other, RigidBody2D* rigidBody)
	{
		return other->ResolveWithCircle(this, rigidBody);// 더블 디스패치 구조
	}

	Vector2 CircleCollider2D::ResolveWithCircle(CircleCollider2D* other, RigidBody2D* rigidBody)
	{
		Transform* ownerTransform = this->GetOwner()->GetComponent<Transform>();
		Transform* otherTransform = other->GetOwner()->GetComponent<Transform>();

		Vector2 ownerPosition = ownerTransform->GetPosition() + this->GetOffset();
		Vector2 otherPosition = otherTransform->GetPosition() + other->GetOffset();
		
		float ownerRadius = this->GetRadius() * PIXELS_PER_UNIT;
		float otherRadius = other->GetRadius() * PIXELS_PER_UNIT;

		Vector2 positionDifference = ownerPosition - otherPosition;
		float distance = positionDifference.Length();
		Vector2 direction = positionDifference.Normalize();

		float overlap = (ownerRadius + otherRadius) - distance + 0.1f;

		Vector2 correction = direction * overlap;
		
		return correction;
	}

	Vector2 CircleCollider2D::ResolveWithBox(BoxCollider2D* other, RigidBody2D* rigidBody)
	{
		Transform* circleTransform = this->GetOwner()->GetComponent<Transform>();
		Transform* boxTransform = other->GetOwner()->GetComponent<Transform>();

		float circleRadius = this->GetRadius() * PIXELS_PER_UNIT;
		Vector2 boxSize = other->GetSize() * PIXELS_PER_UNIT;

		Vector2 circlePosition = circleTransform->GetPosition() + this->GetOffset();
		Vector2 boxPosition = boxTransform->GetPosition() + other->GetOffset();

		float boxMinX = boxPosition.x - boxSize.x * 0.5f;
		float boxMaxX = boxPosition.x + boxSize.x * 0.5f;
		float boxMinY = boxPosition.y - boxSize.y * 0.5f;
		float boxMaxY = boxPosition.y + boxSize.y * 0.5f;

		//사각형 내부에서 원과 가장 가까운 점
		Vector2 closestPoint;
		closestPoint.x = std::clamp(circlePosition.x, boxMinX, boxMaxX);
		closestPoint.y = std::clamp(circlePosition.y, boxMinY, boxMaxY);

		Vector2 positionDifference = circlePosition - closestPoint;
		float distance = positionDifference.Length();
		Vector2 direction = positionDifference.Normalize();

		float overlap = circleRadius - distance + 0.1f;

		Vector2 correction = direction * overlap;

		return correction;
	}
}