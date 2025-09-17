#include "MyTransform.h"

namespace Source
{
	Transform::Transform() :
		Component(Enums::ComponentType::Transform),
		_position(Vector2::zero),
		_scale(Vector2::one),
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