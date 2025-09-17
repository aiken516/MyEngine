#include "MyCamera.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	Camera::Camera() :
		Component(Enums::ComponentType::Camera),
		_resolution(Vector2::zero),
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
		if (_target != nullptr)
		{
			Transform* transform = GetOwner()->GetComponent<Transform>();
			Transform* targetTransform = _target->GetComponent<Transform>();

			if (transform != nullptr && targetTransform != nullptr)
			{
				Vector2 targetPosition = targetTransform->GetPosition();
				transform->SetPosition(targetPosition);
			}
		}
	}

	void Camera::LateUpdate()
	{
	}

	void Camera::Render()
	{
	}

	D2D1_MATRIX_3X2_F Camera::GetViewMatrix()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		if (transform == nullptr)
		{
			return D2D1::Matrix3x2F::Identity();
		}

		Vector2 position = transform->GetPosition();
		float rotation = transform->GetRotation();
		Vector2 scale = transform->GetScale();

		D2D1_MATRIX_3X2_F cameraScaleMatrix = D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(scale.x, scale.y)
		);

		D2D1_MATRIX_3X2_F cameraRotationMatrix = D2D1::Matrix3x2F::Rotation(
			rotation
		);

		D2D1_MATRIX_3X2_F cameraTranslationMatrix = D2D1::Matrix3x2F::Translation(
			position.x - _resolution.x * 0.5f, position.y - _resolution.y * 0.5f
		);

		D2D1_MATRIX_3X2_F cameraWorldMatrix = cameraScaleMatrix * cameraRotationMatrix * cameraTranslationMatrix;

		// 뷰 행렬은 월드 행렬의 역행렬
		D2D1_MATRIX_3X2_F viewMatrix = cameraWorldMatrix;

		D2D1InvertMatrix(&viewMatrix);

		return viewMatrix;
	}
}