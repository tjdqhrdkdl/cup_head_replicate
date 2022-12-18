#pragma once
#include "Common.h"
#include "yaGameobject.h"
namespace ya
{

	class Animator;
	class Player;
	class BottomWoodCart : public GameObject
	{
	public:

		BottomWoodCart();
		~BottomWoodCart();


		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Move(Vector2 pos);

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		Animator* GetAnimator() { return mAnimator; }
		void Release();
	private:
		float mSpeed;
		Animator* mAnimator;
		Collider* mGroundCollider;

		std::vector<Player*> mOnPlayer;
	};
}
