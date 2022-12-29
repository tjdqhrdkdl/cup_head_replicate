#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Player;
	class Collider;
	class FlowerPlatForm : public GameObject
	{
	public:
		FlowerPlatForm();
		~FlowerPlatForm();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();

	private:
		Animator* mAnimator;
		Animator* mPropellerAnimator;
		Collider* mCollider;

		bool mbUp;


		std::vector<Player*> mOnPlayer;
	};
}
