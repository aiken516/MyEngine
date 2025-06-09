#pragma once
#include "MyCollider.h"

namespace Source
{
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();
		~CircleCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		bool Intersect(Collider* other) override;
		bool IntersectWithCircle(class CircleCollider2D* other) override;
		bool IntersectWithBox(class BoxCollider2D* other) override;

		Vector2 ResolveCollision(Collider* other, RigidBody2D* rigidBody) override;
		Vector2 ResolveWithCircle(class CircleCollider2D* other, RigidBody2D* rigidBody) override;
		Vector2 ResolveWithBox(class BoxCollider2D* other, RigidBody2D* rigidBody) override;

		float GetRadius() const { return _radius; }
		void SetRadius(float radius) { _radius = radius; }
	private:
		Math::Vector2 _center;
		float _radius;
	};
}
