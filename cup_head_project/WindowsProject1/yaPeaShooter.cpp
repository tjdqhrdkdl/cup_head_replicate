#include "yaPeaShooter.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaPicture.h"
#include "yaCamera.h"
#include "yaObjectManager.h"



namespace ya
{
	float PeaShooter::CoolTime = 0.2f;
	float PeaShooter::AliveTime = 1.0f;
	PeaShooter::PeaShooter(Vector2 dir)
		: Bullet(dir)
		,mSpeed(1200.0f)
		,mAliveTimeChecker(0.0f)
	{
		SetName(L"PeaShooter");
		SetPos({ 0,0 });
		SetScale({ 20.0f,20.0f });
		SetDamage(3.3f);
		Animator* effectAnimator = GetShootEffect()->GetAnimator();
		effectAnimator->CreateAnimation(L"BulletShotSpark", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Shot Spark\\weapon_peashot_spark_00", 5, 0.03f, false, false);
		effectAnimator->GetCompleteEvent(L"BulletShotSpark") = std::bind(&ShootEffect::ShootEffectCompleteEvent, GetShootEffect());
		effectAnimator->Play(L"BulletShotSpark", false);


		GetAnimator()->CreateAnimation(L"BulletIdleRight", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.01f, false, false, {0,0}, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeft", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, true, { 0,0 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, false, 90);
		GetAnimator()->CreateAnimation(L"BulletIdleDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, false, 270);
		GetAnimator()->CreateAnimation(L"BulletIdleRightUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, false, { 22,10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeftUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, true, { -22,10 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleRightDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalDown\\weapon_peashot_main_00", 6, 0.1f, false, false, { -10,15 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletIdleLeftDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalDown\\weapon_peashot_main_00", 6, 0.1f, false, true, { 10,15 }, true, false);
		GetAnimator()->CreateAnimation(L"BulletDeath", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Death\\weapon_peashot_death_00", 6, 0.01f, false, false, { 0,100 }, true, false);
		
		GetAnimator()->GetCompleteEvent(L"BulletDeath") = std::bind(&Bullet::BulletDeathCompleteEvent, this);
		
		std::wstring dirStr = GetDir().GetDirInStr();
		GetAnimator()->Play(L"BulletIdle" + dirStr, true);
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
		

		if (!(GetAnimator()->GetPlayAnimation()->GetName() == L"BulletDeath"))
		{
			SetPos(pos);
			if (mAliveTimeChecker > AliveTime)
				ObjectManager::Destroy(this);
		}
		Bullet::Tick();
	}

	void PeaShooter::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}

}