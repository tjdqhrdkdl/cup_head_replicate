#pragma once
#include "Common.h"

namespace ya {

	class Collider;
	class Scene;
	class GameObject;
	class CollisionManager
	{
	public:
		static void Tick();
		static void SetLayer(eColliderLayer left, eColliderLayer right, bool value);
		static void LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right);
		static bool Intersect(Collider* left, Collider* right);


		static void ColliderCollision(Collider* left, Collider* right);
		static std::map<UINT64, bool>* GetCollisionInfo() { return &mCollisionInfo; }

	private:
		static WORD mMatrix[_COLLIDER_LAYER];
		static std::map<UINT64, bool> mCollisionInfo;
	};
}