#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Number : public GameObject
	{
	public:
		Number();
		~Number();
		Animator* GetAnimator() { return mAnimator; }
		void SetStopIndex(UINT index) { mStopIndex = index; }
		UINT GetStopIndex() { return mStopIndex; }
		bool GetFin() { return mbFin; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAnimator;
		UINT mStopIndex;
		bool mbFin;
	};
}
