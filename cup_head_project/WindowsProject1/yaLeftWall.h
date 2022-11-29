#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class LeftWall : public GameObject
	{
	public:
		LeftWall();
		~LeftWall();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


	};
}
