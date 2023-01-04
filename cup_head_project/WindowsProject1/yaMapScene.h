#pragma once
#include "yaScene.h"

namespace ya 
{
	class BgImageObject;
	class WorldPlayer;
	class WorldMap;
	class Sound;
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
	private:
		BgImageObject* mBGI;
		BgImageObject* mBGITopperLeft;
		BgImageObject* mBGITopperRight;
		WorldPlayer* mWorldPlayer;
		WorldMap* mWorldMap;

		Sound* mBGM;

	};
}
