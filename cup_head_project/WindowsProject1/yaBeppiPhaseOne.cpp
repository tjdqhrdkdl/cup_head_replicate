#include "yaBeppiPhaseOne.h"
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
#include "yaBullet.h"
namespace ya 
{
	BeppiPhaseOne::BeppiPhaseOne()
		:mSpeed(1.0f)
		, onHit(false)
		, onHitChecker(0.0f)
		, mHp(50.0f)
		, mLookingLeft(true)
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

	BeppiPhaseOne::BeppiPhaseOne(Vector2 position) 
		: mSpeed(1.0f)
		, onHit(false)
		, onHitChecker(0.0f)
		, mHp(50.0f)
		, mLookingLeft(true)
	{
		SetName(L"Enemy");
		SetPos(position);
		SetScale({ 250.0f,200.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, false);
		mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, true);
		mAnimator->CreateAnimation(L"AttackLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Phase1_Attack_", 34, 0.04f, true, false);
		mAnimator->CreateAnimation(L"AttackRightt", L"..\\Resources\\Image\\Beppi\\Attack\\Phase1_Attack_", 34, 0.04f, true, false);

		mAnimator->CreateAnimation(L"Intro", L"..\\Resources\\Image\\Beppi\\Intro\\Phase1_Intro_", 30, 0.03f, true, false,{180,-10});

		mAnimator->SetBaseAnimation(L"IdleLeft");
		mAnimator->Play(L"Intro", false);
	}

	BeppiPhaseOne::~BeppiPhaseOne()
	{
	}

	void BeppiPhaseOne::Tick()
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

	void BeppiPhaseOne::Render(HDC hdc)
	{



		GameObject::Render(hdc);
	}
	void BeppiPhaseOne::Attack()
	{
	}
	void BeppiPhaseOne::OnCollisonEnter(Collider* other)
	{
		GameObject* objOther = other->GetOwner();
		if(objOther->GetLayer() == eColliderLayer::Player_Projecttile)
		{
			Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner());
			mHp -= bullet->GetDamage();
			onHit = true;
			mAnimator->SetMatrixToLighten();
			
		}
	}
	void BeppiPhaseOne::OnCollisonStay(Collider* other)
	{
	}
	void BeppiPhaseOne::OnCollisonExit(Collider* other)
	{
	}
}