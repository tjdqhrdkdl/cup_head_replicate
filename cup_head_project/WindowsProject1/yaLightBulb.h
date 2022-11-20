#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya
{

	class Animator;
	class LightBulb : public GameObject
	{
	public:

		LightBulb();
		~LightBulb();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		Animator* GetAnimator() { return mAnimator; }
		void SetHang(bool drop) { mHang = drop; }

		void ExplodeEndEvent();
	private:
		float mSpeed;
		float mAliveTime;
		float mAliveTimeChecker;
		Animator* mAnimator;
		Picture* mPicture;

		bool mHang;
		bool mExploded;
	};
}
