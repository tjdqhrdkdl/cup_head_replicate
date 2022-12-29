#include "yaChomper.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaGround.h"
namespace ya
{
	Chomper::Chomper()
		:mbIsSeed(true)
	{
		SetName(L"Chomper");
		mHp = 8;
		SetScale({ 50.0f,50.0f });
		mCollider = new Collider();
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mVineAnimator = new Animator();
		AddComponent(mVineAnimator);
		mVineAnimator->CreateAnimation(L"GroundBurst", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\flower_vine_groundburst_00", 8, 0.04f, false, false);


		mAnimator->CreateAnimation(L"SeedFall", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Chomper\\Seed\\Seed_Fall_A_", 35, 0.04f, false, false);
		mAnimator->CreateAnimation(L"SeedArrive", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Chomper\\Seed\\Seed_P_", 8, 0.04f, false, false);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Chomper\\Chomper_", 10, 0.04f, false, false);
		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Chomper\\Death\\Chomper_Die_", 16, 0.04f, false, false);

		mAnimator->GetCompleteEvent(L"SeedArrive") = std::bind(&Chomper::ArriveCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"GroundBurst") = std::bind(&Chomper::GroundBurstCompleteEvent, this);

		mAnimator->Play(L"SeedFall", true);
	}

	Chomper::~Chomper()
	{
	}

	void Chomper::Tick()
	{
		Monster::Tick();
		Vector2 pos = GetPos();
		if (mAnimator->GetPlayAnimation() != nullptr 
			&& mAnimator->GetPlayAnimation()->GetName() == L"SeedFall")
		{
			pos.y += 300*Time::DeltaTime();
		}
		SetPos(pos);
	}

	void Chomper::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void Chomper::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			mAnimator->Play(L"SeedArrive", false);
		}
	}

	void Chomper::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Chomper::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Chomper::ArriveCompleteEvent()
	{
		mAnimator->SetPlayAnimation(nullptr);
		mVineAnimator->Play(L"GroundBurst", false);
	}

	void Chomper::GroundBurstCompleteEvent()
	{
		mVineAnimator->SetPlayAnimation(nullptr);
		mAnimator->Play(L"Idle", true);
		SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::FrontMonster);
		mCollider->SetScale({ 50,100 });
	}

	void Chomper::Release()
	{
	}

}