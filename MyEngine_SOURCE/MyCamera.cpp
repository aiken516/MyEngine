#include "MyCamera.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	Camera::Camera() :
		Component(Enums::ComponentType::Camera),
		_distance(Vector2::Zero),
		_resolution(Vector2::Zero),
		_lookPosition(Vector2::Zero),
		_target(nullptr)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		_resolution.x = application.GetWidth();
		_resolution.y = application.GetHeight();
	}

	void Camera::Update()
	{
		Transform* transform;
		if (_target == nullptr)
		{
			transform = GetOwner()->GetComponent<Transform>();
		}
		else
		{
			transform = _target->GetComponent<Transform>();
		}

		_lookPosition = transform->GetPosition();

		_distance = _lookPosition - (_resolution / 2.0f);
	}

	void Camera::LateUpdate()
	{
	}

	void Camera::Render(HDC hdc)
	{
	}
}