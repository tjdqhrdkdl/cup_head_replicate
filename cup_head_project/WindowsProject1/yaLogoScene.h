#pragma once
#include "yaScene.h"

namespace ya {
	class Animation;
	class LogoScene : public Scene
	{
		public:
			LogoScene();
			~LogoScene();

			virtual void Initialize() override ;
			virtual void Tick() override;
			virtual void Render(HDC hdc) override;

			void SetReady() { mbReady = true; }
			void PlayBGM();

			virtual void Enter();
			virtual void Exit();

	private:
		GameObject* mReady;
		GameObject* mLogo;

		Sound* mBGM;
		bool mbReady;
	};
}
