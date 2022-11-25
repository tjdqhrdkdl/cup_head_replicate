#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class SceneEnter : public GameObject
	{
	public:
		SceneEnter();
		~SceneEnter();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;
	};
}