#pragma once
#include "Common.h"
#include "yaMonster.h"

namespace ya
{

	class Animator;
	class Penguin : public Monster
	{
	public:

		Penguin(UINT posNum);
		~Penguin();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SummonBaseBall();
		
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


		void CollisionGroundCompleteEvent();
		void GetUpCompleteEvent();
		void PopCompleteEvent();
		void ClapCompleteEvent();


		void Release();

	private:
		float mBallTime;
		float mBallTimeChecker;
		Collider* mCollider;

		bool mbGround;
		bool mbArrive;
		UINT mPositionNumber;

		UINT mRolloutPhase;

	};
}
