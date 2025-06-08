#include "MyCameraController.h"
#include "MyInput.h"
#include "MyTransform.h"
#include "MyTime.h"
#include "MyGameObject.h"

namespace Client
{
	CameraController::CameraController()
	{
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::Initialize()
	{
	}

	void CameraController::Update()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		if (Input::GetKey(KeyCode::RIGHT))
		{
			position.x += 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(KeyCode::LEFT))
		{
			position.x -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(KeyCode::UP))
		{
			position.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(KeyCode::DOWN))
		{
			position.y += 100.0f * Time::DeltaTime();
		}

		transform->SetPosition(position);
	}

	void CameraController::LateUpdate()
	{
	}

	void CameraController::Render(HDC hdc)
	{
	}
}