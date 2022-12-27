#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPicture.h"
#include "yaLightBulb.h"

namespace ya
{

	class Animator;
	class DuckPanel : public Monster
	{
	public:

		DuckPanel(bool pink = false, LightBulb* bulb = nullptr);
		~DuckPanel();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();
	private:
		float mSpeed;
		float mAliveTime;
		float mAliveTimeChecker;
		Animator* mAnimator;
		Picture* mPicture;

		LightBulb* mBulb;
		Collider* mBulbDropCollider;
		bool mSpin;
		bool mDown;
	};
}
