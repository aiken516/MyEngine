#include "MyTransform.h"

namespace Source
{
	Transform::Transform() :
		Component(Enums::ComponentType::Transform),
		_position(Vector2::Zero),
		_scale(Vector2::One),
		_rotation(0.0f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::Render()
	{
	}
}