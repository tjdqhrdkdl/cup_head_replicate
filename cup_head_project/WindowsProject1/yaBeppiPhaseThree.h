#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaBeppiHorse.h"
#include "yaBeppiPhaseThreeBack.h"
namespace ya
{

	class Collider;
	class BeppiPhaseThree : public Monster
	{
	public:
		BeppiPhaseThree(bool init = false);
		~BeppiPhaseThree();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		bool IsDropShoes() { return mbYellowDrop; }

		void PatternChoice();
		void Move();
		void Attack();
		void SummonCoaster();

		void EndDropCompleteEvent();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

	private:
		Collider* mCollider;
		BeppiHorse* mHorse;
		BeppiPhaseThreeBack* mBackAnimation;

		bool mbRight;
		bool mbYellowHorse;
		bool mbGoUp;
		bool mbGoDown;
		bool mbEndFall;

		float mAttackTimeChecker;
		float mShoeTimeChecker;
		float mGreenShoeSetTimeChecker;
		bool mbYellowDrop;

		float mCoasterTime;
		float mCoasterTimeChecker;

		float mDeathEffectTimeChecker;

		UCHAR mYellowShoeBlankIndex[3];
		UCHAR mShoeCounter;
		UCHAR mGreenShoeSetCounter;
	};
}
