#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class CatBody : public GameObject
	{
	public:

		CatBody();
		~CatBody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		void SetDeath();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void TailIdleComplete();
		

		void Release();

	private:
		Animator* mLeftArmAnimator;;
		Animator* mRightArmAnimator;
		Animator* mBodyAnimator;;
		Animator* mTailAnimator;

	};
}
