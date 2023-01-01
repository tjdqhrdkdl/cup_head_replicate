#include "yaMiniFlowerBullet.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"


namespace ya {
	MiniFlowerBullet::MiniFlowerBullet(Vector2 dir)
		:mAliveTime(10)
		, mAliveTimeChecker(0)

	{
		mPink = true;
		mDestDir = dir;
		SetName(L"MiniFlowerBullet");
		SetScale({ 40.0f, 40.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Bullet\\Idle\\MF_Atk_", 5, 0.04f, false, false);
		mAnimator->Play(L"Idle", true);
	}

	MiniFlowerBullet::~MiniFlowerBullet()
	{
	}

	void MiniFlowerBullet::Tick()
	{
		GameObject::Tick();
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
		}

		Vector2 pos = GetPos();
		pos += mDestDir * 200 * Time::DeltaTime();
		SetPos(pos);
		if(mParried)
			ObjectManager::Destroy(this);
	}

	void MiniFlowerBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MiniFlowerBullet::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::Player )
			ObjectManager::Destroy(this);
	}

	void MiniFlowerBullet::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void MiniFlowerBullet::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void MiniFlowerBullet::Release()
	{
		mAnimator->Release();
	}

}