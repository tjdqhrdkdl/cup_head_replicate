#include "yaMiniFlower.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaGround.h"
#include "yaMiniFlowerBullet.h"
#include "yaBossCarnationScene.h"
#include "yaPlayer.h"
namespace ya
{
	MiniFlower::MiniFlower()
		:mbIsSeed(true)
	{
		SetName(L"MiniFlower");
		mHp = 8;
		mInvincible = true;
		SetScale({ 50.0f,50.0f });
		mCollider = new Collider();
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mVineAnimator = new Animator();
		AddComponent(mVineAnimator);
		mVineAnimator->CreateAnimation(L"GroundBurst", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\flower_vine_groundburst_00", 8, 0.04f, false, false);
		mVineAnimator->CreateAnimation(L"VineA", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\VFT_Vine_", 17, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"VineB", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\MF_Vine_B_", 18, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"VineC", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Vine_C_", 21, 0.04f, false, false);
		mVineAnimator->CreateAnimation(L"ReverseVineA", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Reversed\\VFT_Vine_", 17, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"ReverseVineB", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Reversed\\MF_Vine_B_", 18, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"ReverseVineC", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Reversed\\Vine_C_", 21, 0.04f, false, false);


		mAnimator->CreateAnimation(L"SeedFall", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Seed\\Falling_A_", 34, 0.04f, false, false);
		mAnimator->CreateAnimation(L"SeedArrive", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Seed\\Seed_Grow_", 8, 0.04f, false, false);

		mAnimator->CreateAnimation(L"Intro", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Intro\\MF_A_", 6, 0.04f, false, false);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Idle\\MF_A_", 9, 0.04f, false, false);
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"Attack", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Attack\\MF_A_", 18, 0.06f, false, false)
			, mAnimator->CreateAnimation(L"LightenAttack", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Seeds\\Mini Flower\\Attack\\MF_A_", 18, 0.06f, false, false));
		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Mini Flower\\Death\\MF_Die_", 17, 0.04f, false, false);

		mAnimator->GetCompleteEvent(L"SeedArrive") = std::bind(&MiniFlower::ArriveCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Death") = std::bind(&MiniFlower::DeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Intro") = std::bind(&MiniFlower::IntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&MiniFlower::AttackCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"GroundBurst") = std::bind(&MiniFlower::GroundBurstCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"VineA") = std::bind(&MiniFlower::VineGrowCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"VineB") = std::bind(&MiniFlower::VineGrowCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"VineC") = std::bind(&MiniFlower::VineGrowCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"ReverseVineA") = std::bind(&MiniFlower::VineReverseCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"ReverseVineB") = std::bind(&MiniFlower::VineReverseCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"ReverseVineC") = std::bind(&MiniFlower::VineReverseCompleteEvent, this);

		mAnimator->Play(L"SeedFall", true);
	}

	MiniFlower::~MiniFlower()
	{
	}

	void MiniFlower::Tick()
	{
		Monster::Tick();
		Vector2 pos = GetPos();
		if (mAnimator->GetPlayAnimation() != nullptr)
		{
			if (mAnimator->GetPlayAnimation()->GetName() == L"SeedFall")
			{
				pos.y += 300 * Time::DeltaTime();
			}

			if (mAnimator->GetPlayAnimation()->GetName() == L"Idle")
			{
				if (pos.y > 150)
				{
					pos.y -= 200 * Time::DeltaTime();
					mVineAnimator->SetAddPos({ mVineAnimator->GetAddPos().x, mVineAnimator->GetAddPos().y + 200 * Time::DeltaTime() });
				}
				else
				{
					if (mbGoRight)
					{
						pos.x += 200 * Time::DeltaTime();
						if (pos.x > 1000)
							mbGoRight = false;
					}
					else
					{
						pos.x -= 200 * Time::DeltaTime();
						if (pos.x < 100)
							mbGoRight = true;
					}
				}

				mAttackTimeChecker += Time::DeltaTime();
				if (mAttackTimeChecker > 5)
				{
					mAnimator->Play(L"Attack", false);
					mInvincible = false;
					mAttackTimeChecker = 0;
					Vector2 plPos = dynamic_cast<BossCarnationScene*>(SceneManager::GetCurScene())->GetScenePlayer()->GetPos();
					Vector2 destDir = (plPos - GetPos()).Normalize();
					MiniFlowerBullet* bullet = new MiniFlowerBullet(destDir);
					bullet->SetPos(GetPos());
					SceneManager::GetCurScene()->AddGameObject(bullet, eColliderLayer::Monster_Projecttile);
				}
			}
			SetPos(pos);

			if (mHp < 0 && mAnimator->GetPlayAnimation()->GetName() != L"Death")
			{
				mAnimator->Play(L"Death", false);
				mCollider->SetOff(true);
			}
		}
	}

	void MiniFlower::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void MiniFlower::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			mAnimator->Play(L"SeedArrive", false);
		}
	}

	void MiniFlower::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void MiniFlower::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void MiniFlower::ArriveCompleteEvent()
	{
		mAnimator->SetPlayAnimation(nullptr);
		mVineAnimator->Play(L"GroundBurst", false);
	}

	void MiniFlower::GroundBurstCompleteEvent()
	{
		switch (rand()%3)
		{
		case 0:
			mVineAnimator->Play(L"VineA", false);
			break;
		case 1:
			mVineAnimator->Play(L"VineB", false);
			break;
		case 2:
			mVineAnimator->Play(L"VineC", false);
			break;
		}
		SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::FrontMonster);
		mCollider->SetScale({ 50,100 });
	}

	void MiniFlower::VineGrowCompleteEvent()
	{
		Vector2 pos = GetPos();
		if (mVineAnimator->GetPlayAnimation()->GetName() == L"VineA")
		{
			pos.y -= 310;
			mVineAnimator->Play(L"ReverseVineA", false);
			mVineAnimator->SetAddPos({ 0,310 });
		}
		else if (mVineAnimator->GetPlayAnimation()->GetName() == L"VineB")
		{	
			pos.y -= 390;
			mVineAnimator->Play(L"ReverseVineB", false);
			mVineAnimator->SetAddPos({ 0,390 });

		}
		else if (mVineAnimator->GetPlayAnimation()->GetName() == L"VineC")
		{
			pos.y -= 470;
			mVineAnimator->SetAddPos({ 0,470 });
			mVineAnimator->Play(L"ReverseVineC", false);
		}		
		SetPos(pos);
		mCollider->SetScale({ 80,80 });
		mAnimator->Play(L"Intro", false);
	}

	void MiniFlower::VineReverseCompleteEvent()
	{
		mVineAnimator->SetPlayAnimation(nullptr);
	}

	void MiniFlower::IntroCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
	}

	void MiniFlower::AttackCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
		mInvincible = true;
	}

	void MiniFlower::DeathCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}
	void MiniFlower::Release()
	{
	}

}