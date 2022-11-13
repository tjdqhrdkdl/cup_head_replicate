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
	float PeaShooter::CoolTime = 1.0f;
	float PeaShooter::AliveTime = 1.0f;
	PeaShooter::PeaShooter(Vector2 dir)
		: Bullet(dir)
		,mSpeed(1200.0f)
		,mAliveTimeChecker(0.0f)
	{
		SetName(L"PeaShooter");
		SetPos({ 0,0 });
		SetScale({ 20.0f,20.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"BulletIdleRight", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.001f, false, false, { 0,0 }, true, true);
		mAnimator->CreateAnimation(L"BulletIdleLeft", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, true, { 0,0 }, true, true);
		mAnimator->CreateAnimation(L"BulletIdleUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, true, 90);
		mAnimator->CreateAnimation(L"BulletIdleDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\Straight\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, true, 270);
		mAnimator->CreateAnimation(L"BulletIdleRightUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, true);
		mAnimator->CreateAnimation(L"BulletIdleLeftUp", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, true, 90);
		mAnimator->CreateAnimation(L"BulletIdleRightDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, true, 270);
		mAnimator->CreateAnimation(L"BulletIdleLeftDown", L"..\\Resources\\Image\\PeaShooter\\Bullet\\Idle\\DiagonalUp\\weapon_peashot_main_00", 6, 0.1f, false, false, { 0,0 }, true, true, 180);
		
		std::wstring dirStr = GetDir().GetDirInStr();
		mAnimator->Play(L"BulletIdle" + dirStr, true);
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
		
		SetPos(pos);
		
		if (mAliveTimeChecker > AliveTime)
			ObjectManager::Destroy(this);

		Bullet::Tick();
	}

	void PeaShooter::Render(HDC hdc)
	{
		Bullet::Render(hdc);
	}

}