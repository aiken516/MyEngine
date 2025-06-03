#include "MyCollider.h"
#include "MyGameObject.h"
#include "MyScript.h"

namespace Source
{
	//충돌체 ID는 1부터 시작해, 각 인스턴스마다 고유 ID를 부여
	UINT32 Collider::_currentCollisionID = 1;

	Collider::Collider(ColliderType type) : 
		Component(Enums::ComponentType::Collider),
		_type(type),
		_offset(Math::Vector2::zero),
		_size(Math::Vector2::one),
		_collisionID(_currentCollisionID++)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render(HDC hdc)
	{
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script != nullptr)
		{
			script->OnCollisionEnter(other);
		}
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script != nullptr)
		{
			script->OnCollisionStay(other);
		}
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		if (script != nullptr)
		{
			script->OnCollisionExit(other);
		}
	}
}