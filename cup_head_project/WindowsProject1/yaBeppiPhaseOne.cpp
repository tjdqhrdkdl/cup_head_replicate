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
#include "yaDuckPanel.h"
#include "yaBossBeppiScene.h"
namespace ya 
{
	float AttackCoolTime = 5.0f;
	float IdleMoveTime = 0.1f;

	BeppiPhaseOne::BeppiPhaseOne()
		: mIdleSpeed(700.0f)
		, mAttackSpeed(800.0f)
		, mDuckTime(3.0f)
		, mCurState(BeppiPh1State_LookLeft)
		, mAttackTimeChecker(0.0f)
		, mBulbDuckChecker(1)
	{
		SetName(L"BeppiPhaseOne");
		mHp = 200;
		SetPos({ 1100,790 });
		SetScale({ 250.0f,200.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
	
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, false)
			, mAnimator->CreateAnimation(L"LightenIdleLeft", L"..\\Resources\\Image\\Beppi\\Idle\\Lighten\\Phase1_Idle_", 26, 0.04f, true, false));
		
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Idle\\Phase1_Idle_", 26, 0.04f, true, true)
			, mAnimator->CreateAnimation(L"LightenIdleRight", L"..\\Resources\\Image\\Beppi\\Idle\\Lighten\\Phase1_Idle_", 26, 0.04f, true, true));
		
		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"AttackStartLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Start\\Phase1_Attack_", 12, 0.05f, true, false, { 0,30 })
			, mAnimator->CreateAnimation(L"LightenAttackStartLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Lighten\\Start\\Phase1_Attack_", 12, 0.05f, true, false, { 0,30 }));

		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"AttackStartRight", L"..\\Resources\\Image\\Beppi\\Attack\\Start\\Phase1_Attack_", 12, 0.05f, true, true, { 0,30 })
			, mAnimator->CreateAnimation(L"LightenAttackStartRight", L"..\\Resources\\Image\\Beppi\\Attack\\Lighten\\Start\\Phase1_Attack_", 12, 0.05f, true, true, { 0,30 }));
	
		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"AttackMovingLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Moving\\Phase1_Attack_", 6, 0.01f, true, false, { 0,30 })
			, mAnimator->CreateAnimation(L"LightenAttackMovingLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Lighten\\Moving\\Phase1_Attack_", 6, 0.01f, true, false, { 0,30 }));

		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"AttackMovingRight", L"..\\Resources\\Image\\Beppi\\Attack\\Moving\\Phase1_Attack_", 6, 0.01f, true, true, { 0,30 })
			, mAnimator->CreateAnimation(L"LightenAttackMovingRight", L"..\\Resources\\Image\\Beppi\\Attack\\Lighten\\Moving\\Phase1_Attack_", 6, 0.01f, true, true, { 0,30 }));

		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"AttackSmashLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Smash\\Phase1_Attack_", 17, 0.04f, true, false)
			, mAnimator->CreateAnimation(L"LightenAttackSmashLeft", L"..\\Resources\\Image\\Beppi\\Attack\\Lighten\\Smash\\Phase1_Attack_", 17, 0.04f, true, false));

		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"AttackSmashRight", L"..\\Resources\\Image\\Beppi\\Attack\\Smash\\Phase1_Attack_", 17, 0.04f, true, true)
			, mAnimator->CreateAnimation(L"LightenAttackSmashRight", L"..\\Resources\\Image\\Beppi\\Attack\\Lighten\\Smash\\Phase1_Attack_", 17, 0.04f, true, true));


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
		
		DuckPanel InitDuck = DuckPanel();
		LightBulb InitBulb = LightBulb();
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
			Attack();
			Move();
			SummonDuck();
		}


		Monster::Tick();
		
	}

	void BeppiPhaseOne::Render(HDC hdc)
	{

		Monster::Render(hdc);
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
				playAnimationName = L"EndRight";
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
				playAnimationName = L"EndLeft";
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

		if (mAttackStarted)
		{
			mAttackStartedTimeChecker += Time::DeltaTime();
			if (mAttackStartedTimeChecker > 0.5f)
			{
				mCurState &= ~BeppiPh1State_OnAttackStart;
				mCurState |= BeppiPh1State_OnAttackMoving;
				mAttackStarted = false;
				mAttackStartedTimeChecker = 0;
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
			pos.y += 500 * Time::DeltaTime();
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

	void BeppiPhaseOne::SummonDuck()
	{
		mDuckTimeChecker += Time::DeltaTime();
		if (mDuckTimeChecker >= mDuckTime)
		{
			Scene* curScene = SceneManager::GetCurScene();
			if (mPinkDuckChecker == 2)
			{
				bool pink = true;
				DuckPanel* pinkDuck = new DuckPanel(pink);
				pinkDuck->Initialize();
				curScene->AddGameObject(pinkDuck, eColliderLayer::FrontMonster);
				mPinkDuckChecker = 0;
			}
			else
			{
				if (mBulbDuckChecker == 2)
				{
					LightBulb* bulb = new LightBulb();
					DuckPanel* bulbDuck = new DuckPanel(false,bulb);
					bulbDuck->Initialize();
					curScene->AddGameObject(bulbDuck, eColliderLayer::FrontMonster);
					mBulbDuckChecker = 0;
				}
				else
				{
					ObjectManager::Instantiate<DuckPanel>(curScene, eColliderLayer::FrontMonster);
					mBulbDuckChecker += 1;
				}
				mPinkDuckChecker += 1;
			}
			mDuckTimeChecker = 0.0f;
		}
	}

	void BeppiPhaseOne::AttackStartCompleteEvent()
	{
		mAttackStarted = true;
	}

	void BeppiPhaseOne::AttackSmashCompleteEvent()
	{
		mCurState &= ~BeppiPh1State_OnAttackSmash;
		mCurState ^= BeppiPh1State_LookLeft;
		if (mHp <= 0)
		{
			ObjectManager::Destroy(this, 5.0f);
			dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->SetPhase(2);
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
		SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::BehindMonster);
		mCurState |= BeppiPh1State_EndFall;
	}

	void BeppiPhaseOne::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void BeppiPhaseOne::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseOne::OnCollisonExit(Collider* other, Collider* my)
	{
	}
}