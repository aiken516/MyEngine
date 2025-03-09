#pragma once

namespace Source::Enums
{
	//������Ʈ �� ���� �켱 ����
	enum class ComponentType
	{
		Transform,
		Renderer,
		Script,
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
		//
		MAX = 16
	};

	enum class ResourceType
	{
		Texture,
		//Mesh,
		//Video,
		AudioClip,
		Prefab,
		END
	};
}