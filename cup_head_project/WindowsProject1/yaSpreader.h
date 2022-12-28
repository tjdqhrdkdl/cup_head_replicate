#pragma once
#include "yaBullet.h"
namespace ya
{
	class Animator;
	class Player;
	class Spreader :public Bullet

	{
	public:
		Spreader(Vector2 dir, bool special = false);
		~Spreader();

		static float GetCoolTime() { return CoolTime; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		static void Shoot(Vector2 dir, Player* player, bool special = false);

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void SmokeIntroCompleteEvent();

	private:
		float mSpeed;
		float mAliveTimeChecker;
		float mEXShootTimeChecker;
		float mCrackTimeChecker;

		Animator* mSmokeAnimator;

		static float AliveTime;
		static float CoolTime;
		static float BulletDamage;
		static float EXDamage;
	};
}
