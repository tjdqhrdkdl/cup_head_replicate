#pragma once
#include "Common.h"
#include "yaGameObject.h"
namespace ya 
{
	class Collider;
	class Sound;
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
		void ReleaseCameraObj();

		Collider* GetNearestCollider(GameObject* base, eColliderLayer targetLayer);

		void AddGameObject(GameObject* gameobject , eColliderLayer type);
		void DeleteGameObject(GameObject* target);
		bool isIntro() { return misIntro; }
		void SetIntro(bool b) { misIntro = b; }
		void SetStart(bool start) { mbStart = true; }
		void ChangeLayer(GameObject* gameobject, eColliderLayer newtype);

		std::vector<GameObject*> GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<GameObject*>* GetGameObjects() { return mObjects; }

		UINT mParryCount;
		UINT mSuperCount;
		UINT mHPCount;
	protected:
		std::vector<GameObject*> mObjects[_COLLIDER_LAYER];
		bool misIntro;
		bool mbStart;
		bool mbSceneChanging;

		float mTime;



	};
}
