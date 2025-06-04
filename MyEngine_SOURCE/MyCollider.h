#pragma once
#include "MyComponent.h"

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
		virtual void Render(HDC hdc) override;

		virtual bool Intersect(Collider* other) = 0;
		virtual bool IntersectWithCircle(class CircleCollider2D* other) = 0;
		virtual bool IntersectWithBox(class BoxCollider2D* other) = 0;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		UINT32 GetCollisionID() const { return _collisionID; }
		Math::Vector2 GetOffset() const { return _offset; }
		void SetOffset(Math::Vector2 offset) { _offset = offset; }
		Math::Vector2 GetSize() const { return _size; }
		void SetSize(Math::Vector2 size) { _size = size; }
		ColliderType GetColliderType() const { return _type; }
	private:
		static UINT32 _currentCollisionID;
		
		ColliderType _type;
		UINT32 _collisionID;
		Math::Vector2 _offset;
		Math::Vector2 _size;
	};
}
