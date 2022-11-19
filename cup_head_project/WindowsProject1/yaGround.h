#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Ground : public GameObject
	{
	public:
		Ground();
		~Ground();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;

	private:
		Player* mPlayer;
	};
}
