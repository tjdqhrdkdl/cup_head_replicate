#include "yaRollerCoasterHeadPinkNose.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya
{
	RollerCoasterHeadPinkNose::RollerCoasterHeadPinkNose()
		:mAliveTime(10.0f)
		,mAliveTimeChecker(0)
	{
		mCollider = new Collider();
		mCollider->SetScale({ 100,30 });
		mCollider->SetAddPos({ -70,-250 });
		mCollider->SetDanger(false);
		AddComponent(mCollider);
		mPink = true;
	}

	RollerCoasterHeadPinkNose::~RollerCoasterHeadPinkNose()
	{
	}

	void RollerCoasterHeadPinkNose::Tick()
	{
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
			mAliveTimeChecker = 0;
		}
		GameObject::Tick();
	}

	void RollerCoasterHeadPinkNose::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void RollerCoasterHeadPinkNose::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void RollerCoasterHeadPinkNose::OnCollisonExit(Collider* other, Collider* my)
	{
	}

}