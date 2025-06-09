#include "MyRigidBody2D.h"
#include "MyTime.h"
#include "MyGameObject.h"
#include "MyTransform.h"
#include "MySettings.h"

namespace Source
{
	RigidBody2D::RigidBody2D() :
		Component(Enums::ComponentType::RigidBody),
		_isGround(false),
		_useGravity(true),
		_mass(1.0f),
		_friction(20.0f),
		_force(Vector2::zero),
		_acceleration(Vector2::zero),
		_velocity(Vector2::zero),
		_gravity(Vector2(0.0f, 98.1f)),
		_terminalVelocity(Vector2(200.0f, 500.0f))
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

		if (_useGravity)
		{
			//�߷� ���� ���� ���� ��� (����ȭ)
			Vector2 gravityDirection = _gravity;
			gravityDirection.Normalize();

			// ���� �ӵ��� �߷� ���� ����
			float verticalSpeed = Vector2::Dot(_velocity, gravityDirection);

			if (_isGround)
			{
				//��ü �������� ���� ���� �ӵ� �����ϰ� ����(�����׷�)
				_velocity -= gravityDirection * verticalSpeed;
			}
			else
			{
				// ������ ��� �׳� �߷� ����
				_velocity += _gravity * Time::DeltaTime();

				// �߷� ���� �� ���
				verticalSpeed = Vector2::Dot(_velocity, gravityDirection);
			}

			// �߷� ���� �ӵ� ����
			Vector2 verticalVelocity = gravityDirection * verticalSpeed;

			// �߷°� ������ �ӵ�(���� �ӵ�) ���
			Vector2 horizontalVelocity = _velocity - verticalVelocity;

			// �߷� ���� �ӵ� ����
			if (fabs(verticalSpeed) > _terminalVelocity.y)
			{
				verticalVelocity = gravityDirection * _terminalVelocity.y;
				if (verticalSpeed < 0)
				{
					// �Ʒ��� �������� ���
					verticalVelocity *= -1.0f; 
				}
				else
				{
					// ���� ���ϴ� ���
					verticalVelocity *= 1.0f;
				}
			}

			// ���� �ӵ� ����
			float horizontalSpeed = horizontalVelocity.Length();
			if (horizontalSpeed > _terminalVelocity.x)
			{
				horizontalVelocity = horizontalVelocity.Normalize() * _terminalVelocity.x;
			}

			// ���� �ӵ� = ���� + ����
			_velocity = verticalVelocity + horizontalVelocity;
		}

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

	void RigidBody2D::OnCollisionEnter(Collider* other)
	{

	}

	void RigidBody2D::OnCollisionStay(Collider* other)
	{
		Collider* collider = this->GetOwner()->GetComponent<Collider>();
		Vector2 correction = other->ResolveCollision(collider, this);

		if (correction != Vector2::zero)
		{
			Transform* transform = this->GetOwner()->GetComponent<Transform>();
			Vector2 position = transform->GetPosition();
			position += correction;
			transform->SetPosition(position);

			Vector2 gravityDirection = _gravity;
			gravityDirection.Normalize();
			gravityDirection *= -1.0f;
			Vector2 correctionDirection = correction.Normalize();

			float alignment = Vector2::Dot(correctionDirection, gravityDirection);
			if (alignment > 0.9f)
			{
				this->SetIsGround(true);
			}
		}
	}

	void RigidBody2D::OnCollisionExit(Collider* other)
	{
		SetIsGround(false);
	}
}