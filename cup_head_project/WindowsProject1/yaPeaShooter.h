#pragma once
#include "yaBullet.h"
namespace ya
{
	class Animator;
	class PeaShooter:public Bullet
	
	{
	public:
		PeaShooter(Vector2 dir, bool special = false);
		~PeaShooter();
		
		static float GetCoolTime() { return CoolTime; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

	private:
		float mSpeed;
		float mAliveTimeChecker;
		float mEXDamageTimeChecker;
		float mEXDeathTimeChecker;

		int mHitCount;

		static float AliveTime;
		static float CoolTime;
	};
}
