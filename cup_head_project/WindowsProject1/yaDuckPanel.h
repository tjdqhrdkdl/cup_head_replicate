#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya
{

	class Animator;
	class DuckPanel : public GameObject
	{
	public:

		DuckPanel(bool pink = false);
		~DuckPanel();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;

	private:
		float mSpeed;
		float mAliveTime;
		float mAliveTimeChecker;
		Animator* mAnimator;
		Picture* mPicture;

		bool mSpin;
		bool mPink;
		bool mDown;
	};
}
