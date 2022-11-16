#pragma once
#include "yaBullet.h"
namespace ya
{
	class Animator;
	class PeaShooter:public Bullet
	
	{
	public:
		PeaShooter(Vector2 dir);
		~PeaShooter();
		
		static float GetCoolTime() { return CoolTime; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
		float mAliveTimeChecker;

		static float AliveTime;
		static float CoolTime;
	};
}
