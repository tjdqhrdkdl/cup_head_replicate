#include "yaPenguinBaseBall.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaShootEffect.h"


namespace ya{
	BaseBall::BaseBall(Vector2 dir)
		:mAliveTime(10)
		,mAliveTimeChecker(0)

	{
		mDestDir = dir;
		SetName(L"BaseBall");
		SetScale({ 50.0f, 50.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mShootEffect = new ShootEffect();
		Scene* curScene = SceneManager::GetCurScene();
		curScene->AddGameObject(mShootEffect, eColliderLayer::Effect);
		Animator* effectAnimator = mShootEffect->GetAnimator();
		effectAnimator->CreateAnimation(L"Spark", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Clap\\Spark\\clown_ph3_penguin_clapspark_00", 11, 0.03f, false, false,{0,30});
		effectAnimator->GetCompleteEvent(L"Spark") = std::bind(&ShootEffect::ShootEffectCompleteEvent, mShootEffect);
		effectAnimator->Play(L"Spark", false);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\BaseBall\\penguin_baseball_00", 17, 0.04f, false, false, {-5,28});
		mAnimator->Play(L"Idle", true);
	}

	BaseBall::~BaseBall()
	{
	}

	void BaseBall::Tick()
	{
		GameObject::Tick();
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
		}

		Vector2 pos = GetPos();
		pos += mDestDir * 400 * Time::DeltaTime();
		SetPos(pos);
	}

	void BaseBall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BaseBall::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void BaseBall::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BaseBall::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void BaseBall::Release()
	{
		mAnimator->Release();
	}

}