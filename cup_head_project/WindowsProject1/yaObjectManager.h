#pragma once
#include "yaScene.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"

namespace ya
{
	namespace ObjectManager
	{
		template <typename T>
		static __forceinline T* Instantiate(Scene* scene, eColliderLayer type)
		{
			T* gameObject = new T();
			gameObject->Initialize();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		template <typename T>
		static __forceinline T* Instantiate(Scene* scene, Vector2 position, eColliderLayer type)
		{
			T* gameObject = new T(position);
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		static __forceinline void Destroy(GameObject* gameObj)
		{
			gameObj->Death();
		}

		// 시간 측정해서 지우기
		static __forceinline void Destroy(GameObject* gameObj, float deathTime)
		{
			gameObj->SetDeathTime(deathTime);
		}

		static __forceinline void Release()
		{
			Scene* scene = SceneManager::GetCurScene();

			for (size_t y = 0; y < _COLLIDER_LAYER; y++)
			{
				for (std::vector<GameObject*>::iterator iter = scene->GetGameObjects()[y].begin()
					; iter != scene->GetGameObjects()[y].end();)
				{
					if ((*iter)->IsDeath() == true)
					{
						GameObject* obj = *iter;
						iter = scene->GetGameObjects()[y].erase(iter);
						delete obj;
						obj = nullptr;
						continue;
					}
					++iter;
				}
			}
		}

	}
}