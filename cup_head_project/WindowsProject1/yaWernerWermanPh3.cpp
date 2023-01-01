#include "yaWernerWermanPh3.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaWernerWermanPh2.h"
#include "yaBossCanRatScene.h"
#include "yaCatBody.h"
#include "yaGhostMouse.h"
#include "yaCatPaw.h"
#include "yaWoodPiece.h"
#include "yaKnockOut.h"
#include "yaBossExplosion.h"
namespace ya
{
	WernerWermanPh3::WernerWermanPh3(bool init)
		:mbPlayJail(false)
	{
		SetName(L"WernerWermanPh3");
		mHp = 200;
		SetPos({ 800,900 });
		SetScale({ 400,300.0f });
		mCollider = new Collider();
		mCollider->SetAddPos({ 0,-450 });
		mCollider->SetDanger(false);
		AddComponent(mCollider);
		mAnimator = new Animator();
		mHeadAnimator = new Animator();

		AddComponent(mAnimator);
		AddComponent(mHeadAnimator);


		mHeadAnimator->CreateAnimation(L"CatIntroFront_A", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Intro\\IntroFront1\\cat_intro_00", 4, 0.06f, false, false, { 0,-70 });
		mHeadAnimator->CreateAnimation(L"CatIntroFront_B", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Intro\\IntroFront2\\cat_intro_00", 32, 0.06f, false, false, {0, 310});
		mHeadAnimator->CreateAnimation(L"CatIntroFront_C", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Intro\\IntroFront3\\cat_intro_00", 16, 0.06f, false, false, { 0,-70 });

		mHeadAnimator->CreateAnimation(L"CatDeath", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Death\\cat_death_head_00", 16, 0.06f, false, false);

		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"HeadIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Head\\cat_idle_head_00", 19, 0.05f, false, false)
			, mHeadAnimator->CreateAnimation(L"LightenHeadIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Idle\\Head\\cat_idle_head_00", 19, 0.05f, false, false));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"HeadIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Idle\\Head\\cat_idle_head_00", 19, 0.05f, false, true)
			, mHeadAnimator->CreateAnimation(L"LightenHeadIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Idle\\Head\\cat_idle_head_00", 19, 0.05f, false, true));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"HeadJail", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Head\\cat_head_jail_00", 34, 0.05f, false, false)
			, mHeadAnimator->CreateAnimation(L"LightenHeadJail", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Head\\cat_head_jail_00", 34, 0.05f, false, false));

		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"ClawHeadIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Head\\Intro\\cat_claw_intro_0", 11, 0.05f, false, false)
			, mHeadAnimator->CreateAnimation(L"LightenClawHeadIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Claw\\Head\\Intro\\cat_claw_intro_0", 11, 0.05f, false, false));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"ClawHeadIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Head\\Intro\\cat_claw_intro_0", 11, 0.05f, false, true)
			, mHeadAnimator->CreateAnimation(L"LightenClawHeadIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Claw\\Head\\Intro\\cat_claw_intro_0", 11, 0.05f, false, true));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"ClawHeadIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Head\\Idle\\cat_claw_head_idle_00", 6, 0.05f, false, false)
			, mHeadAnimator->CreateAnimation(L"LightenClawHeadIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Claw\\Head\\Idle\\cat_claw_head_idle_00", 6, 0.05f, false, false));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"ClawHeadIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Head\\Idle\\cat_claw_head_idle_00", 6, 0.05f, false, true)
			, mHeadAnimator->CreateAnimation(L"LightenClawHeadIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Claw\\Head\\Idle\\cat_claw_head_idle_00", 6, 0.05f, false, true));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"ClawHeadOutroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Head\\Outro\\cat_claw_head_outro_0", 11, 0.05f, false, false)
			, mHeadAnimator->CreateAnimation(L"LightenClawHeadOutroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Claw\\Head\\Outro\\cat_claw_head_outro_0", 11, 0.05f, false, false));
		mHeadAnimator->SetLightenAnimation(mHeadAnimator->CreateAnimation(L"ClawHeadOutroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Head\\Outro\\cat_claw_head_outro_0", 11, 0.05f, false, true)
			, mHeadAnimator->CreateAnimation(L"LightenClawHeadOutroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Claw\\Head\\Outro\\cat_claw_head_outro_0", 11, 0.05f, false, true));
		

		mHeadAnimator->GetCompleteEvent(L"CatIntroFront_A") = std::bind(&WernerWermanPh3::CatFirstIntroCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"CatIntroFront_B") = std::bind(&WernerWermanPh3::CatSecondIntroCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"CatIntroFront_C") = std::bind(&WernerWermanPh3::CatThirdIntroCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"HeadIdleLeft") = std::bind(&WernerWermanPh3::HeadIdleLeftCompletEvent, this);
		mHeadAnimator->GetCompleteEvent(L"HeadIdleRight") = std::bind(&WernerWermanPh3::HeadIdleRightCompletEvent, this);
		mHeadAnimator->GetCompleteEvent(L"HeadJail") = std::bind(&WernerWermanPh3::HeadJailCompletEvent, this);
		mHeadAnimator->GetCompleteEvent(L"ClawHeadIntroLeft") = std::bind(&WernerWermanPh3::ClawHeadIntroCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"ClawHeadIntroRight") = std::bind(&WernerWermanPh3::ClawHeadIntroCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"ClawHeadOutroLeft") = std::bind(&WernerWermanPh3::ClawHeadOutroCompleteEvent, this);
		mHeadAnimator->GetCompleteEvent(L"ClawHeadOutroRight") = std::bind(&WernerWermanPh3::ClawHeadOutroCompleteEvent, this);

		mHeadAnimator->Play(L"CatIntroFront_A", false);

		mHeadAnimator->SetAddPos({ 0,-400 });
		if (init)
		{
			CatBody();
			GhostMouse(true);
			WoodPiece();
			Paw(true);
		}
		else
		{
			mCatBody = new CatBody();
			SceneManager::GetCurScene()->AddGameObject(mCatBody, eColliderLayer::BackGround);
		}
	}


	WernerWermanPh3::~WernerWermanPh3()
	{
	}

	void WernerWermanPh3::Tick()
	{
		if (mAnimator->isLighten())
			mHeadAnimator->SetLighten(true);
		else
			mHeadAnimator->SetLighten(false);
		Monster::Tick();
		Move();
		if (mHeadAnimator->GetPlayAnimation()->GetName() != L"CatDeath")
		{
			Attack();
			Jail();
		}
		if (mHp < 0)
		{
			if (mHeadAnimator->GetPlayAnimation()->GetName() != L"CatDeath")
			{
				ObjectManager::Instantiate<KnockOut>(SceneManager::GetCurScene(), eColliderLayer::UI);
				mHeadAnimator->Play(L"CatDeath", false);
				mCollider->SetOff(true);
				mCatBody->SetDeath();
				ObjectManager::Destroy(this, 300.0f);
			}
			mDeathEffectTimeChecker += Time::DeltaTime();
			if (mDeathEffectTimeChecker > 0.4f + (rand() % 5) * 0.1)
			{
				mDeathEffectTimeChecker = 0;
				Vector2 pos = { 800,450 };
				switch (rand() % 6)
				{
				case 0:
					pos += {160, 120};
					break;
				case 1:
					pos += {-250, 30};
					break;
				case 2:
					pos += {200, 50};
					break;
				case 3:
					pos += {-20, 250};
					break;
				case 4:
					pos += {-170, 40};
					break;
				case 5:
					pos += {60, 200};
					break;
				}

				BossExplosion* effect = ObjectManager::Instantiate<BossExplosion>(SceneManager::GetCurScene(), eColliderLayer::Effect);

				effect->SetPos(pos);
			}

			if (GetDeathTime() < 295)
				dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->SetPhase(5);
		}
	}

	void WernerWermanPh3::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void WernerWermanPh3::Move()
	{
		Vector2 pos = GetPos();
		if (mHeadAnimator->GetPlayAnimation()->GetName() == L"HeadIdleRight"
			|| mHeadAnimator->GetPlayAnimation()->GetName() == L"HeadIdleLeft")
		{
			int x = mHeadAnimator->GetPlayAnimation()->GetIndex();
			if (x == 0)
				pos = { 800,900 };
			else if (x <= 7)
			{
				if (mHeadAnimator->GetPlayAnimation()->GetName() == L"HeadIdleRight")
				{
					pos.x += Time::DeltaTime() * 300;
					pos.y += Time::DeltaTime() * 150;
				}
				else
				{
					pos.x -= Time::DeltaTime() * 300;
					pos.y += Time::DeltaTime() * 150;
				}
			}

			else if (x >= 10 && x< 17)
			{
				if (mHeadAnimator->GetPlayAnimation()->GetName() == L"HeadIdleRight")
				{
					pos.x -= Time::DeltaTime() * 300;
					pos.y -= Time::DeltaTime() * 150;
				}
				else 
				{
					pos.x += Time::DeltaTime() * 300;
					pos.y -= Time::DeltaTime() * 150;
				}
			}			
		}

		else if (mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadIntroLeft"
			|| mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadIdleLeft")
		{
			if (!mbPawBack)
			{
				pos.x -= Time::DeltaTime() * 200;
				if (pos.x < 600)
				{
					pos.x = 600;
				}
			}
			else
			{
				pos.x += Time::DeltaTime() * 60;
				if (pos.x > 800)
				{
					pos.x = 800;
				}
			}
		}
		else if (mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadIntroRight"
			|| mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadIdleRight")
		{
			if (!mbPawBack)
			{
				pos.x += Time::DeltaTime() * 200;
				if (pos.x > 1050)
				{
					pos.x = 1050;
				}
			}
			else
			{
				pos.x -= Time::DeltaTime() * 60;
				if (pos.x < 800)
				{
					pos.x = 800;
				}
			}
		}
		else if (mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadOutroRight")
		{
			pos.x -= Time::DeltaTime() * 300;
			if (pos.x < 800)
			{
				pos.x = 800;
			}
		}
		else if (mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadOutroLeft")
		{
			pos.x += Time::DeltaTime() * 300;
			if (pos.x > 800)
			{
				pos.x = 800;
			}
		}
		else if (mHeadAnimator->GetPlayAnimation()->GetName() == L"CatDeath")
		{
			pos.x = 800;
			pos.y += Time::DeltaTime() * 500;
			if (pos.y > 1250)
				pos.y = 1250;

		}
		SetPos(pos);
	}

	void WernerWermanPh3::Attack()
	{
		mAttackTimeChecker += Time::DeltaTime();
		if (mAttackTimeChecker > 8)
		{
			switch (rand()%2)
			{
			case 0:
				if (mLeftGhostMouse == nullptr or mRightGhostMouse == nullptr)
				{
					mbPlayJail = true;
				}
				else
					mbPlayClawRight = true;
				break;
			case 1:
				mbPlayClawLeft = true;
				break;
			case 2:
				mbPlayClawRight = true;
				break;

			}

			mAttackTimeChecker = 0;
		}
	}

	void WernerWermanPh3::Jail()
	{

		if (mHeadAnimator->GetPlayAnimation()->GetName() == L"HeadJail")
		{
			if (mHeadAnimator->GetPlayAnimation()->GetIndex() == 16)
			{
				if (mLeftGhostMouse == nullptr)
				{
					mLeftGhostMouse = new GhostMouse(false);
					SceneManager::GetCurScene()->AddGameObject(mLeftGhostMouse, eColliderLayer::FrontMonster);
					dynamic_cast<GhostMouse*>(mLeftGhostMouse)->SetOwnerCat(this);
				}
				if (mRightGhostMouse == nullptr)
				{
					mRightGhostMouse = new GhostMouse(true);
					SceneManager::GetCurScene()->AddGameObject(mRightGhostMouse, eColliderLayer::FrontMonster);
					dynamic_cast<GhostMouse*>(mRightGhostMouse)->SetOwnerCat(this);
				}
			}
		}
	}

	void WernerWermanPh3::SummonWoodPieces(bool right)
	{
		for (size_t i = 0; i < 10; i++)
		{
			WoodPiece* plank = new WoodPiece();
			if (right)
				plank->SetPos({ i * 200.0f + 100, -200.0f * i - 100});
			else
				plank->SetPos({ -(i * 200.0f) + 1500, -200.0f * i - 100 });

			SceneManager::GetCurScene()->AddGameObject(plank, eColliderLayer::FrontMonster);
		}
	}

	void WernerWermanPh3::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void WernerWermanPh3::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void WernerWermanPh3::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void WernerWermanPh3::PawOutroFin()
	{
		if(mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadIdleLeft")
			mHeadAnimator->Play(L"ClawHeadOutroLeft", false);
		else
			mHeadAnimator->Play(L"ClawHeadOutroRight", false);

	}

	void WernerWermanPh3::CatFirstIntroCompleteEvent()
	{
		mHeadAnimator->Play(L"CatIntroFront_B", false);
		ObjectManager::Destroy(mBeforePhaseToDelete);
		dynamic_cast<WernerWermanPh2*>(mBeforePhaseToDelete)->DestroyWoodCart();
	}

	void WernerWermanPh3::CatSecondIntroCompleteEvent()
	{
		mHeadAnimator->Play(L"CatIntroFront_C", false);
		dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->ChangeBGQue();
	}

	void WernerWermanPh3::CatThirdIntroCompleteEvent()
	{
		mHeadAnimator->Play(L"HeadIdleLeft", false);
	}

	void WernerWermanPh3::HeadIdleRightCompletEvent()
	{
		mHeadAnimator->Play(L"HeadIdleLeft", false);
		if (mbPlayJail)
		{
			mHeadAnimator->Play(L"HeadJail", false);
			mbPlayJail = false;
		}

		else if (mbPlayClawLeft)
		{
			mHeadAnimator->Play(L"ClawHeadIntroLeft", false);
			mbPlayClawLeft = false;
		}
		else if (mbPlayClawRight)
		{
			mHeadAnimator->Play(L"ClawHeadIntroRight", false);
			mbPlayClawRight = false;
		}
	}

	void WernerWermanPh3::HeadIdleLeftCompletEvent()
	{
		mHeadAnimator->Play(L"HeadIdleRight", false);
		if (mbPlayJail)
		{
			mHeadAnimator->Play(L"HeadJail", false);
			mbPlayJail = false;
		}

		else if (mbPlayClawLeft)
		{
			mHeadAnimator->Play(L"ClawHeadIntroLeft", false);
			mbPlayClawLeft = false;
		}
		else if (mbPlayClawRight)
		{
			mHeadAnimator->Play(L"ClawHeadIntroRight", false);
			mbPlayClawRight = false;
		}
	}

	void WernerWermanPh3::HeadJailCompletEvent()
	{
		mHeadAnimator->Play(L"HeadIdleRight", false);
	}

	void WernerWermanPh3::ClawHeadIntroCompleteEvent()
	{
		if (mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadIntroLeft")
		{
			mHeadAnimator->Play(L"ClawHeadIdleLeft", true);
			Paw* pawRight = new Paw(true);
			pawRight->SetPos({ -950,800 });
			pawRight->SetOwnerCat(this);
			SceneManager::GetCurScene()->AddGameObject(pawRight, eColliderLayer::FrontMonster);
		}
		else
		{
			mHeadAnimator->Play(L"ClawHeadIdleRight", true);
			Paw* pawLeft = new Paw(false);
			pawLeft->SetPos({ 2550,800 });
			pawLeft->SetOwnerCat(this);
			SceneManager::GetCurScene()->AddGameObject(pawLeft, eColliderLayer::FrontMonster);
		}
	}

	void WernerWermanPh3::ClawHeadOutroCompleteEvent()
	{
		mbPawBack = false;
		if (mHeadAnimator->GetPlayAnimation()->GetName() == L"ClawHeadOutroLeft")
			mHeadAnimator->Play(L"HeadIdleLeft", false);
		else
			mHeadAnimator->Play(L"HeadIdleRight", false);
	}

	void WernerWermanPh3::Release()
	{
		mHeadAnimator->Release();
		CatBody().Release();
		Paw(1).Release();
		GhostMouse(1).Release();
		WoodPiece().Release();
		
	}

}