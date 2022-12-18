#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaRollerCoasterHeadPinkNose.h"
namespace ya
{

	class Animator;
	class RollerCoasterHead : public GameObject
	{
	public:

		RollerCoasterHead();
		~RollerCoasterHead();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		RollerCoasterHeadPinkNose* GetNose() { return mPinkNose; }

		void Release();
	private:
		Collider* mCollider;
		Animator* mAnimator;
		float mAliveTime;
		float mAliveTimeChecker;

		RollerCoasterHeadPinkNose* mPinkNose;
	};
}
