#pragma once
#include "Common.h"
#include "yaEntity.h"
namespace ya {

	class GameObject;
	class Component:public Entity
	{
	public:
		friend class GameObject;
		Component(eComponentType type);
		Component() = delete;
		virtual ~Component();
		virtual void Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Render(HDC hdc);

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
		eComponentType GetType() { return mType; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}
