#include "yaGhostMouse.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaGhostMouseBall.h"
#include "yaBossCanRatScene.h"
namespace ya
{
	GhostMouse::GhostMouse(bool right)
		:mbIntro(true)
		,mBallTime(7)
		,mBallTimeChecker(0)
	{
		SetName(L"GhostMouse");
		mHp = 10;
		mbRight = right;
		if (mbRight)
			mBallTimeChecker = 4;
		SetPos({ 800,300 });
		SetScale({ 130.0f,200.0f });
		mCollider = new Collider();
		mCollider->SetDanger(false);
		AddComponent(mCollider);
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Intro\\ghost_mouse_intro_00", 27, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenGhostMouseIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Intro\\ghost_mouse_intro_00", 27, 0.04f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Intro\\ghost_mouse_intro_00", 27, 0.04f, false, true)
			, mAnimator->CreateAnimation(L"LightenGhostMouseIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Intro\\ghost_mouse_intro_00", 27, 0.04f, false, true));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Idle\\ghost_mouse_idle_00", 17, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenGhostMouseIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Idle\\ghost_mouse_idle_00", 17, 0.04f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Idle\\ghost_mouse_idle_00", 17, 0.04f, false, true)
			, mAnimator->CreateAnimation(L"LightenGhostMouseIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Idle\\ghost_mouse_idle_00", 17, 0.04f, false, true));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseDeath", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Death\\ghost_mouse_death_00", 34, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenGhostMouseIdle", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Death\\ghost_mouse_death_00", 34, 0.04f, false, false));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseAttackIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Attack\\Pink\\ghost_mouse_pink_attack_00", 16, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenGhostMouseAttackIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Attack\\Pink\\ghost_mouse_pink_attack_00", 16, 0.04f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseAttackIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Attack\\Pink\\ghost_mouse_pink_attack_00", 16, 0.04f, false, true)
			, mAnimator->CreateAnimation(L"LightenGhostMouseAttackIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Attack\\Pink\\ghost_mouse_pink_attack_00", 16, 0.04f, false, true));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseAttackOutroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Attack\\Outro\\ghost_mouse_attack_outro_00", 9, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenGhostMouseAttackOutroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Attack\\Outro\\ghost_mouse_attack_outro_00", 9, 0.04f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"GhostMouseAttackOutroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Jail\\Ghost Mouse\\Attack\\Outro\\ghost_mouse_attack_outro_00", 9, 0.04f, false, true)
			, mAnimator->CreateAnimation(L"LightenGhostMouseAttackOutroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Lighten\\Jail\\Ghost Mouse\\Attack\\Outro\\ghost_mouse_attack_outro_00", 9, 0.04f, false, true));

		
		mAnimator->GetCompleteEvent(L"GhostMouseIntroRight") = std::bind(&GhostMouse::GhostMouseIntroCompletEvent, this);
		mAnimator->GetCompleteEvent(L"GhostMouseIntroLeft") = std::bind(&GhostMouse::GhostMouseIntroCompletEvent, this);
		mAnimator->GetCompleteEvent(L"GhostMouseAttackIntroRight") = std::bind(&GhostMouse::GhostMouseAttackIntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"GhostMouseAttackIntroLeft") = std::bind(&GhostMouse::GhostMouseAttackIntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"GhostMouseAttackOutroRight") = std::bind(&GhostMouse::GhostMouseAttackOutroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"GhostMouseAttackOutroLeft") = std::bind(&GhostMouse::GhostMouseAttackOutroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"GhostMouseDeath") = std::bind(&GhostMouse::GhostMouseDeathCompleteEvent, this);


		if (mbRight)
			mAnimator->Play(L"GhostMouseIntroRight", false);
		else
			mAnimator->Play(L"GhostMouseIntroLeft", false);

		GhostMouseBall({0,0});
	}

	GhostMouse::~GhostMouse()
	{
	}

	void GhostMouse::Tick()
	{
		Vector2 pos = GetPos();
		Monster::Tick();
		if (mbIntro)
		{
			if (mbRight)
				pos.x += Time::DeltaTime() * 400;
			else
				pos.x -= Time::DeltaTime() * 400;
		}
		SetPos(pos);

		mBallTimeChecker += Time::DeltaTime();
		if (mBallTimeChecker > mBallTime)
		{
			if (mbRight)
				mAnimator->Play(L"GhostMouseAttackIntroRight", false);
			else
				mAnimator->Play(L"GhostMouseAttackIntroLeft", false);
			mBallTimeChecker = 0;
		}

		if (mHp < 0 && mAnimator->GetPlayAnimation()->GetName()!=L"GhostMouseDeath")
		{
			mAnimator->Play(L"GhostMouseDeath", false);
			mCollider->SetOff(true);
		}
	}

	void GhostMouse::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void GhostMouse::SummonBall()
	{
	}

	void GhostMouse::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void GhostMouse::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void GhostMouse::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void GhostMouse::GhostMouseIntroCompletEvent()
	{
		if(mbRight)
			mAnimator->Play(L"GhostMouseIdleRight", true);
		else
			mAnimator->Play(L"GhostMouseIdleLeft", true);
		mbIntro = false;
	}

	void GhostMouse::GhostMouseAttackIntroCompleteEvent()
	{
		if (mbRight)
			mAnimator->Play(L"GhostMouseAttackOutroRight", false);
		else
			mAnimator->Play(L"GhostMouseAttackOutroLeft", false);
		Player* player = dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->GetScenePlayer();
		Vector2 playerPos = player->GetPos();
		Vector2 destPos = playerPos - GetPos();
		GhostMouseBall* ball = new GhostMouseBall(destPos.Normalize());
		Vector2 ballPos = GetPos();
		ballPos.y -= GetScale().y/2;
		ball->SetPos(ballPos);
		ball->Initialize();
		SceneManager::GetCurScene()->AddGameObject(ball, eColliderLayer::Monster_Projecttile);

	}

	void GhostMouse::GhostMouseAttackOutroCompleteEvent()
	{
		if (mbRight)
			mAnimator->Play(L"GhostMouseIdleRight", true);
		else
			mAnimator->Play(L"GhostMouseIdleLeft", true);
	}

	void GhostMouse::GhostMouseDeathCompleteEvent()
	{
		mOwnerCat->DeleteGhostMouse(!mbRight);
		ObjectManager::Destroy(this);
	}

	void GhostMouse::Release()
	{
		mAnimator->Release();
		GhostMouseBall({0,1}).Release();
	}

}