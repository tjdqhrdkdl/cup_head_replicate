#pragma once
#include "Common.h"
#include "yaGameobject.h"
#include "yaRollerCoasterTrail.h"
#include "yaRollerCoasterHead.h"
#include	"yaRollerCoasterTail.h"
namespace ya
{

	class Animator;
	class Player;
	class RollerCoaster : public GameObject
	{
	public:

		RollerCoaster(UINT coasterLength , bool init = false);
		~RollerCoaster();

		void SetSpeed(float speed) { mSpeed = speed; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void Release();
	private:
		float mSpeed;
		float mAliveTime;
		float mAliveTimeChecker;

		Collider* mGroundCollider;
		UINT mTrailLength;

		RollerCoasterHead* mHead;
		RollerCoasterTail* mTail;
		std::vector<RollerCoasterTrail*> mTrails;

	};
}
