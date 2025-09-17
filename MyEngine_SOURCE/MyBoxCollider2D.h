#pragma once
#include "MyCollider.h"

namespace Source
{
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnDrawGizmos() override;

		bool Intersect(Collider* other) override;
		bool IntersectWithCircle(class CircleCollider2D* other) override;
		bool IntersectWithBox(class BoxCollider2D* other) override;

		Vector2 ResolveCollision(Collider* other, RigidBody2D* rigidBody) override;
		Vector2 ResolveWithCircle(class CircleCollider2D* other, RigidBody2D* rigidBody) override;
		Vector2 ResolveWithBox(class BoxCollider2D* other, RigidBody2D* rigidBody) override;

		Vector2 GetSize() const { return _size; }
		void SetSize(Vector2 size) { _size = size; }
	private:
		Vector2 _size;
	};
}
