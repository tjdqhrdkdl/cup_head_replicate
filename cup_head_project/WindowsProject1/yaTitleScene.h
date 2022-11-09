#pragma once
#include "yaScene.h"

namespace ya 
{
	class BgImageObject;
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();
	private:
		BgImageObject* mBGI;
	};
}
