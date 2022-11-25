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

		void Release();

		void AddGameObject(GameObject* gameobject , eColliderLayer type);
		void DeleteGameObject(GameObject* target);
		bool isIntro() { return misIntro; }
		void SetIntro(bool b) { misIntro = b; }
		std::vector<GameObject*> GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<GameObject*>* GetGameObjects() { return mObjects; }

	protected:
		std::vector<GameObject*> mObjects[_COLLIDER_LAYER];
		bool misIntro;
	};
}
