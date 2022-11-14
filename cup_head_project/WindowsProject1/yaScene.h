#pragma once
#include "Common.h"
#include "yaGameObject.h"
namespace ya {
	class Scene
	{
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);
		
		virtual void Enter();
		virtual void Exit();

		void AddGameObject(GameObject* gameobject , eColliderLayer type);
		void DeleteGameObject(GameObject* target);

		std::vector<GameObject*> GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<GameObject*>* GetGameObjects() { return mObjects; }

	private:
		std::vector<GameObject*> mObjects[_COLLIDER_LAYER];
		
	};
}
