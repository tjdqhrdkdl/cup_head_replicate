#pragma once
#include "yaScene.h"

namespace ya {
	class LogoScene : public Scene
	{
		public:
			LogoScene();
			~LogoScene();

			virtual void Initialize() override ;
			virtual void Tick() override;
			virtual void Render(HDC hdc) override;


			virtual void Enter();
			virtual void Exit();

	};
}
