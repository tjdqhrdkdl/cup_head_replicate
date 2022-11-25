#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class SceneExit : public GameObject
	{
	public:
		SceneExit(eSceneType type);
		~SceneExit();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AnimCompleteEvent();

	private:
		Animator* mAnimator;
		eSceneType mType;
	};
}