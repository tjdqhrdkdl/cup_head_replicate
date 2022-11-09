#pragma once
#include "yaScene.h"

namespace ya {
	class BossBeppiScene : public Scene
	{
	public:
		BossBeppiScene();
		~BossBeppiScene();


		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();
	};
}
