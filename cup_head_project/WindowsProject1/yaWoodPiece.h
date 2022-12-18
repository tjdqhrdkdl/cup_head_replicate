#pragma once
#include "Common.h"
#include "yaGameobject.h"
#include "yaWernerWermanPh3.h"
namespace ya
{

	class Animator;
	class Collider;
	class WoodPiece : public GameObject
	{
	public:

		WoodPiece();
		~WoodPiece();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void DeathCompleteEvent();


		void Release();

	private:
		Animator* mAnimator;

		Collider* mCollider;

	};
}
