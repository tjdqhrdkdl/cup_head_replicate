#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{

	class Animator;
	class RollerCoasterHeadPinkNose : public GameObject
	{
	public:

		RollerCoasterHeadPinkNose();
		~RollerCoasterHeadPinkNose();

		virtual void Tick() override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


	private:
		float mAliveTime;
		float mAliveTimeChecker;
		Collider* mCollider;
	};
}
