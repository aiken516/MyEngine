#pragma once

namespace Source::Enums
{
	//Enum ������ ������Ʈ �� ���� �켱 ����
	enum class ComponentType
	{
		Transform,
		Collider,
		RigidBody,
		Script,
		Renderer,
		Animator,
		Camera,
		END
	};

	//������ �� �켱 ������ ���� ���̾�
	//����Ƽ�� ī�޶� ���̾� ����� �������� enum
	//������ ��ü�� �켱 ���� ���ڰ� �� �־�� �� ����
	enum class LayerType
	{
		None = 0,
		Background = 1,
		Player = 2,
		Particle = 3,
		//
		MAX = 16
	};

	enum class ResourceType
	{
		Texture,
		//Mesh,
		//Video,
		AudioClip,
		Animation,
		Prefab,
		END
	};

	enum class ColliderType
	{
		Circle2D,
		Box2D,
		End,
	};
}