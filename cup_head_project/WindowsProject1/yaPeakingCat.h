#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class PeakingCat : public GameObject
	{
	public:
		PeakingCat(Vector2 startPos, Vector2 destPos);
		~PeakingCat();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetPhase2ObjectToDelete(GameObject* phase2) {mbPhase3 = true, mPhase2Object = phase2; }

		void Reset(Vector2 startPos, Vector2 destPos);
		void CatIntroCompleteEvent();

		void SetOn(bool b) { mbOn = b; }
	private:
		Animator* mAnimator;

		Vector2 mDestPos;
		Vector2 mStartPos;
		Vector2 mDir;

		bool mbArrive;
		bool mbOn;
		bool mbGoPeak;
		bool mbPhase3;

		float mTime;
		GameObject* mPhase2Object;
	};
}
