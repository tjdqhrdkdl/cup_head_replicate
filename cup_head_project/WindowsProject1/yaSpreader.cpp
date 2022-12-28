#include "yaSpreader.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaMonster.h"
#include "yaPlayer.h"

namespace ya
{
	float Spreader::CoolTime = 0.2f;
	float Spreader::AliveTime = 1.0f;
	float Spreader::BulletDamage = 2.0f;
	float Spreader::EXDamage = 10.0f;

	Spreader::Spreader(Vector2 dir, bool special)
		: Bullet(dir, special)
		, mSpeed(1200.0f)
		, mAliveTimeChecker(0.0f)
	{
		SetName(L"Spreader");
		SetPos({ 0,0 });
		Animator* effectAnimator = GetShootEffect()->GetAnimator();
		effectAnimator->CreateAnimation(L"BulletSpreaderSpark", L"..\\Resources\\Image\\Spreader\\Bullet\\Spark\\weapon_spread_spark_00", 5, 0.03f, false, false);
		effectAnimator->GetCompleteEvent(L"BulletSpreaderSpark") = std::bind(&ShootEffect::ShootEffectCompleteEvent, GetShootEffect());

		mSmokeAnimator = new Animator();

		AddComponent(mSmokeAnimator);
		AddComponent(mAnimator);

		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroUp", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\Up\\spread_ex_smoke_trail_00", 4, 0.05f, false, false, { 0,0 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroDown", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\Down\\spread_ex_smoke_trail_00", 4, 0.05f, false, false, { 0,0 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroRight", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\Straight\\spread_ex_smoke_trail_00", 4, 0.05f, false, false, { 0,0 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroLeft", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\Straight\\spread_ex_smoke_trail_00", 4, 0.05f, false, true, { 0,0 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroRightUp", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\DiagonalUp\\spread_ex_smoke_trail_00", 4, 0.05f, false, false, { 22,10 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroLeftUp", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\DiagonalUp\\spread_ex_smoke_trail_00", 4, 0.05f, false, true, { -22,10 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroRightDown", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\DiagonalDown\\spread_ex_smoke_trail_00", 4, 0.05f, false, false, { -10,15 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIntroLeftDown", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Intro\\DiagonalDown\\spread_ex_smoke_trail_00", 4, 0.05f, false, true, { 10,15 }, true, false);

		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleUp", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\Up\\spread_ex_smoke_trail_00", 5, 0.05f, false, false, { 0,160 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleDown", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\Down\\spread_ex_smoke_trail_00", 5, 0.05f, false, false, { 0,-30 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleRight", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\Straight\\spread_ex_smoke_trail_00", 5, 0.05f, false, false, { -100,50 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleLeft", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\Straight\\spread_ex_smoke_trail_00", 5, 0.05f, false, true, { 100,50 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleRightUp", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\DiagonalUp\\spread_ex_smoke_trail_00", 5, 0.05f, false, false, { -75,170 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleLeftUp", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\DiagonalUp\\spread_ex_smoke_trail_00", 5, 0.05f, false, true, { 75,170 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleRightDown", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\DiagonalDown\\spread_ex_smoke_trail_00", 5, 0.05f, false, false, { -65,15 }, true, false);
		mSmokeAnimator->CreateAnimation(L"BulletSmokeIdleLeftDown", L"..\\Resources\\Image\\Spreader\\EX\\Smoke\\Idle\\DiagonalDown\\spread_ex_smoke_trail_00", 5, 0.05f, false, true, { 65,15 }, true, false);


		GetAnimator()->CreateAnimation(L"BulletIdleUp", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\Up\\spread_large_idle_00", 5, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleDown", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\Down\\spread_large_idle_00", 5, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleRight", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\Straight\\spread_large_idle_00", 5, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeft", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\Straight\\spread_large_idle_00", 5, 0.05f, false, true, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleRightUp", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\DiagonalUp\\spread_large_idle_00", 5, 0.05f, false, false, { 22,10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeftUp", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\DiagonalUp\\spread_large_idle_00", 5, 0.05f, false, true, { -22,10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleRightDown", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\DiagonalDown\\spread_large_idle_00", 5, 0.05f, false, false, { -10,15 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeftDown", L"..\\Resources\\Image\\Spreader\\Bullet\\Idle\\DiagonalDown\\spread_large_idle_00", 5, 0.05f, false, true, { 10,15 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletDeath", L"..\\Resources\\Image\\Spreader\\Bullet\\Death\\spread_large_death_00", 5, 0.03f, false, false, { 0,100 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletHit", L"..\\Resources\\Image\\Spreader\\Bullet\\Hit\\spread_large_hit_00", 7, 0.04f, false, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialIntroUp", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\Up\\spread_ex_intro_00", 6, 0.1f, false, false, { 0,100 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroDown", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\Down\\spread_ex_intro_00", 6, 0.1f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroRight", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\Straight\\spread_ex_intro_00", 6, 0.1f, false, false, { -50,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroLeft", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\Straight\\spread_ex_intro_00", 6, 0.1f, false, true, { 50,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroRightUp", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\DiagonalUp\\spread_ex_intro_00", 6, 0.1f, false, false, { -40,180 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroLeftUp", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\DiagonalUp\\spread_ex_intro_00", 6, 0.1f, false, true, { 40,180 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroRightDown", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\DiagonalDown\\spread_ex_intro_00", 6, 0.1f, false, false, { -30,80 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIntroLeftDown", L"..\\Resources\\Image\\Spreader\\EX\\Intro\\DiagonalDown\\spread_ex_intro_00", 6, 0.1f, false, true, { 30,80 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialIdleUp", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\Up\\spread_ex_idle_00", 5, 0.05f, false, false, { 0,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleDown", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\Down\\spread_ex_idle_00", 5, 0.05f, false, false, { 0,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleRight", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\Straight\\spread_ex_idle_00", 5, 0.05f, false, false, { 0,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleLeft", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\Straight\\spread_ex_idle_00", 5, 0.05f, false, true, { 0,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleRightUp", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\DiagonalUp\\spread_ex_idle_00", 5, 0.05f, false, false, { 0,80 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleLeftUp", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\DiagonalUp\\spread_ex_idle_00", 5, 0.05f, false, true, { 0,80 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleRightDown", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\DiagonalDown\\spread_ex_idle_00", 5, 0.05f, false, false, { 10,80 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleLeftDown", L"..\\Resources\\Image\\Spreader\\EX\\Idle\\DiagonalDown\\spread_ex_idle_00", 5, 0.05f, false, true, { -10,80 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialDeath", L"..\\Resources\\Image\\Spreader\\EX\\Death\\spread_ex_death_00", 8, 0.03f, false, false, { 0,100 }, true, false);

		GetAnimator()->GetCompleteEvent(L"BulletSpecialDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletHit") = std::bind(&Bullet::BulletDeathCompleteEvent, this);

		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroUp") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroDown") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroRight") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroLeft") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroRightUp") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroLeftUp") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroRightDown") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		mSmokeAnimator->GetCompleteEvent(L"BulletSmokeIntroLeftDown") = std::bind(&Spreader::SmokeIntroCompleteEvent, this);
		if (!mSpecial)
		{
			SetScale({ 20.0f,20.0f });

			SetDamage(BulletDamage);


			Spreader::AliveTime = 0.3f;



			std::wstring dirStr = GetDir().GetDirInStr();
			if (dirStr != L"")
			{
				GetAnimator()->Play(L"BulletIdle" + dirStr, true);
				effectAnimator->Play(L"BulletSpreaderSpark", false);
			}
		}
		else
		{
			SetScale({ 100.0f,100.0f });

			SetDamage(EXDamage);
			mSpeed = 800;
			Spreader::AliveTime = 3.0f;

			effectAnimator->Play(L"BulletSpreaderSpark", false);

			GetComponent<Collider>()->SetAddPos({ 0,30 });

			std::wstring dirStr = GetDir().GetDirInStr();
			if (dirStr != L"")
			{
				GetAnimator()->Play(L"BulletSpecialIdle" + dirStr, true);
				mSmokeAnimator->Play(L"BulletSmokeIntro" + dirStr, false);
			}
		}
	}

	Spreader::~Spreader()
	{
	}

	void Spreader::Tick()
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		pos = pos + GetDir() * mSpeed * Time::DeltaTime();
		mAliveTimeChecker += Time::DeltaTime();





		if (!(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletDeath")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletSpecialDeath")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletHit")
			)
		{

			if (mAliveTimeChecker > AliveTime)
			{
				if (!mSpecial)
				{
					mAnimator->Play(L"BulletDeath", false);
					GetComponent<Collider>()->SetOff(true);
				}

				else if (mAliveTimeChecker > AliveTime * 2)
				{
					mAnimator->Play(L"BulletSpecialDeath", false);
				}
			}

			SetPos(pos);
		}
		Bullet::Tick();
	}

	void Spreader::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}

	void Spreader::Shoot(Vector2 dir, Player* player, bool special)
	{
		Scene* curScene = SceneManager::GetCurScene();
		if (special == false)
		{
			for (size_t i = 0; i < 5; i++)
			{
				Vector2 bulletDir = math::Rotate(dir, 15.0f * i - 30);
				Spreader* newSpread = new Spreader(bulletDir, special);
				if (bulletDir.x > 0)
				{
					if (bulletDir.y > 0)
					{
						newSpread->mAnimator->Play(L"BulletIdleRightDown", true);
					}

					else if (bulletDir.y < 0)
					{
						newSpread->mAnimator->Play(L"BulletIdleRightUp", true);
					}
				}
				else if (bulletDir.x < 0)
				{
					if (bulletDir.y > 0)
					{
						newSpread->mAnimator->Play(L"BulletIdleLeftDown", true);
					}
					else if (bulletDir.y < 0)
					{
						newSpread->mAnimator->Play(L"BulletIdleLeftUp", true);
					}
				}
				newSpread->Initialize();
				newSpread->SetOwner(player);
				player->SetBulletStartPos(newSpread);
				curScene->AddGameObject(newSpread, eColliderLayer::Player_Projecttile);


			}
		}
		else
		{
			Vector2 vectors[8] = { Vector2::Up, Vector2::Down, Vector2::Right, Vector2::Left, Vector2::RightUp, Vector2::RightDown, Vector2::LeftUp, Vector2::LeftDown };
			for (size_t i = 0; i < 8; i++)
			{
				Vector2 bulletDir = vectors[i];
				Spreader* newSpread = new Spreader(bulletDir, special);
				newSpread->Initialize();
				newSpread->SetOwner(player);
				player->SetBulletStartPos(newSpread);
				curScene->AddGameObject(newSpread, eColliderLayer::Player_Projecttile);
			}

		}

	}

	void Spreader::OnCollisonEnter(Collider* other, Collider* my)
	{
		Bullet::OnCollisonEnter(other, my);
		if (other->isHitBox() && !(other->isBulletPassing()))
		{
			if (!mSpecial)
			{
				mAnimator->Play(L"BulletHit", false);
				GetComponent<Collider>()->SetOff(true);
			}

			else
			{
				if (other->GetOwner()->GetLayer() == eColliderLayer::FrontMonster
					|| other->GetOwner()->GetLayer() == eColliderLayer::BehindMonster
					)
				{
					mAnimator->Play(L"BulletSpecialDeath", false);
					GetComponent<Collider>()->SetOff(true);
					mSmokeAnimator->SetPlayAnimation(nullptr);
				}
			}
		}
	}

	void Spreader::OnCollisonStay(Collider* other, Collider* my)
	{
		Bullet::OnCollisonStay(other, my);
	}

	void Spreader::OnCollisonExit(Collider* other, Collider* my)
	{
		Bullet::OnCollisonExit(other, my);
	}

	void Spreader::SmokeIntroCompleteEvent()
	{
		std::wstring dirStr = GetDir().GetDirInStr();
		mSmokeAnimator->Play(L"BulletSmokeIdle" + dirStr, true);
	}

}