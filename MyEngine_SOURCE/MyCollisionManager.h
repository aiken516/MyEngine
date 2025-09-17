#pragma once

#include "CommonInclude.h"
#include "MyCollider.h"

namespace Source
{
	using namespace Enums;

	union CollisionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};

		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

		static void Clear();

		static void SetCollisionLayerMatrix(LayerType left, LayerType right, bool isEnable);
		static void LayerCollision(LayerType left, LayerType right);

		static void CheckCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		static std::bitset<(UINT)LayerType::MAX> _collisionLayerMatrix[(UINT)LayerType::MAX];
		static std::unordered_map<UINT64, bool> _collisionMap;
	};
}



