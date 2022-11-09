#pragma once
#include "yaBullet.h"
namespace ya
{
	class Animator;
	class PeaShooter:public Bullet
	
	{
	public:
		PeaShooter();
		~PeaShooter();
		
		static float GetCoolTime() { return CoolTime; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
		float mAliveTimeChecker;
		Animator* mAnimator;

		static float AliveTime;
		static float CoolTime;
	};
}
