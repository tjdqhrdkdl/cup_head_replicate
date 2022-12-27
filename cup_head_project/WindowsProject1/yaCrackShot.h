#pragma once
#include "yaBullet.h"
namespace ya
{
	class Animator;
	class CrackShot :public Bullet

	{
	public:
		CrackShot(Vector2 dir, bool special = false);
		~CrackShot();

		static float GetCoolTime() { return CoolTime; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void BulletCometIntroCompleteEvent();
		void EXLaunchCompleteEvent();
		void EXSpinCompleteEvent();

	private:
		float mSpeed;
		float mAliveTimeChecker;
		float mEXShootTimeChecker;
		float mCrackTimeChecker;

		bool mbCrack;

		Vector2 mDestDir;
		ShootEffect* mCrackShootEffect;

		static float AliveTime;
		static float CoolTime;
		static float BulletDamage;
		static float EXDamage;
	};
}
