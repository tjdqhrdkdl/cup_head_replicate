#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class RollerCoasterHead : public GameObject
	{
	public:

		RollerCoasterHead();
		~RollerCoasterHead();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


	private:
		Collider* mCollider;

		Animator* mAnimator;
	};
}
