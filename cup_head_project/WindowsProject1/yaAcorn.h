#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class Acorn : public GameObject
	{
	public:

		Acorn();
		~Acorn();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetShootTime(float time) { mShootTime = time; }
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void DeathCompleteEvent();
		void Release();

	private:
		float mAliveTime;
		float mAliveTimeChecker;
		float mRotationTimeChecker;
		float mSpeed;
		float mShootTime;
		Animator* mAnimator;
		Vector2 mDestDir;

	};
}
