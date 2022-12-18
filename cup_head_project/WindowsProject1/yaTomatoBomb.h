#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class TomatoBomb : public GameObject
	{
	public:

		TomatoBomb(bool right = false);
		~TomatoBomb();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void ExplodeCompleteEvent();

		void Release();

	private:
		Animator* mAnimator;

		float mDegree;

		bool mbRight;
	};
}
