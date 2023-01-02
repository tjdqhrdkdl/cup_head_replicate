#include "yaCrackShot.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaMonster.h"


namespace ya
{
	float CrackShot::CoolTime = 0.5f;
	float CrackShot::AliveTime = 3.0f;
	float CrackShot::BulletDamage = 10.0f;
	float CrackShot::EXDamage = 20.0f;

	CrackShot::CrackShot(Vector2 dir, bool special)
		: Bullet(dir, special)
		, mSpeed(1100.0f)
		, mAliveTimeChecker(0.0f)
	{
		AddComponent(mAnimator);
		SetName(L"CrackShot");
		SetPos({ 0,0 });
		Animator* effectAnimator = GetShootEffect()->GetAnimator();
		effectAnimator->CreateAnimation(L"BulletShotSpark", L"..\\Resources\\Image\\CrackShot\\Bullet\\Shot Spark\\weapon_crackshot_spark_00", 5, 0.03f, false, false);
		effectAnimator->GetCompleteEvent(L"BulletShotSpark") = std::bind(&ShootEffect::ShootEffectCompleteEvent, GetShootEffect());

		mCrackShootEffect = new ShootEffect();
		Animator* crackEffectAnimator = mCrackShootEffect->GetAnimator();
		crackEffectAnimator->CreateAnimation(L"BulletCrackShotSpark", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Shot VFX\\A\\crack_bullet_VFX_a_00", 8, 0.03f, false, false);
		crackEffectAnimator->GetCompleteEvent(L"BulletCrackShotSpark") = std::bind(&ShootEffect::ShootEffectCompleteEvent, mCrackShootEffect);
		crackEffectAnimator->Play(L"BulletCrackShotSpark", false);

		GetAnimator()->CreateAnimation(L"BulletAIdleUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Up\\A\\crack_bullet_a_00", 13, 0.05f, false, false, { 0,70 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Down\\A\\crack_bullet_a_00", 13, 0.05f, false, false, { 0,-30 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleRight", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Straight\\A\\crack_bullet_a_00", 13, 0.05f, false, false, { -20,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleLeft", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Straight\\A\\crack_bullet_a_00", 13, 0.05f, false, true, { 20,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleRightUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalUp\\A\\crack_bullet_a_00", 13, 0.05f, false, false, { -40,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleLeftUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalUp\\A\\crack_bullet_a_00", 13, 0.05f, false, true, { 40,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleRightDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalDown\\A\\crack_bullet_a_00", 13, 0.05f, false, false, { -40,35 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletAIdleLeftDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalDown\\A\\crack_bullet_a_00", 13, 0.05f, false, true, { 40,35 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletBIdleUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Up\\B\\crack_bullet_b_00", 13, 0.05f, false, false, { 0,70 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Down\\B\\crack_bullet_b_00", 13, 0.05f, false, false, { 0,-30 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleRight", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Straight\\B\\crack_bullet_b_00", 13, 0.05f, false, false, { -20,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleLeft", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Straight\\B\\crack_bullet_b_00", 13, 0.05f, false, true, { 20,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleRightUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalUp\\B\\crack_bullet_b_00", 13, 0.05f, false, false, { -40,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleLeftUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalUp\\B\\crack_bullet_b_00", 13, 0.05f, false, true, { 40,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleRightDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalDown\\B\\crack_bullet_b_00", 13, 0.05f, false, false, { -40,35 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletBIdleLeftDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalDown\\B\\crack_bullet_b_00", 13, 0.05f, false, true, { 40,35 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletCIdleUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Up\\C\\crack_bullet_c_00", 13, 0.05f, false, false, { 0,70 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Down\\C\\crack_bullet_c_00", 13, 0.05f, false, false, { 0,-30 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleRight", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Straight\\C\\crack_bullet_c_00", 13, 0.05f, false, false, { -20,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleLeft", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\Straight\\C\\crack_bullet_c_00", 13, 0.05f, false, true, { 20,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleRightUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalUp\\C\\crack_bullet_c_00", 13, 0.05f, false, false, { -40,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleLeftUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalUp\\C\\crack_bullet_c_00", 13, 0.05f, false, true, { 40,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleRightDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalDown\\C\\crack_bullet_c_00", 13, 0.05f, false, false, { -40,35 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCIdleLeftDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Idle\\DiagonalDown\\C\\crack_bullet_c_00", 13, 0.05f, false, true, { 40,35 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletDeath", L"..\\Resources\\Image\\CrackShot\\Bullet\\Death\\B\\crack_bullet_death_b_00", 8, 0.04f, false, false, { 0,100 }, true, false);
		
		GetAnimator()->CreateAnimation(L"BulletCometIdleUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\Up\\A\\crack_comet_a_00", 6, 0.05f, false, false, { 0,70 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\Down\\A\\crack_comet_a_00", 6, 0.05f, false, false, { 0,-30 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleRight", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\Straight\\A\\crack_comet_a_00", 6, 0.05f, false, false, { -130,-10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleLeft", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\Straight\\A\\crack_comet_a_00", 6, 0.05f, false, true, { 130,-10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleRightUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\DiagonalUp\\A\\crack_comet_a_00", 6, 0.05f, false, false, { -130,220 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleLeftUp", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\DiagonalUp\\A\\crack_comet_a_00", 6, 0.05f, false, true, { 130,220 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleRightDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\DiagonalDown\\A\\crack_comet_a_00", 6, 0.05f, false, false, { -130,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIdleLeftDown", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Idle\\DiagonalDown\\A\\crack_comet_a_00", 6, 0.05f, false, true, { 110,0 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletCometDeathRight", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Death\\A\\crack_comet_death_a_00", 7, 0.04f, false, false, { -50,100 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometDeathLeft", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Death\\A\\crack_comet_death_a_00", 7, 0.04f, false, true, { 50,100 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletCometIntro", L"..\\Resources\\Image\\CrackShot\\Bullet\\Comet\\Intro\\A\\crack_comet_a_intro_00", 3, 0.04f, false, false, { 0,0 }, true, false);


		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchUp", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\Up\\crackshot_ex_launch_00", 12, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchDown", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\Down\\crackshot_ex_launch_00", 12, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchRight", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\Straight\\crackshot_ex_launch_00", 12, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchLeft", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\Straight\\crackshot_ex_launch_00", 12, 0.05f, false, true, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchRightUp", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\DiagonalUp\\crackshot_ex_launch_00", 12, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchLeftUp", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\DiagonalUp\\crackshot_ex_launch_00", 12, 0.05f, false, true, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchRightDown", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\DiagonalDown\\crackshot_ex_launch_00", 12, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialLaunchLeftDown", L"..\\Resources\\Image\\CrackShot\\EX\\Launch\\DiagonalDown\\crackshot_ex_launch_00", 12, 0.05f, false, true, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdle", L"..\\Resources\\Image\\CrackShot\\EX\\Idle\\crackshot_ex_idle_00", 13, 0.03f, false, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialSpin", L"..\\Resources\\Image\\CrackShot\\EX\\Spin\\crackshot_ex_statespot_00", 20, 0.03f, false, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialDeath", L"..\\Resources\\Image\\CrackShot\\EX\\Disappearing\\crackshot_ex_disappearing_00", 17, 0.03f, false, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialShootUp", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\Up\\crackshot_ex_parry_planet_00", 5, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootDown", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\Down\\crackshot_ex_parry_planet_00", 5, 0.05f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootRight", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\Straight\\crackshot_ex_parry_planet_00", 5, 0.05f, false, true, { -30,30 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootLeft", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\Straight\\crackshot_ex_parry_planet_00", 5, 0.05f, false, false, { 30,30 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootRightUp", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\DiagonalUp\\crackshot_ex_parry_planet_00", 5, 0.05f, false, true, { 0,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootLeftUp", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\DiagonalUp\\crackshot_ex_parry_planet_00", 5, 0.05f, false, false, { 0,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootRightDown", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\DiagonalDown\\crackshot_ex_parry_planet_00", 5, 0.05f, false, true, { -50,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialShootLeftDown", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\DiagonalDown\\crackshot_ex_parry_planet_00", 5, 0.05f, false, false, { 50,50 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialExplosion", L"..\\Resources\\Image\\CrackShot\\EX\\Parry\\VFX\\Parry Explosion VFX\\crackshot_ex_parry_explode_00", 15, 0.04f, false, false, { 20,180 }, true, false);

		GetAnimator()->GetCompleteEvent(L"BulletSpecialDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletCometDeathRight") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletCometDeathLeft") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialExplosion") = std::bind(&Bullet::BulletDeathCompleteEvent, this);


		GetAnimator()->GetCompleteEvent(L"BulletCometIntro") = std::bind(&CrackShot::BulletCometIntroCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchUp") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchDown") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchRight") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchLeft") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchRightUp") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchLeftUp") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchRightDown") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialLaunchLeftDown") = std::bind(&CrackShot::EXLaunchCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialSpin") = std::bind(&CrackShot::EXSpinCompleteEvent, this);

		if (!mSpecial)
		{
			SetScale({ 50.0f,50.0f });

			SetDamage(BulletDamage);


			effectAnimator->Play(L"BulletShotSpark", false);



			std::wstring dirStr = GetDir().GetDirInStr();
			switch (rand() % 3)
			{
			case 0:
				GetAnimator()->Play(L"BulletAIdle" + dirStr, true);
				break;
			case 1:
				GetAnimator()->Play(L"BulletBIdle" + dirStr, true);
				break;
			case 2:
				GetAnimator()->Play(L"BulletCIdle" + dirStr, true);
				break;
			}
		}
		else
		{
			SetScale({ 100,100 });

			SetDamage(EXDamage);

			effectAnimator->Play(L"BulletShotSpark", false);

			//GetComponent<Collider>()->SetAddPos({ 0,30 });

			std::wstring dirStr = GetDir().GetDirInStr();
			GetAnimator()->Play(L"BulletSpecialLaunch" + dirStr, false);

			mPink = true;
			mEmptyPink = true;

		}
	}

	CrackShot::~CrackShot()
	{
	}

	void CrackShot::Tick()
	{


		Vector2 pos = GetPos();
		mAliveTimeChecker += Time::DeltaTime();

		if (mSpecial)
		{
			if (mParried == true && !mbCrack && !GetComponent<Collider>()->isOff())
			{
				mbCrack = true;

				mSpeed = 1200;
				Collider* destCol = SceneManager::GetCurScene()->GetNearestCollider(this, eColliderLayer::FrontMonster);
				if (destCol == nullptr || dynamic_cast<Monster*>(destCol->GetOwner()) == nullptr)
					mDestDir = GetDir();
				else
					mDestDir = (destCol->GetPos() - GetPos()).Normalize();

				if (mDestDir.x > 0)
				{
					if (mDestDir.x < cosf(70.0f / 180 * PI))
					{
						if (mDestDir.y < 0)
							SetDir(Vector2::Up);
						else
							SetDir(Vector2::Down);
					}
					else if (mDestDir.x < cosf(25.0f / 180 * PI))
					{
						if (mDestDir.y < 0)
							SetDir(Vector2::RightUp);
						else
							SetDir(Vector2::RightDown);
					}
					else
						SetDir(Vector2::Right);
				}
				else
				{
					if (mDestDir.x > -cosf(70.0f / 180 * PI))
					{
						if (mDestDir.y < 0)
							SetDir(Vector2::Up);
						else
							SetDir(Vector2::Down);
					}
					else if (mDestDir.x > -cosf(25.0f / 180 * PI))
					{
						if (mDestDir.y < 0)
							SetDir(Vector2::LeftUp);
						else
							SetDir(Vector2::LeftDown);
					}
					else
						SetDir(Vector2::Left);

				}

				std::wstring dirStr = GetDir().GetDirInStr();
				GetAnimator()->Play(L"BulletSpecialShoot" + dirStr, true);


				Scene* curScene = SceneManager::GetCurScene();
				curScene->AddGameObject(mCrackShootEffect, eColliderLayer::Effect);
				mCrackShootEffect->SetPos(GetPos());
			}
			else if (mbCrack)
				pos += mDestDir * mSpeed * Time::DeltaTime();


			if (mAnimator->GetPlayAnimation()->GetName() == L"BulletSpecialLaunch" + GetDir().GetDirInStr())
			{
				if (GetDir() == Vector2::RightDown || GetDir() == Vector2::RightUp || GetDir() == Vector2::LeftUp || GetDir() == Vector2::LeftDown)
					pos += GetDir() * mSpeed/3 * Time::DeltaTime();
				else
					pos += GetDir() * mSpeed/2 * Time::DeltaTime();
			}

			else if (mAnimator->GetPlayAnimation()->GetName() == L"BulletSpecialIdle")
			{
				mEXShootTimeChecker += Time::DeltaTime();
				if (mEXShootTimeChecker > 2.0f)
				{
					mEXShootTimeChecker = 0;
					CrackShot* comet = new CrackShot(GetDir());
					comet->SetPos(GetPos());
					comet->mCrackTimeChecker = 100.0f;
					comet->SetOwner(GetOwner());
					Scene* curScene = SceneManager::GetCurScene();
					curScene->AddGameObject(comet, eColliderLayer::Player_Projecttile);
				}
			}
		}


		if (!mSpecial && !GetComponent<Collider>()->isOff())
		{
			if (!mbCrack)
			{
				pos = pos + GetDir() * mSpeed * Time::DeltaTime();
				mCrackTimeChecker += Time::DeltaTime();
				if (mCrackTimeChecker > 0.33f)
				{
					mbCrack = true;

					mSpeed = 2200;
					Collider* destCol = SceneManager::GetCurScene()->GetNearestCollider(this, eColliderLayer::FrontMonster);
					if (destCol == nullptr || dynamic_cast<Monster*>(destCol->GetOwner()) == nullptr)
						mDestDir = GetDir();
					else
						mDestDir = (destCol->GetPos() - GetPos()).Normalize();

					if (mDestDir.x > 0)
					{
						if (mDestDir.x < cosf(70.0f / 180 * PI))
						{
							if (mDestDir.y < 0)
								SetDir(Vector2::Up);
							else
								SetDir(Vector2::Down);
						}
						else if (mDestDir.x < cosf(25.0f / 180 * PI))
						{
							if (mDestDir.y < 0)
								SetDir(Vector2::RightUp);
							else
								SetDir(Vector2::RightDown);
						}
						else
							SetDir(Vector2::Right);
					}
					else
					{
						if (mDestDir.x > -cosf(70.0f / 180 * PI))
						{
							if (mDestDir.y < 0)
								SetDir(Vector2::Up);
							else
								SetDir(Vector2::Down);
						}
						else if (mDestDir.x > -cosf(25.0f / 180 * PI))
						{
							if (mDestDir.y < 0)
								SetDir(Vector2::LeftUp);
							else
								SetDir(Vector2::LeftDown);
						}
						else
							SetDir(Vector2::Left);

					}

					GetAnimator()->Play(L"BulletCometIntro" , false);


					Scene* curScene = SceneManager::GetCurScene();
					curScene->AddGameObject(mCrackShootEffect, eColliderLayer::Effect);
					mCrackShootEffect->SetPos(GetPos());
				}
			}

			else
			{
				pos += mDestDir * mSpeed * Time::DeltaTime();
			}
		}

		if (!(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletDeath")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletSpecialDeath")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletSpecialExplosion")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletCometDeathRight")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletCometDeathLeft")
			)
		{

			if (mAliveTimeChecker > AliveTime)
			{
				if (!mSpecial)
				{
					ObjectManager::Destroy(this);
				}

				else if (mAliveTimeChecker > AliveTime * 3)
				{
					mAnimator->Play(L"BulletSpecialDeath", false);
					mAliveTimeChecker = 0;
					GetComponent<Collider>()->SetOff(true);
				}
			}

			SetPos(pos);
		}
		Bullet::Tick();
	}

	void CrackShot::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}

	void CrackShot::OnCollisonEnter(Collider* other, Collider* my)
	{
		Bullet::OnCollisonEnter(other, my);
		if (mbCrack && other->isHitBox() && !(other->isBulletPassing()))
		{
			if (!mSpecial)
			{
				if (mDir.x > 0)
					mAnimator->Play(L"BulletCometDeathRight", false);
				else
					mAnimator->Play(L"BulletCometDeathLeft", false);
			}
		}
		if (mSpecial && other->isHitBox() && !(other->isBulletPassing()))
		{
			mAnimator->Play(L"BulletSpecialExplosion", false);
			GetComponent<Collider>()->SetOff(true);
		}
	}

	void CrackShot::OnCollisonStay(Collider* other, Collider* my)
	{
		Bullet::OnCollisonStay(other, my);

	}

	void CrackShot::OnCollisonExit(Collider* other, Collider* my)
	{
		Bullet::OnCollisonExit(other, my);
	}

	void CrackShot::BulletCometIntroCompleteEvent()
	{
		mAnimator->Play(L"BulletCometIdle"+GetDir().GetDirInStr(), true);
	}

	void CrackShot::EXLaunchCompleteEvent()
	{
		mAnimator->Play(L"BulletSpecialSpin", false);
	}

	void CrackShot::EXSpinCompleteEvent()
	{
		mAnimator->Play(L"BulletSpecialIdle", true);

	}

}