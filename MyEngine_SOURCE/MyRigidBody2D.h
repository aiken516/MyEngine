#pragma once
#include "MyEntity.h"
#include "MyComponent.h"
#include "MyCollider.h"

namespace Source
{
	class RigidBody2D : public Component
	{
	public:
		RigidBody2D();
		~RigidBody2D();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render()  override;

		void OnCollisionEnter(class Collider* other);
		void OnCollisionStay(class Collider* other);
		void OnCollisionExit(class Collider* other);

		void SetIsGround(bool isGround) { _isGround = isGround; }
		void SetUseGravity(bool useGravity) { _useGravity = useGravity; }

		void SetMass(float mass) { _mass = mass; }
		void SetFriction(float friction) { _friction = friction; }
		void SetVelocity(const Vector2& velocity) { _velocity = velocity; }
		void SetGravity(const Vector2& gravity) { _gravity = gravity; }

		void AddForce(const Vector2& force) { _force += force; }

	private:
		bool _isGround;
		bool _useGravity;

		float _mass;
		float _friction;

		Vector2 _force;
		Vector2 _acceleration;
		Vector2 _velocity;
		Vector2 _gravity;

		Vector2 _terminalVelocity;
	};
}