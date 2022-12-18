#include "yaScene.h"
#include "yaCamera.h"

#include "yaApplication.h"

namespace ya {
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		Release();
		ReleaseCameraObj();
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
				if (y < mObjects[x].size())
				{
					if (mObjects[x][y]->isLayerChanged())
					{
						mObjects[x][y]->SetLayerChange(false);
						continue;
					}
					if (mObjects[x][y] != nullptr)
						mObjects[x][y]->Tick();
				}
			}
		}

	}

	void Scene::Render(HDC hdc)
	{
		for (size_t x = 0; x < _COLLIDER_LAYER; x++)
		{
			for (size_t y = 0; y < mObjects[x].size(); y++)
			{
				if (mObjects[x][y] == nullptr)
					continue;
				if (mObjects[x][y]->IsDeath())
					continue;


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

	void Scene::Release()
	{
		for (size_t x = 0; x < _COLLIDER_LAYER-1; x++)
		{
			for (size_t y = 0; y < mObjects[x].size(); y++)
			{
				delete mObjects[x][y];
			}
			mObjects[x].clear();
		}
	}

	void Scene::ReleaseCameraObj()
	{
		for (size_t y = 0; y < mObjects[_COLLIDER_LAYER-1].size(); y++)
		{
			mObjects[_COLLIDER_LAYER - 1].erase(mObjects[_COLLIDER_LAYER - 1].begin() + y);
		}
		mObjects[_COLLIDER_LAYER - 1].clear();
	}

	void Scene::AddGameObject(GameObject* gameobject, eColliderLayer type)
	{
		gameobject->SetLayer(type);
		gameobject->Initialize();
		mObjects[(UINT)type].push_back(gameobject);
	}

	void Scene::DeleteGameObject(GameObject* target)
	{
		for (size_t i = 0; i < _COLLIDER_LAYER; i++)
		{
			mObjects[i].erase(remove(mObjects[i].begin(), mObjects[i].end(), target), mObjects[i].end());
		}
	}
	void Scene::ChangeLayer(GameObject* gameobject, eColliderLayer newtype)
	{
		eColliderLayer curtype = gameobject->GetLayer();
		if (curtype == newtype)
			return;
		else
		{
			mObjects[(UINT)curtype].erase(remove(mObjects[(UINT)curtype].begin()
				, mObjects[(UINT)curtype].end(), gameobject), mObjects[(UINT)curtype].end());
			mObjects[(UINT)newtype].push_back(gameobject);
			gameobject->SetLayer(newtype);
			gameobject->SetLayerChange(true);
		}
	}
	
}