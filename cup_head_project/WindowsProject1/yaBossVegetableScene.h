#pragma once
#include "yaScene.h"

namespace ya {
	class BossVegetableScene : public Scene
	{
	public:
		BossVegetableScene();
		~BossVegetableScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();



	};
}
