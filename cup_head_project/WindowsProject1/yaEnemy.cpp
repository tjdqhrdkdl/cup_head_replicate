#include "yaEnemy.h"
#include "yaTime.h"
#include "yaBullet.h"
#include "yaScenemanager.h"
#include "yaScene.h"
#include "yaInput.h"
#include "yaPicture.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaCamera.h"
namespace ya {
	Enemy::Enemy()
		:mSpeed(1.0f)
		,onHit(false)
		,onHitChecker(0.0f)
	{
		SetName(L"Enemy");
		SetPos({ 960.0f, 500.0f });
		SetScale({ 400.0f,400.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, false);
		AddComponent(mAnimator);
		mAnimator->Play(L"IdleRight", true);
	}

	Enemy::Enemy(Vector2 position) :
		mSpeed(1.0f)
		, onHit(false)
		, onHitChecker(0.0f)
	{
		SetName(L"Enemy");
		SetPos(position);
		SetScale({ 400.0f,400.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, false);
		mAnimator->Play(L"IdleRight", true);
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::Tick()
	{
		Vector2 pos = GetPos();
		if (onHit)
		{
			onHitChecker += Time::DeltaTime();
			if (onHitChecker > 0.2f)
			{
				onHitChecker = 0;
				onHit = false;
				mAnimator->SetMatrixToBase();
			}
		}
		GameObject::Tick();
		
	}

	void Enemy::Render(HDC hdc)
	{



		GameObject::Render(hdc);
	}
	void Enemy::OnCollisonEnter(Collider* other)
	{
		GameObject* objOther = other->GetOwner();
		if(objOther->GetLayer() == eColliderLayer::Player_Projecttile)
		{
			onHit = true;
			mAnimator->SetMatrixToLighten();
		}
	}
	void Enemy::OnCollisonStay(Collider* other)
	{
	}
	void Enemy::OnCollisonExit(Collider* other)
	{
	}
}