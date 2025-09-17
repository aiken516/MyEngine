#include "MyComponent.h"

namespace Source
{
	Component::Component(Enums::ComponentType type) :
		_owner(),
		_type(type)
	{
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{

	}

	void Component::Update()
	{

	}

	void Component::LateUpdate()
	{

	}

	void Component::Render()
	{

	}

	void Component::OnDrawGizmos()
	{
	}
}