#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class TomatoFire : public GameObject
	{
	public:

		TomatoFire(bool right = false);
		~TomatoFire();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();

	private:
		Animator* mAnimator;
	};
}
