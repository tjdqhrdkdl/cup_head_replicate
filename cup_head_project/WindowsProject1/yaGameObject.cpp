#include "yaGameObject.h"
#include "yaTime.h"
namespace ya {
	GameObject::GameObject()
		:mPos(0.0f, 0.0f)
		, mScale(1.0f, 1.0f)
	{
	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			delete component;
			component = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* component : mComponents)
		{
			component->Initialize();
		}
	}

	void GameObject::Tick()
	{

		DeathLoop();

		for (std::vector<Component*>::iterator iter = mComponents.begin(); iter != mComponents.end(); iter++)
		{
			(* iter)->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* component: mComponents)
		{
			component->Render(hdc);
		}
	}

	void GameObject::SetDeathTime(float time)
	{
		if (mDeathTime <= 0.0f)
		{
			mDeathTime = time;
			mDeathTimeOn = true;
		}
	}

	void GameObject::OnCollisonEnter(Collider* other)
	{
	}

	void GameObject::OnCollisonStay(Collider* other)
	{
	}

	void GameObject::OnCollisonExit(Collider* other)
	{
	}

	Component* GameObject::GetComponent(eComponentType type)
	{
		Component* ret = nullptr;

		for (Component* component : mComponents)
		{
			if(component->GetType() == type)
			{
				ret = component;
				break;
			}
		}

		return ret;
	}
	void GameObject::DeathLoop()
	{
		if (mDeathTimeOn == true)
		{
			mDeathTime -= Time::DeltaTime();
			if (mDeathTime <= 0.0f)
				Death();
		}
		
	}
}