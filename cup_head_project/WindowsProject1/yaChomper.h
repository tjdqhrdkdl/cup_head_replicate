#pragma once
#include "Common.h"
#include "yaMonster.h"

namespace ya
{

	class Chomper : public Monster
	{
	public:
		Chomper();
		~Chomper();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void ArriveCompleteEvent();
		void GroundBurstCompleteEvent();

		void Release();

	private:
		Collider* mCollider;
		Animator* mVineAnimator;
		float mSpeed;

		bool mbIsSeed;

	};
}
