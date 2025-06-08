#include "MyRigidBody2D.h"
#include "MyTime.h"
#include "MyGameObject.h"
#include "MyTransform.h"

namespace Source
{
	RigidBody2D::RigidBody2D() :
		Component(Enums::ComponentType::RigidBody),
		_mass(1.0f),
		_friction(20.0f),
		_force(Vector2::zero),
		_acceleration(Vector2::zero),
		_velocity(Vector2::zero),
		_gravity(Vector2::zero)
	{
	}

	RigidBody2D::~RigidBody2D()
	{
	}

	void RigidBody2D::Initialize()
	{
	}

	void RigidBody2D::Update()
	{
		// f = m * a
		// a = f / m
		_acceleration = _force / _mass;
		_velocity += _acceleration * Time::DeltaTime();

		// ������ ����(Damping���� �����ؾ� �� ����?)
		if (_velocity != Vector2::zero)
		{
			//�ӵ��� �ݴ� �������� �������� ����
			Vector2 frictionForce = (-_velocity).Normalize() * _friction * _mass * Time::DeltaTime();

			if (_velocity.Length() < frictionForce.Length())
			{
				// ���������� �ӵ��� 0�� �Ǹ� ����
				_velocity = Vector2::zero;
			}
			else
			{
				_velocity += frictionForce;
			}

			Transform* transform = GetOwner()->GetComponent<Transform>();
			Vector2 position = transform->GetPosition();

			position += _velocity * Time::DeltaTime();
			transform->SetPosition(position);
		}

		_force.Clear();
	}

	void RigidBody2D::LateUpdate()
	{
	}

	void RigidBody2D::Render(HDC hdc)
	{
	}
}