#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Player;
	class Collider;
	class SwingPlatForm : public GameObject
	{
	public:
		SwingPlatForm(bool isStart = false);
		~SwingPlatForm();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();

	private:
		Animator* mAnimator;
		Collider* mCollider;
		bool mbGoUp;
		bool mbStart;

		std::vector<Player*> mOnPlayer;
	};
}
