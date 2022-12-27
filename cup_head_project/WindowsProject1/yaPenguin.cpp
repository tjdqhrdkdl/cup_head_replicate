#include "yaPenguin.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaGround.h"
#include "yaRollerCoasterHead.h"
#include "yaPenguinBaseBall.h"
#include "yaPlayer.h"
#include "yaBossBeppiScene.h"
#include "yaShootEffect.h"

namespace ya
{
	Penguin::Penguin(UINT posNum)
		:mBallTime(5)
		,mBallTimeChecker(0)
	{
		mPositionNumber = posNum;
		SetName(L"BeppiPh4Penguin");
		mHp = 10;
		SetPos({ 800,500 });
		SetScale({ 60.0f,100.0f });
		mCollider = new Collider();
		mCollider->SetHitBox(false);
		AddComponent(mCollider);
		mAnimator = new Animator();
		AddComponent(mAnimator);


		mAnimator->CreateAnimation(L"RollBeforeGround", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\BeforeGround\\clown_ph3_penguin_roll_00", 20, 0.04f, false, false);

		mAnimator->CreateAnimation(L"RollCollisionGround", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\CollisionGround\\clown_ph3_penguin_roll_ground_00", 2, 0.04f, true, false);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"RollOnGroundLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\OnGround\\clown_ph3_penguin_roll_ground_00", 9, 0.04f, true, false)
			, mAnimator->CreateAnimation(L"LightenRollOnGroundLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\Lighten\\OnGround\\clown_ph3_penguin_roll_ground_00", 9, 0.04f, true, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"RollOnGroundRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\OnGround\\clown_ph3_penguin_roll_ground_00", 9, 0.04f, true, true)
			, mAnimator->CreateAnimation(L"LightenRollOnGroundRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\Lighten\\OnGround\\clown_ph3_penguin_roll_ground_00", 9, 0.04f, true, true));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"RollGetUpLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\GetUp\\clown_ph3_penguin_roll_00", 10, 0.04f, true, false)
			, mAnimator->CreateAnimation(L"LightenRollGetUpLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\Lighten\\GetUp\\clown_ph3_penguin_roll_00", 10, 0.04f, true, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"RollGetUpRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\GetUp\\clown_ph3_penguin_roll_00", 10, 0.04f, true, true)
			, mAnimator->CreateAnimation(L"LightenRollGetUpRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Roll\\Lighten\\GetUp\\clown_ph3_penguin_roll_00", 10, 0.04f, true, true));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Idle\\clown_ph3_penguin_idle_00", 17, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Idle\\Lighten\\clown_ph3_penguin_idle_00", 17, 0.04f, false, false));

		mAnimator->CreateAnimation(L"Pop", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Explode\\clown_ph3_penguin_explode_00", 13, 0.04f, false, false);
		mAnimator->CreateAnimation(L"Clap", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Penguin\\Clap\\Clap\\clown_ph3_penguin_clap_00", 12, 0.05f, false, false);

		mAnimator->GetCompleteEvent(L"RollCollisionGround") = std::bind(&Penguin::CollisionGroundCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"RollGetUpLeft") = std::bind(&Penguin::GetUpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"RollGetUpRight") = std::bind(&Penguin::GetUpCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Pop") = std::bind(&Penguin::PopCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Clap") = std::bind(&Penguin::ClapCompleteEvent, this);
		mAnimator->Play(L"RollBeforeGround", false);
	}

	Penguin::~Penguin()
	{
	}

	void Penguin::Tick()
	{
		if (mAnimator->GetPlayAnimation()->GetName() != L"Pop")
		{
			Vector2 pos = GetPos();
			float destXPos;
			switch (mPositionNumber)
			{
			case 0:
				destXPos = 10;
				break;
			case 1:
				destXPos = 350;
				break;
			case 2:
				destXPos = 700;
				break;
			case 3:
				destXPos = 1050;
				break;
			case 4:
				destXPos = 1310;
				break;
			case 5:
				destXPos = 1570;
				break;
			}
			Monster::Tick();


			if (mAnimator->GetPlayAnimation()->GetName() == L"RollOnGroundRight")
			{
				pos.x += Time::DeltaTime() * 600;
				if (pos.x > destXPos)
				{
					pos.x = destXPos;
					mbArrive = true;
					mAnimator->Play(L"RollGetUpRight", true);
				}
			}
			else if (mAnimator->GetPlayAnimation()->GetName() == L"RollOnGroundLeft")
			{
				pos.x -= Time::DeltaTime() * 600;
				if (pos.x < destXPos)
				{
					pos.x = destXPos;
					mbArrive = true;
					mAnimator->Play(L"RollGetUpLeft", true);
				}
			}
			else if (mRolloutPhase == 0)
			{
				pos.y += Time::DeltaTime() * 200;
				if (pos.y > 520)
				{
					pos.y = 520;
					++mRolloutPhase;
				}
			}
			else if (mRolloutPhase == 1)
			{
				pos.y -= Time::DeltaTime() * 200;
				if (pos.y < 460)
				{
					pos.y = 460;
					++mRolloutPhase;
				}
			}
			else if (mRolloutPhase == 2)
			{
				pos.y += Time::DeltaTime() * 600;
				if (mbGround)
					mRolloutPhase = 3;
			}
			SetPos(pos);

			if (mHp < 0)
			{
				if (mAnimator->GetPlayAnimation()->GetName() != L"Pop")
				{
					SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::Effect);
					mAnimator->Play(L"Pop", false);
				}
				mCollider->SetOff(true);
			}

			SummonBaseBall();
		}
	}

	void Penguin::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void Penguin::SummonBaseBall()
	{
		mBallTimeChecker += Time::DeltaTime();
		if (mBallTimeChecker > mBallTime)
		{
			mAnimator->Play(L"Clap", false);
			mBallTimeChecker = 0;
		}
	}

	void Penguin::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr && !mbGround)
		{
			mbGround = true;
			Vector2 pos = GetPos();
			pos.y = 700;
			SetPos(pos);
			mAnimator->Play(L"RollCollisionGround", false);
			mCollider->SetHitBox(true);
		}

		else if (dynamic_cast<RollerCoasterHead*>(other->GetOwner()) != nullptr)
		{
			if (mAnimator->GetPlayAnimation()->GetName() != L"Pop")
			{
				SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::Effect);
				mAnimator->Play(L"Pop", false);
			}
			mCollider->SetOff(true);
		}

	}

	void Penguin::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Penguin::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Penguin::CollisionGroundCompleteEvent()
	{
		if (mPositionNumber < 3)
			mAnimator->Play(L"RollOnGroundLeft", true);
		else
			mAnimator->Play(L"RollOnGroundRight", true);
	}

	void Penguin::GetUpCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
	}

	void Penguin::PopCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void Penguin::ClapCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
		Player* player = dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->GetScenePlayer();
		Vector2 playerPos = player->GetPos();
		Vector2 destPos = playerPos - GetPos();
		BaseBall* ball = new BaseBall(destPos.Normalize());
		Vector2 ballPos = GetPos();
		ballPos.y -= GetScale().y + 15;
		ball->SetPos(ballPos);
		ball->mShootEffect->SetPos(ballPos);
		ball->Initialize();
		SceneManager::GetCurScene()->AddGameObject(ball, eColliderLayer::Monster_Projecttile);
	}

	void Penguin::Release()
	{
		mAnimator->Release();
		BaseBall({ 0, 0}).Release();
	}

}