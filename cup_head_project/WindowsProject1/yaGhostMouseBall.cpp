#include "yaGhostMouseBall.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaGround.h"
namespace ya
{
	GhostMouseBall::GhostMouseBall(Vector2 dir)
		:mAliveTime(10)
		,mAliveTimeChecker(0)
	{
		mDestDir = dir;
		mPink = true;
		SetName(L"GhostMouseBall");
		SetScale({ 100.0f, 100.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);


		mAnimator->CreateAnimation(L"Intro", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Bullet\\Pink\\ghost_ball_pink_00", 8, 0.07f, false, false);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Bullet\\Pink\\Idle\\ghost_ball_pink_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Bullet\\Pink\\Death\\ghost_ball_death_pink_00", 6, 0.05f, false, false, {0,230});

		mAnimator->GetCompleteEvent(L"Death") = std::bind(&GhostMouseBall::DeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Intro") = std::bind(&GhostMouseBall::IntroCompleteEvent, this);
		mAnimator->Play(L"Intro", false);
	}

	GhostMouseBall::~GhostMouseBall()
	{
	}

	void GhostMouseBall::Tick()
	{
		GameObject::Tick();
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
		}
		if (mParried)
			ObjectManager::Destroy(this);

		if (mAnimator->GetPlayAnimation()->GetName() != L"Death")
		{
			Vector2 pos = GetPos();
			pos += mDestDir * 400 * Time::DeltaTime();
			SetPos(pos);
		}
	}

	void GhostMouseBall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GhostMouseBall::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (other->GetOwner()->GetLayer() == eColliderLayer::FrontObject
			&& dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			mAnimator->Play(L"Death", false);
			GetComponent<Collider>()->SetOff(true);
		}
	}

	void GhostMouseBall::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void GhostMouseBall::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void GhostMouseBall::DeathCompleteEvent()
	{
		
		ObjectManager::Destroy(this);

	}

	void GhostMouseBall::IntroCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
	}

	void GhostMouseBall::Release()
	{
		mAnimator->Release();
	}

}