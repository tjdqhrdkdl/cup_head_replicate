#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class RightWall : public GameObject
	{
	public:
		RightWall();
		~RightWall();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


	};
}
