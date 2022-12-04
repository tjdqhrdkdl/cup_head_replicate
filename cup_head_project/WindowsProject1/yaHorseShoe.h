#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class BeppiPhaseThree;
	class HorseShoe : public GameObject
	{
	public:

		HorseShoe(bool yellow, bool right, bool pink = false);
		~HorseShoe();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Move();
		void SetStopXPos(float x) { mStopXPos = x; }
		void SetBeppi(BeppiPhaseThree* beppi) { mOwnerBeppi = beppi; }

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		Animator* GetAnimator() { return mAnimator; }

	private:
		bool mbRight;
		bool mbYellow;

		bool mbComeBack;
		bool mbStop;
		bool mbDropSoon;
		bool mbDrop;

		float mStopXPos;
		float mDropTimeChecker;

		Vector2 mDir;
		float mDegree;
		bool mbDirChange;

		float mSpeed;
		float mAliveTime;
		float mAliveTimeChecker;
		Animator* mAnimator;
		BeppiPhaseThree* mOwnerBeppi;
	};
}
