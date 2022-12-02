#pragma once
#include "Common.h"
#include "yaMonster.h"

namespace ya
{

	class Animator;
	class BalloonDog : public Monster
	{
	public:

		BalloonDog(Vector2 dir , bool pink = false);
		~BalloonDog();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetDestDir(Vector2 dir) { mDestDir = dir; }
		
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void ApearCompleteEvent();
		void PopCompleteEvent();


	private:
		float mAliveTime;
		float mAliveTimeChecker;
		float mSpeed;

		Collider* mCollider;
		Vector2 mDir;
		Vector2 mDestDir;
	};
}
