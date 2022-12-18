#pragma once
#include "Common.h"
#include "yaGameobject.h"

namespace ya
{

	class Animator;
	class Collider;
	class Disc : public GameObject
	{
	public:

		Disc(bool right);
		~Disc();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;
		
		void SetGo() { if (!mbMoving) { mbGoBack = true; mbMoving = true; } }

		void SetFin(bool fin) { mbFin = fin; }

		void Release();

	private:
		Animator* mAnimator;
		Animator* mStickAnimator;

		Collider* mCollider;

		bool mbRight;
		bool mbIntro;
		bool mbGoBack;
		bool mbGoFront;
		bool mbMoving;
		bool mbSpeedDown;
		bool mbFin;
		float mSpeed;
	};
}
