#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class BossObject : public GameObject
	{
	public:

		BossObject();
		~BossObject();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		Animator* GetAnimator() { return mAnimator; }
		Collider* GetCollider() { return mCollider; }

		eBossType mType;
		void Release();


	private:
		Animator* mAnimator;
		Collider* mCollider;
	};
}
