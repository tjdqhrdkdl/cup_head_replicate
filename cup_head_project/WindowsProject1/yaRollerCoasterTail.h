#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class RollerCoasterTail : public GameObject
	{
	public:

		RollerCoasterTail();
		~RollerCoasterTail();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();

	private:
		float mAliveTime;
		float mAliveTimeChecker;

		Animator* mBackAnimator;
		Animator* mFrontAnimator;
	};
}
