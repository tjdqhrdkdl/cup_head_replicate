#pragma once
#include "yaScene.h"

namespace ya {
	class MapScene : public Scene
	{
	public:
		MapScene();
		~MapScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();

	};
}
