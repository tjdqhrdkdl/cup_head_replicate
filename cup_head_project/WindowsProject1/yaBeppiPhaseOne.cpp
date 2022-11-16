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
#include "yaObjectManager.h"
namespace ya 
{
	float AttackCoolTime = 5.0f;
	float IdleMoveTime = 0.1f;

	BeppiPhaseOne::BeppiPhaseOne()
		: mIdleSpeed(700.0f)
		, mAttackSpeed(800.0f)
		, onHit(false)
		, onHitChecker(0.0f)
		, mHp(50.0f)
		, mCurState(BeppiPh1State_LookLeft)
		, mAttackTimeChecker(0.0f)
	{
		SetName(L"Enemy");
		SetPos({ 1100,790 });
		SetScale({ 250.0f,200.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, false);
		mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, true);
		
		mAnimator->CreateAnimation(L"AttackStartLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Start\\Phase1_Attack_", 12, 0.05f, true, false, {0,30});
		mAnimator->CreateAnimation(L"AttackStartRight", L"..\\Resources\\Image\\Beppi\\Attack\\Start\\Phase1_Attack_", 12, 0.05f, true, true, { 0,30 });

		mAnimator->CreateAnimation(L"AttackMovingLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Moving\\Phase1_Attack_", 6, 0.01f, true, false, { 0,30 });
		mAnimator->CreateAnimation(L"AttackMovingRight", L"..\\Resources\\Image\\Beppi\\Attack\\Moving\\Phase1_Attack_", 6, 0.01f, true, true, { 0,30 });

		mAnimator->CreateAnimation(L"AttackSmashLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Smash\\Phase1_Attack_", 17, 0.04f, true, false);
		mAnimator->CreateAnimation(L"AttackSmashRight", L"..\\Resources\\Image\\Beppi\\Attack\\Smash\\Phase1_Attack_", 17, 0.04f, true, true);

		mAnimator->CreateAnimation(L"Intro", L"..\\Resources\\Image\\Beppi\\Intro\\Phase1_Intro_", 30, 0.03f, true, false, { 180,-10 });

		mAnimator->CreateAnimation(L"EndLeft", L"..\\Resources\\Image\\Beppi\\End\\Phase1_End_", 16, 0.05f, true, false, { 0,0 });
		mAnimator->CreateAnimation(L"EndRight", L"..\\Resources\\Image\\Beppi\\End\\Phase1_End_", 16, 0.05f, true, true, { 0,0 });

		
		mAnimator->GetCompleteEvent(L"IdleLeft") = std::bind(&BeppiPhaseOne::IdleCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"IdleRight") = std::bind(&BeppiPhaseOne::IdleCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"AttackStartLeft") = std::bind(&BeppiPhaseOne::AttackStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"AttackStartRight") = std::bind(&BeppiPhaseOne::AttackStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"AttackSmashLeft") = std::bind(&BeppiPhaseOne::AttackSmashCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"AttackSmashRight") = std::bind(&BeppiPhaseOne::AttackSmashCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"EndLeft") = std::bind(&BeppiPhaseOne::EndCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"EndRight") = std::bind(&BeppiPhaseOne::EndCompleteEvent, this);

		
		
		
		mAnimator->SetBaseAnimation(L"IdleLeft");
		mAnimator->Play(L"Intro", false);
	}

	BeppiPhaseOne::~BeppiPhaseOne()
	{
	}

	void BeppiPhaseOne::Tick()
	{
		Vector2 pos = GetPos();
		if (mAnimator->GetPlayAnimation()->GetName() != L"Intro")
		{
			SetAnimation();
			OnHitCheck();
			Attack();
			Move();
		}


		GameObject::Tick();
		
	}

	void BeppiPhaseOne::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	void BeppiPhaseOne::SetAnimation()
	{
		bool bLoop = true;
		std::wstring playAnimationName = L"";
		if ((mCurState & BeppiPh1State_LookLeft) == BeppiPh1State_LookLeft)
		{
			playAnimationName = L"IdleLeft";
			if (IsDeathTimeOn())
			{
				playAnimationName = L"EndLeft";
				bLoop = false;
			}
			else if ((mCurState & BeppiPh1State_OnAttackStart) == BeppiPh1State_OnAttackStart)
			{
				playAnimationName = L"AttackStartLeft"; 
				bLoop = false;
			}
			else if ((mCurState & BeppiPh1State_OnAttackMoving) == BeppiPh1State_OnAttackMoving)
				playAnimationName = L"AttackMovingLeft";
			else if ((mCurState & BeppiPh1State_OnAttackSmash) == BeppiPh1State_OnAttackSmash)
			{
				playAnimationName = L"AttackSmashLeft";
				bLoop = false;
			}
		}
		else
		{
			playAnimationName = L"IdleRight";
			if (IsDeathTimeOn())
			{
				playAnimationName = L"EndRight";
				bLoop = false;
			}
			else if ((mCurState & BeppiPh1State_OnAttackStart) == BeppiPh1State_OnAttackStart)
			{
				playAnimationName = L"AttackStartRight";
				bLoop = false;
			}
			else if ((mCurState & BeppiPh1State_OnAttackMoving) == BeppiPh1State_OnAttackMoving)
				playAnimationName = L"AttackMovingRight";
			else if ((mCurState & BeppiPh1State_OnAttackSmash) == BeppiPh1State_OnAttackSmash)
			{
				playAnimationName = L"AttackSmashRight";
				bLoop = false;
			}
		}

		if (playAnimationName != L"" and
			mAnimator->GetPlayAnimation() != mAnimator->FindAnimation(playAnimationName))
			mAnimator->Play(playAnimationName, bLoop);
	}

	void BeppiPhaseOne::Attack()
	{
		mAttackTimeChecker += Time::DeltaTime();
		if (mAttackTimeChecker > AttackCoolTime)
		{
			mCurState |= eBeppiPh1State::BeppiPh1State_OnAttackStart;
			mCurState &= ~BeppiPh1State_OnIdleMove;
			mAttackTimeChecker = 0;
		}
	}

	void BeppiPhaseOne::OnHitCheck()
	{
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
	}

	void BeppiPhaseOne::Move()
	{
		Vector2 pos = GetPos();
		Vector2 dir;
		if ((mCurState & BeppiPh1State_LookLeft) == BeppiPh1State_LookLeft)
			dir = Vector2::Left;
		else
			dir = Vector2::Right;
		
		if ((mCurState & BeppiPh1State_EndFall) == BeppiPh1State_EndFall)
		{

			pos.y += 1000 * Time::DeltaTime();
		}
		else if ((mCurState & BeppiPh1State_OnAttackMoving) == BeppiPh1State_OnAttackMoving)
		{
			if (dir.isLeft())
			{
				if (pos.x <= 200)
				{
					mCurState &= ~BeppiPh1State_OnAttackMoving;
					mCurState |= BeppiPh1State_OnAttackSmash;
				}
			}
			else
			{
				if (pos.x >= 1400)
				{
					mCurState &= ~BeppiPh1State_OnAttackMoving;
					mCurState |= BeppiPh1State_OnAttackSmash;
				}
			}
			pos += dir * mAttackSpeed * Time::DeltaTime();
			
		}
		
		else if ((mCurState & BeppiPh1State_OnIdleMove) == BeppiPh1State_OnIdleMove)
		{
			mIdleMoveTimeChecker += Time::DeltaTime();
			pos += dir * mIdleSpeed * Time::DeltaTime();
			if (mIdleMoveTimeChecker > IdleMoveTime)
			{
				mIdleMoveTimeChecker = 0;
				mCurState &= ~BeppiPh1State_OnIdleMove;
			}
		}
		SetPos(pos);
	}

	void BeppiPhaseOne::AttackStartCompleteEvent()
	{
		if (mAttackTimeChecker > 1.3f)
		{
			mCurState &= ~BeppiPh1State_OnAttackStart;
			mCurState |= BeppiPh1State_OnAttackMoving;
		}
	}

	void BeppiPhaseOne::AttackSmashCompleteEvent()
	{
		mCurState &= ~BeppiPh1State_OnAttackSmash;
		mCurState ^= BeppiPh1State_LookLeft;
		if (mHp <= 0)
		{
			ObjectManager::Destroy(this, 3.0f);
			GetComponent<Collider>()->SetScale({0,0});
			SetScale({ 0,0 });
		}
	}

	void BeppiPhaseOne::IdleCompleteEvent()
	{
		mCurState |= BeppiPh1State_OnIdleMove;
	}

	void BeppiPhaseOne::EndCompleteEvent()
	{
		mCurState |= BeppiPh1State_EndFall;
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