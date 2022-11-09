#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaCollider.h"

namespace ya {

	WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionInfo = {};
	void CollisionManager::Tick()
	{
		for (size_t row = 0; row < _COLLIDER_LAYER; row++)
		{
			for (size_t col = 0; col < _COLLIDER_LAYER; col++)
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(SceneManager::GetCurScene(), (eColliderLayer)row, (eColliderLayer)col);
				}
			}
		}
	}

	void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
	{
		UINT row = 0;
		UINT col = 0;
		if ((UINT)left < (UINT)right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		if (value == true)
			mMatrix[row] |= (1 << col);
		else
			mMatrix[row] &= ~(1 << col);


	}

	void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
	{
		std::vector<GameObject*> lefts = SceneManager::GetCurScene()->GetGameObjects(left);
		std::vector<GameObject*> rights = SceneManager::GetCurScene()->GetGameObjects(right);

		for (GameObject* leftObject : lefts)
		{
			Collider* leftCollider = leftObject->GetComponent<Collider>();
			if (leftCollider == nullptr)
				continue;

			for (GameObject* rightObject : rights)
			{
				Collider* rightCollider = rightObject->GetComponent<Collider>();
				if (rightCollider == nullptr)
					continue;
				
				if (leftObject == rightObject)
					continue;

				ColliderCollision(leftCollider, rightCollider);


			}
		}

	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPos();
		Vector2 rightPos = right->GetPos();

		Vector2 leftScale = left->GetScale();
		Vector2 rightScale = right->GetScale();
		if(fabs(leftPos.x-rightPos.x) < fabs(rightScale.x/2.0f+leftScale.x/2.0f) && 
			fabs(leftPos.y - rightPos.y) < fabs(rightScale.y / 2.0f + leftScale.y / 2.0f))
		{
			return true;
		}
		return false;
	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		CollisionId id = {};
		id.left = left->GetId();
		id.right = right->GetId();
		std::map<UINT64, bool>::iterator iter 
			= mCollisionInfo.find(id.ID);

		if (iter == mCollisionInfo.end())
		{
			mCollisionInfo.insert(std::make_pair(id.ID, false));
			iter = mCollisionInfo.find(id.ID);
		}

		if (Intersect(left, right))
		{

			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}
}