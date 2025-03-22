#include "MyCamera.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	Camera::Camera() :
		Component(Enums::ComponentType::Camera),
		_distance(Vector2::zero),
		_resolution(Vector2::zero),
		_lookPosition(Vector2::zero),
		_target(nullptr)
	{
	}
	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		_resolution.x = application.GetWidth();
		_resolution.x = application.GetHeight();
	}

	void Camera::Update()
	{
		if (_target != nullptr)
		{
			Transform* transform = _target->GetComponent<Transform>();
			_lookPosition = transform->GetPosition();
		}
		else
		{
			Transform* transform = GetOwner()->GetComponent<Transform>();
			_lookPosition = transform->GetPosition();
		}

		_distance = _lookPosition - (_resolution / 2.0f);
	}
	void Camera::LateUpdate()
	{
	}
	void Camera::Render(HDC hdc)
	{
	}
}