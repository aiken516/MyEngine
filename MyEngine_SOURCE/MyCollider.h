#pragma once
#include "MyComponent.h"
#include "MySettings.h"
#include "MyRigidBody2D.h"

namespace Source
{
	class Collider : public Component
	{
	public:
		Collider(ColliderType type);
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnDrawGizmos() override;

		virtual bool Intersect(Collider* other) = 0;
		virtual bool IntersectWithCircle(class CircleCollider2D* other) = 0;
		virtual bool IntersectWithBox(class BoxCollider2D* other) = 0;

		virtual Vector2 ResolveCollision(Collider* other, class RigidBody2D* rigidBody) = 0;
		virtual Vector2 ResolveWithCircle(class CircleCollider2D* other, class RigidBody2D* rigidBody) = 0;
		virtual Vector2 ResolveWithBox(class BoxCollider2D* other, class RigidBody2D* rigidBody) = 0;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		UINT32 GetCollisionID() const { return _collisionID; }
		Vector2 GetOffset() const { return _offset; }
		void SetOffset(Vector2 offset) { _offset = offset; }
		ColliderType GetColliderType() const { return _type; }
	private:
		static UINT32 _currentCollisionID;
		
		ColliderType _type;
		UINT32 _collisionID;
		Vector2 _offset;
	};
}
