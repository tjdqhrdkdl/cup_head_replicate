#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya 
{

	class Animator;
	class Enemy : public GameObject
	{
	public:

		Enemy();
		Enemy(Vector2 position);
		~Enemy();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;
	private:
		float mSpeed;
		Animator* mAnimator;
		bool onHit;
		float onHitChecker;
	};
}
