#pragma once
#include "MyEntity.h"
#include "MyComponent.h"

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
		void Render(HDC hdc)  override;

		void SetMass(float mass) { _mass = mass; }
		void SetFriction(float friction) { _friction = friction; }
		void AddForce(const Vector2& force) { _force += force; }

	private:
		float _mass;
		float _friction;

		Vector2 _force;
		Vector2 _acceleration;
		Vector2 _velocity;
		Vector2 _gravity;
	};
}