#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class Ph2WallGround : public GameObject
	{
	public:
		Ph2WallGround();
		~Ph2WallGround();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void FreePlayers();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

	private:
		std::vector<Player*> mOnPlayer;
	};
}
