#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya {

	class WorldPlayer;
	class WorldMap : public GameObject
	{
	public:
		WorldMap();
		~WorldMap();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetPlayer(WorldPlayer* pl) { mWorldPlayer = pl; }

	
	private:
		Picture* mBackImage;
		WorldPlayer* mWorldPlayer;
	};
}
