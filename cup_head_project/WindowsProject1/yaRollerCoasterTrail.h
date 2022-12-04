#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class RollerCoasterTrail : public GameObject
	{
	public:

		RollerCoasterTrail(bool blue, bool person);
		~RollerCoasterTrail();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


	private:
		bool misBlue;
		bool mWithPassenger;
		Collider* mCollider;
		float mAliveTime;
		float mAliveTimeChecker;

		Animator* mBackAnimator;
		Animator* mChairAnimator;
		Animator* mPersonXAnimator1;
		Animator* mPersonYAnimator1;
		Animator* mPersonXAnimator2;
		Animator* mPersonYAnimator2;
		Animator* mFrontAnimator;
	};
}
