#pragma once
#include "Common.h"
#include "yaGameobject.h"
#include "yaWernerWermanPh3.h"
namespace ya
{

	class Animator;
	class Collider;
	class Paw : public GameObject
	{
	public:

		Paw(bool right);
		~Paw();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		void SetOwnerCat(WernerWermanPh3* cat) { mOwnerCat = cat; }

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;



		void PawMainCompleteEvent();


		void Release();

	private:
		WernerWermanPh3* mOwnerCat;
		Animator* mAnimator;

		Collider* mCollider;

		bool mbRight;

		UCHAR mHitCount;
	};
}
