#include "yaScene.h"

namespace ya {
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		for (size_t x = 0; x < _COLLIDER_LAYER; x++)
		{
			for (size_t y = 0; y < mObjects[x].size(); y++)
			{
				delete mObjects[x][y];
				mObjects[x][y] = nullptr;
			}
		}

	}

	void Scene::Initialize()
	{
		for (size_t x = 0; x < _COLLIDER_LAYER; x++)
		{
			for (size_t y = 0; y < mObjects[x].size(); y++)
			{
				mObjects[x][y]->Initialize();
			}
		}
	}

	void Scene::Tick()
	{
		for (size_t x = 0; x < _COLLIDER_LAYER; x++)
		{
			for (size_t y = 0; y < mObjects[x].size(); y++)
			{
				mObjects[x][y]->Tick();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (size_t x = 0; x < _COLLIDER_LAYER; x++)
		{
			for (size_t y = 0; y < mObjects[x].size(); y++)
			{
				mObjects[x][y]->Render(hdc);
			}
		}
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
	}

	void Scene::AddGameObject(GameObject* gameobject, eColliderLayer type)
	{
		gameobject->SetLayer(type);
		mObjects[(UINT)type].push_back(gameobject);
	}

	void Scene::DeleteGameObject(GameObject* target)
	{
		for (size_t i = 0; i < _COLLIDER_LAYER; i++)
		{
			mObjects[i].erase(remove(mObjects[i].begin(), mObjects[i].end(), target), mObjects[i].end());
		}
	}
}