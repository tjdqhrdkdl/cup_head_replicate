#include "yaPeaShooter.h"
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
	float PeaShooter::CoolTime = 0.2f;
	float PeaShooter::AliveTime = 1.0f;
	float PeaShooter::BulletDamage = 3.3f;
	float PeaShooter::EXDamage = 10.0f;

	PeaShooter::PeaShooter(Vector2 dir, bool special)
		: Bullet(dir, special)
		, mSpeed(1200.0f)
		, mAliveTimeChecker(0.0f)
	{
		SetName(L"PeaShooter");
		SetPos({ 0,0 });
		Animator* effectAnimator = GetShootEffect()->GetAnimator();
		effectAnimator->CreateAnimation(L"BulletShotSpark", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Shot Spark\\weapon_peashot_spark_00", 5, 0.03f, false, false);
		effectAnimator->GetCompleteEvent(L"BulletShotSpark") = std::bind(&ShootEffect::ShootEffectCompleteEvent, GetShootEffect());


		GetAnimator()->CreateAnimation(L"BulletIdleRight", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.01f, false, false, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeft", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, true, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, false, 90);
		GetAnimator()->CreateAnimation(L"BulletIdleDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, false, 270);
		GetAnimator()->CreateAnimation(L"BulletIdleRightUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, false, { 22,10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeftUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, true, { -22,10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleRightDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalDown\\weapon_peashot_main_00", 6, 0.1f, false, false, { -10,15 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeftDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalDown\\weapon_peashot_main_00", 6, 0.1f, false, true, { 10,15 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletDeath", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Death\\weapon_peashot_death_00", 6, 0.02f, false, false, { 0,100 }, true, false);

		GetAnimator()->CreateAnimation(L"BulletSpecialIdleRight", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\Straight\\weapon_peashot_EX_loop_00", 9, 0.05f, false, false, { -50,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleLeft", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\Straight\\weapon_peashot_EX_loop_00", 9, 0.05f, false, true, { 50,50 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleUp", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\Straight\\weapon_peashot_EX_loop_00", 9, 0.05f, false, false, { 0,100 }, true, false, 270);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleDown", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\Straight\\weapon_peashot_EX_loop_00", 9, 0.05f, false, false, { 0,0 }, true, false, 90);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleRightUp", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\DiagonalUp\\weapon_peashot_EX_loop_00", 9, 0.1f, false, false, { -40,180 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleLeftUp", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\DiagonalUp\\weapon_peashot_EX_loop_00", 9, 0.1f, false, true, { 40,180 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleRightDown", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\DiagonalDown\\weapon_peashot_EX_loop_00", 9, 0.1f, false, false, { -30,80 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialIdleLeftDown", L"..\\Resources\\Image\\PeaShooter\\EX\\Idle\\DiagonalDown\\weapon_peashot_EX_loop_00", 9, 0.1f, false, true, { 30,80 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletSpecialDeath", L"..\\Resources\\Image\\PeaShooter\\EX\\Death\\weapon_peashot_ex_death_00", 11, 0.025f, false, false, { 0,100 }, true, false);

		GetAnimator()->GetCompleteEvent(L"BulletSpecialDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		GetAnimator()->GetCompleteEvent(L"BulletSpecialDeath");

		if (!mSpecial)
		{
			SetScale({ 20.0f,20.0f });

			SetDamage(BulletDamage);

			
			effectAnimator->Play(L"BulletShotSpark", false);



			std::wstring dirStr = GetDir().GetDirInStr();
			GetAnimator()->Play(L"BulletIdle" + dirStr, true);
		}
		else
		{
			SetScale({ 150.0f,150.0f });

			SetDamage(EXDamage);

			effectAnimator->Play(L"BulletShotSpark", false);

			GetComponent<Collider>()->SetAddPos({ 0,30 });

			std::wstring dirStr = GetDir().GetDirInStr();
			GetAnimator()->Play(L"BulletSpecialIdle" + dirStr, true);
		}
	}

	PeaShooter::~PeaShooter()
	{
	}

	void PeaShooter::Tick()
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		pos = pos + GetDir() * mSpeed * Time::DeltaTime();
		mAliveTimeChecker += Time::DeltaTime();
		
		if (mSpecial)
		{
			mEXDamageTimeChecker += Time::DeltaTime();
		}


		if (mHitCount == 3)
		{
			GetComponent<Collider>()->SetOff(true);
			mEXDeathTimeChecker += Time::DeltaTime();
		}


		if (!(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletDeath")
			&& !(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletSpecialDeath")
			)
		{
			
			if (mAliveTimeChecker > AliveTime)
			{
				if (!mSpecial)
				{
					ObjectManager::Destroy(this);
				}

				else if(mAliveTimeChecker > AliveTime * 2)
				{
					mAnimator->Play(L"BulletSpecialDeath", false);
				}
			}
			if (mEXDeathTimeChecker > 0.03f)
			{
				mAnimator->Play(L"BulletSpecialDeath", false);
			}
			SetPos(pos);
		}
		Bullet::Tick();
	}

	void PeaShooter::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}

	void PeaShooter::OnCollisonEnter(Collider* other, Collider* my)
	{
		Bullet::OnCollisonEnter(other, my);
		if (mSpecial
			&& other->isHitBox()
			&& other->GetOwner()->GetLayer() ==eColliderLayer::FrontMonster)
		{
			mHitCount++;
		}
	}

	void PeaShooter::OnCollisonStay(Collider* other, Collider* my)
	{
		Bullet::OnCollisonStay(other, my);
		if (mSpecial && mEXDamageTimeChecker > 0.1)
		{
			PeaShooter::OnCollisonEnter(other, my);
			if (other->isHitBox()
				&& other->GetOwner()->GetLayer() == eColliderLayer::FrontMonster)
			{
				Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
				monster->OnCollisonEnter(my, other);
			}
			mEXDamageTimeChecker = 0;
		}
	}

	void PeaShooter::OnCollisonExit(Collider* other, Collider* my)
	{
		Bullet::OnCollisonExit(other, my);
	}

}