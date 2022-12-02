#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "yaComponent.h"

namespace ya {

	class Collider;
	class GameObject :public Entity
	{
	public:
		GameObject();
		~GameObject();
		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);
		void SetPos(Vector2 vec) { mPos = vec; }
		void SetScale(Vector2 vec) { mScale = vec; }
		void SetLayer(eColliderLayer layer) { mLayer = layer; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }
		eColliderLayer GetLayer() { return mLayer; }
		void Death() { mDead = true; }
		bool IsDeath() { return mDead; }
		void SetDeathTime(float time);
		bool IsDeathTimeOn() { return mDeathTimeOn; }
		float GetDeathTime() { return mDeathTime; }


		virtual void OnCollisonEnter(Collider* other, Collider* my);
		virtual void OnCollisonStay(Collider* other, Collider* my);
		virtual void OnCollisonExit(Collider* other, Collider* my);

		void AddComponent(Component* c) { c->SetOwner(this); mComponents.push_back(c); }

		Component* GetComponent(Component*);
		Component* GetComponent(eComponentType type);
		template <typename T>
		T* GetComponent()
		{
			for (auto c : mComponents)
			{
				T* component = dynamic_cast<T*>(c);
				if (component != nullptr)
					return component;
			}
			return nullptr;
		}		
		template <typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};
			for (auto c : mComponents)
			{
				T* component = dynamic_cast<T*>(c);
				if (component != nullptr)
					components.push_back(component);
			}
			return components;
		}

		void DeathLoop();


		bool isParryable() { return mPink; }
		void SetParried(bool parry) { mParried = parry; }
		bool isParried() { return mParried; }
		bool isLayerChanged() { return mLayerChanged; }
		void SetLayerChange(bool b) { mLayerChanged = b; }
	private:
		std::vector<Component*> mComponents;
		Vector2 mPos;
		Vector2 mScale;
		bool mDead;
		eColliderLayer mLayer;
		float mDeathTime;
		bool mDeathTimeOn;

	protected:
		bool mPink;
		bool mParried;
		bool mLayerChanged;
	};
}
