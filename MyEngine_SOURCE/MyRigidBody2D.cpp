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
		_force(Vector2::Zero),
		_acceleration(Vector2::Zero),
		_velocity(Vector2::Zero),
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
			//중력 방향 단위 벡터 계산 (정규화)
			Vector2 gravityDirection = _gravity;
			gravityDirection.Normalize();

			// 현재 속도의 중력 방향 성분
			float verticalSpeed = _velocity.Dot(gravityDirection);

			if (_isGround)
			{
				//물체 위에서는 수직 방향 속도 제거하고 적용(수직항력)
				_velocity -= gravityDirection * verticalSpeed;
			}
			else
			{
				// 공중일 경우 그냥 중력 적용
				_velocity += _gravity * Time::DeltaTime();

				// 중력 적용 후 계산
				verticalSpeed = _velocity.Dot(gravityDirection);
			}

			// 중력 방향 속도 벡터
			Vector2 verticalVelocity = gravityDirection * verticalSpeed;

			// 중력과 수직인 속도(수평 속도) 계산
			Vector2 horizontalVelocity = _velocity - verticalVelocity;

			// 중력 방향 속도 제한
			if (fabs(verticalSpeed) > _terminalVelocity.y)
			{
				verticalVelocity = gravityDirection * _terminalVelocity.y;
				if (verticalSpeed < 0)
				{
					// 아래로 떨어지는 경우
					verticalVelocity *= -1.0f; 
				}
				else
				{
					// 위로 향하는 경우
					verticalVelocity *= 1.0f;
				}
			}

			// 수평 속도 제한
			float horizontalSpeed = horizontalVelocity.Length();
			if (horizontalSpeed > _terminalVelocity.x)
			{
				horizontalVelocity.Normalize();
				horizontalVelocity *= _terminalVelocity.x;
			}

			// 최종 속도 = 수직 + 수평
			_velocity = verticalVelocity + horizontalVelocity;
		}

		// 마찰력 적용(Damping으로 수정해야 할 수도?)
		if (_velocity != Vector2::Zero)
		{
			//속도의 반대 방향으로 마찰력을 적용
			Vector2 minusVelocity = -_velocity;
			minusVelocity.Normalize();
			Vector2 frictionForce = minusVelocity * _friction * _mass * Time::DeltaTime();

			if (_velocity.Length() < frictionForce.Length())
			{
				// 마찰력으로 속도가 0이 되면 정지
				_velocity = Vector2::Zero;
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

		_force = Vector2::Zero;
	}

	void RigidBody2D::LateUpdate()
	{
	}

	void RigidBody2D::Render()
	{
	}

	void RigidBody2D::OnCollisionEnter(Collider* other)
	{

	}

	void RigidBody2D::OnCollisionStay(Collider* other)
	{
		Collider* collider = this->GetOwner()->GetComponent<Collider>();
		Vector2 correction = other->ResolveCollision(collider, this);

		if (correction != Vector2::Zero)
		{
			Transform* transform = this->GetOwner()->GetComponent<Transform>();
			Vector2 position = transform->GetPosition();
			position += correction;
			transform->SetPosition(position);

			Vector2 gravityDirection = _gravity;
			gravityDirection.Normalize();
			gravityDirection *= -1.0f;
			correction.Normalize();
			Vector2 correctionDirection = correction;

			float alignment = correctionDirection.Dot(gravityDirection);
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