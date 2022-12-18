#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaWernerWermanPh3.h"
namespace ya
{

	class Animator;
	class GhostMouse : public Monster
	{
	public:

		GhostMouse(bool right);
		~GhostMouse();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SummonBall();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;
		
		void SetOwnerCat(WernerWermanPh3* cat) { mOwnerCat = cat; }


		void GhostMouseIntroCompletEvent();
		void GhostMouseAttackIntroCompleteEvent();
		void GhostMouseAttackOutroCompleteEvent();
		void GhostMouseDeathCompleteEvent();

		void Release();

	private:
		float mBallTime;
		float mBallTimeChecker;
		WernerWermanPh3* mOwnerCat;
		Collider* mCollider;

		bool mbRight;
		bool mbIntro;

	};
}
