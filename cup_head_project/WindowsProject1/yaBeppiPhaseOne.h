#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya 
{

	class Animator;
	class BeppiPhaseOne : public GameObject
	{
	public:

		BeppiPhaseOne();
		BeppiPhaseOne(Vector2 position);
		~BeppiPhaseOne();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void Attack();
		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;
	private:
		float mSpeed;
		float mHp;
		bool mLookingLeft;

		Animator* mAnimator;
		bool onHit;
		float onHitChecker;
	};
}
