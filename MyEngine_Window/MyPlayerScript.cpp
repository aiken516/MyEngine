#include "MyPlayerScript.h"
#include "MyPlayer.h"
#include "MyInput.h"
#include "MyTransform.h"
#include "MyTime.h"
#include "MyGameObject.h"
#include "MyObject.h"
#include "MyRigidBody2D.h"

namespace Client
{
	PlayerScript::PlayerScript()
		: _deadTime(0.0f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		_deadTime += Time::DeltaTime();
		if (_deadTime > 6.0f)
		{
			_deadTime = 0.0f;
			//Object::Destroy(GetOwner());
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		RigidBody2D* rb = GetOwner()->GetComponent<RigidBody2D>();

		if (Input::GetKey(KeyCode::RIGHT))
		{
			//pos.x += 100.0f * Time::DeltaTime();
			//tr->SetPosition(pos);

			rb->AddForce(Vector2(100.0f, 0.0f));
		}
		else if (Input::GetKey(KeyCode::LEFT))
		{
			//pos.x -= 100.0f * Time::DeltaTime();
			//tr->SetPosition(pos);

			rb->AddForce(Vector2(-100.0f, 0.0f));
		}
		else if (Input::GetKey(KeyCode::UP))
		{
			//pos.y -= 100.0f * Time::DeltaTime();
			//tr->SetPosition(pos);

			rb->AddForce(Vector2(0.0f, -100.0f));
		}
		else if (Input::GetKey(KeyCode::DOWN))
		{
			//pos.y += 100.0f * Time::DeltaTime();
			//tr->SetPosition(pos);

			rb->AddForce(Vector2(0.0f, 100.0f));
		}
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hdc)
	{
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
		int a = 0;
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
		Object::Destroy(GetOwner());
	}
}