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
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)LayerType::MAX; row++)
		{
			for (UINT col = 0; col < (UINT)LayerType::MAX; col++)
			{
				if (_collisionLayerMatrix[row][col])
				{
					LayerCollision(scene, (LayerType)row, (LayerType)col);

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

	// 레이어 간 충돌 체크를 위한 매트릭스 설정(SetCollisionLayer라 명명하는게 나을 수도)
	void CollisionManager::CollisionLayerCheck(LayerType left, LayerType right, bool isEnable)
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

	void CollisionManager::LayerCollision(class Scene* scene, LayerType left, LayerType right)
	{
		const std::vector<GameObject*>& leftObjects = scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rightObjects = scene->GetLayer(right)->GetGameObjects();

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
		Transform* leftTransform = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTransform = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPosition = leftTransform->GetPosition() + left->GetOffset();
		Vector2 rightPosition = rightTransform->GetPosition() + right->GetOffset();

		// size 1,1 일 기본크기가 100픽셀이라고 가정, 추후 확인 필요
		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		ColliderType leftType = left->GetColliderType();
		ColliderType rightType = right->GetColliderType();

		//AABB 충돌 알고리즘
		if (leftType == ColliderType::Box2D && rightType == ColliderType::Box2D)
		{
			//Box와 Box
			if (fabs(leftPosition.x - rightPosition.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f) && 
				fabs(leftPosition.y - rightPosition.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
			{
				return true;
			}
		}
		else if (leftType == ColliderType::Circle2D && rightType == ColliderType::Circle2D)
		{
			//Circle과 Circle
			Vector2 leftCirclePosition = leftPosition + (leftSize / 2.0f);
			Vector2 rightCirclePosition = rightPosition + (rightSize / 2.0f);
			
			float distance = (leftCirclePosition - rightCirclePosition).Length();

			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}
		}
		else if ((leftType == ColliderType::Circle2D && rightType == ColliderType::Box2D) || 
			(leftType == ColliderType::Box2D && rightType == ColliderType::Circle2D))
		{
			//Circle과 Box
			Vector2 circlePosition; //원의 중점
			Vector2	boxPosition;
			Vector2 boxSize;

			float circleRadius;

			if (leftType == ColliderType::Circle2D)
			{
				circlePosition = leftPosition + (leftSize / 2.0f);
				boxPosition = rightPosition;
				boxSize = rightSize;
				circleRadius = leftSize.x / 2.0f;
			}
			else
			{
				circlePosition = rightPosition + (rightSize / 2.0f);
				boxPosition = leftPosition;
				boxSize = leftSize;
				circleRadius = rightSize.x / 2.0f;
			}

			Vector2 boxCenter = boxPosition + boxSize / 2.0f;

			//사각형 내부에서 원과 가장 가까운 점
			Vector2 closestPoint;
			float boxMin = boxCenter.x - boxSize.x / 2.0f;
			float boxMax = boxCenter.x + boxSize.x / 2.0f;

			closestPoint.x = (circlePosition.x < boxMin) ? boxMin :
				(circlePosition.x > boxMax) ? boxMax : circlePosition.x;

			boxMin = boxCenter.y - boxSize.y / 2.0f;
			boxMax = boxCenter.y + boxSize.y / 2.0f;

			closestPoint.y = (circlePosition.y < boxMin) ? boxMin :
				(circlePosition.y > boxMax) ? boxMax : circlePosition.y;

			Vector2 difference = circlePosition - closestPoint;
			if (difference.x * difference.x + difference.y * difference.y <= circleRadius * circleRadius)
			{
				return true; // 충돌 발생
			}
		}

		return false;
	}
}

