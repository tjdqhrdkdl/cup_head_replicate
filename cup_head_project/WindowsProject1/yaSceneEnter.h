#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class Scene;
	class SceneEnter : public GameObject
	{
	public:
		SceneEnter(Scene* prev);
		~SceneEnter();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;

		Scene* mPrevScene;
	};
}