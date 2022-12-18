#pragma once
#include "Common.h"
#include "yaMonster.h"
namespace ya
{

	class Animator;
	class Collider;
	class CatBody;
	class WernerWermanPh3 : public Monster
	{
	public:

		WernerWermanPh3(bool init = false);
		~WernerWermanPh3();


		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Move();
		void Attack();
		void Jail();
		void SummonWoodPieces(bool right);

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void PawOutroFin();

		void SetPhase2Object(GameObject* phase2) { mBeforePhaseToDelete = phase2; }
		void DeleteGhostMouse(bool left) { if (left)mLeftGhostMouse = nullptr; else mRightGhostMouse = nullptr; }
		void SetPawBack() { mbPawBack = true; }

		void CatFirstIntroCompleteEvent();
		void CatSecondIntroCompleteEvent();
		void CatThirdIntroCompleteEvent();

		void HeadIdleRightCompletEvent();
		void HeadIdleLeftCompletEvent();
		void HeadJailCompletEvent();

		void ClawHeadIntroCompleteEvent();
		void ClawHeadOutroCompleteEvent();
		

		void Release();

	private:
		GameObject* mBeforePhaseToDelete;
		GameObject* mLeftGhostMouse;
		GameObject* mRightGhostMouse;
		CatBody* mCatBody;

		Animator* mHeadAnimator;

		Collider* mCollider;
		Collider* mHeadCollider;

		float mDeathEffectTimeChecker;
		float mAttackTimeChecker;

		bool mbPlayJail;
		bool mbPlayClawRight;
		bool mbPlayClawLeft;
		bool mbPawBack;
		UINT mGhostCount;
	};
}
