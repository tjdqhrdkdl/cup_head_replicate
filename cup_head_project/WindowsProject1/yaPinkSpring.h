#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class PinkSpring : public GameObject
	{
	public:

		PinkSpring(float degree, bool right = false);
		~PinkSpring();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		
		
		
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void LandCompleteEvent();
		void DeathCompleteEvent();

		void Release();

	private:
		Animator* mAnimator;

		float mDegree;

		bool mbRight;
	};
}
