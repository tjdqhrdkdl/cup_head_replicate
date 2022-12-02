#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPicture.h"
#include "yaBeppiPh2Body.h"
namespace ya
{

	class Animator;
	class RollerCoaster;
	class BeppiPhaseTwo : public Monster
	{
	public:
		BeppiPhaseTwo();
		~BeppiPhaseTwo();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Move();
		void SummonBalloonDogs();
		void SummonCoaster();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void SetBody(BeppiPh2Body* body) { mPh2Body = body; }
		void IntroBulkupCompleteEvent();
		void IntroBalloonCompleteEvent();
	private:
		BeppiPh2Body* mPh2Body;
		Collider* mCollider;
		bool mbMoveLeft;
		bool mbMoveDown;

		UCHAR mBalloonPoint;
		UCHAR mPinkBalloonCount;
		float mBalloonTime;
		float mBalloonTimeChecker;

		float mCoasterTime;
		float mCoasterTimeChecker;

		bool misIntroApear;
		float mDeathEffectTimeChecker;
	};
}
