#include "MyCollisionManager.h"
#include "MyCollider.h"
#include "MyScene.h"
#include "MySceneManager.h"
#include "MyGameObject.h"
#include "MyTransform.h"

namespace Source
{
	std::bitset<(UINT)LayerType::MAX> CollisionManager::_collisionLayerMatrix[(UINT)LayerType::MAX] = {};
	std::unordered_map<UINT64, bool> CollisionManager::_collisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT row = 0; row < (UINT)LayerType::MAX; row++)
		{
			for (UINT col = 0; col < (UINT)LayerType::MAX; col++)
			{
				if (_collisionLayerMatrix[row][col])
				{
					LayerCollision((LayerType)row, (LayerType)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::Clear()
	{
		_collisionMap.clear();

		for (UINT i = 0; i < (UINT)LayerType::MAX; i++)
		{
			_collisionLayerMatrix[i].reset();
		}
	}

	// 레이어 간 충돌 체크를 위한 매트릭스 설정
	void CollisionManager::SetCollisionLayerMatrix(LayerType left, LayerType right, bool isEnable)
	{
		UINT row = 0;
		UINT col = 0;

		//레이어 매트릭스는 대칭 행렬이기에 대칭 중 한 쪽만 체크하도록 한다.
		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		_collisionLayerMatrix[row][col] = isEnable;
	}

	void CollisionManager::LayerCollision(LayerType left, LayerType right)
	{
		const std::vector<GameObject*>& leftObjects = SceneManager::GetGameObjectsOnScene(left);
		const std::vector<GameObject*>& rightObjects = SceneManager::GetGameObjectsOnScene(right);

		for (GameObject* leftObject : leftObjects)
		{
			if (!leftObject->IsActive())
			{
				continue;
			}

			Collider* leftCollider = leftObject->GetComponent<Collider>();
			if (leftCollider == nullptr)
			{
				continue;
			}

			for (GameObject* rightObject : rightObjects)
			{
				if (!rightObject->IsActive() ||
					leftObject == rightObject)
				{
					continue;
				}

				Collider* rightCollider = rightObject->GetComponent<Collider>();
				if (rightCollider == nullptr)
				{
					continue;
				}

				CheckCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::CheckCollision(Collider* left, Collider* right)
	{
		//두 충돌체의 ID를 확인 후 검색
		CollisionID collisionID = {};
		collisionID.left = left->GetCollisionID();
		collisionID.right = right->GetCollisionID();

		auto iterator = _collisionMap.find(collisionID.id);
		if (iterator == _collisionMap.end())
		{
			_collisionMap.insert(std::make_pair(collisionID.id, false));
			iterator = _collisionMap.find(collisionID.id);
		}

		//충돌 체크
		if (Intersect(left, right))
		{
			if (iterator->second == false)
			{
				//충돌이 발생했을 때
				iterator->second = true;
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else
			{
				//충돌이 발생 중
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iterator->second == true)
			{
				//충돌이 종료되었을 때
				iterator->second = false;
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		return left->Intersect(right);
	}
}

