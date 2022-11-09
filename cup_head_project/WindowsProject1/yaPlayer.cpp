#include "yaPlayer.h"
#include "yaTime.h"
#include "yaBullet.h"
#include "yaScenemanager.h"
#include "yaScene.h"
#include "yaInput.h"
#include "yaPicture.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaAnimator.h"
#include "yaPeaShooter.h"

namespace ya {
	Player::Player()
		:mSpeed(200.0f)
		, mGunDir(Vector2::Right)
		, mState(0x00000000)
		, mShooterCoolTime(PeaShooter::GetCoolTime())
		, mShooterCoolTimeChecker(0.0f)
		, mCurGunType(eGunType::PeaShooter)
		, mShootPoint(0)
	{
		SetName(L"Player");
		SetPos({ 200.0f, 500.0f });
		SetScale({ 90.0f, 120.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator); 
		mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_00", 5, 0.1f, false, false, { 0, 0 }, true, true );
		mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_00", 5, 0.1f,false,true, { 0, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"RunRight", L"..\\Resources\\Image\\Cuphead\\Run\\Normal\\cuphead_run_00", 16, 0.03f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"RunLeft", L"..\\Resources\\Image\\Cuphead\\Run\\Normal\\cuphead_run_00", 16, 0.03f, false, true, { 0, 0 }, true, true);
	
		mAnimator->CreateAnimation(L"ShootRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_00", 3, 0.1f, false, false, { 15, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_00", 3, 0.1f, false, true, { -15, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_boil_00", 3, 0.1f, false, false, { 18, -7 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_boil_00", 3, 0.1f, false, true, { -18, -7 }, true, true);
	
		mAnimator->CreateAnimation(L"ShootUpRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootUpLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_00", 3, 0.1f, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilUpRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_boil_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilUpLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_boil_00", 3, 0.1f, false, true, { 0, 0 }, true, true);
	
		mAnimator->CreateAnimation(L"ShootDownRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootDownLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_00", 3, 0.1f, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDownRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_boil_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDownLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_boil_00", 3, 0.1f, false, true, { 0, 0 }, true, true);

		mAnimator->Play(L"IdleRight", true);
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		PlayerKeyInput();
		
		if ((mState & PlayerState_CoolShoot) == PlayerState_CoolShoot)
		{
			mShooterCoolTimeChecker += Time::DeltaTime();
			if (mShooterCoolTimeChecker >= mShooterCoolTime)
			{
				mState &= ~PlayerState_CoolShoot;
				mShooterCoolTimeChecker = 0.0f;
			}
		}
		GameObject::Tick();
	}

	void Player::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	void Player::OnCollisonEnter(Collider* other)
	{
	}

	void Player::OnCollisonStay(Collider* other)
	{
	}

	void Player::OnCollisonExit(Collider* other)
	{
	}

	void Player::PlayerKeyInput()
	{
		Vector2 pos = GetPos();
		std::wstring wstrPlDir = GetPlayerStrDir();
		std::wstring xDir = GetPlayerXDir();

		// 키 눌러진 상태
		if (KEY_PRESSED(eKeyCode::W))
		{
			pos.y -= 120.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::S))
		{
			pos.y += 120.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::A))
		{
			pos.x -= 120.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::D))
		{
			pos.x += 120.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::X))
		{
			if ((mState & PlayerState_CoolShoot) != PlayerState_CoolShoot)
				Shoot();
			//else if (mShooterCoolTimeChecker > 0.3f)
			//	mAnimator->Play(L"ShootBoil" + wstrPlDir, true);
		}

		// 키 누르는 순간
		// 중복키

		if (false)
		{
		}

		else
		{
			if (KEY_DOWN(eKeyCode::W))
			{
				mAnimator->Play(L"RunRight", true);
				mGunDir = Vector2::Up;
			}
			if (KEY_DOWN(eKeyCode::S))
			{
				mAnimator->Play(L"RunRight", true);
				mGunDir = Vector2::Down;
			}
			if (KEY_DOWN(eKeyCode::A))
			{
				mAnimator->Play(L"RunLeft", true);
				mState |= PlayerState_LookLeft;
				mGunDir = Vector2::Left;
			}
			if (KEY_DOWN(eKeyCode::D))
			{
				mAnimator->Play(L"RunRight", true);
				mState &= ~(PlayerState_LookLeft);
				mGunDir = Vector2::Right;
			}
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			if ((mState & PlayerState_CoolShoot) != PlayerState_CoolShoot)
				Shoot();
			else
				mAnimator->Play(L"ShootBoil" + wstrPlDir, true);
		}

		//키 떼는 순간
		if (KEY_UP(eKeyCode::A) 
			|| KEY_UP(eKeyCode::D)
			|| KEY_UP(eKeyCode::X))
		{
			mAnimator->Play(L"Idle"+xDir, true);
		}

		SetPos(pos);

	}

	void Player::SetShooterCoolTime(eGunType guntype)
	{
		if (guntype == eGunType::PeaShooter)
			mShooterCoolTime = PeaShooter::GetCoolTime();
		else if (guntype == eGunType::CrackShot)
			mShooterCoolTime = 0.5f;
		else if (guntype == eGunType::Spreader)
			mShooterCoolTime = 0.1f;
	}

	std::wstring Player::GetPlayerStrDir()
	{
		std::wstring ret = L"";
		if (mGunDir == Vector2::Left)
			ret = L"Left";
		else if (mGunDir == Vector2::Right)
			ret = L"Right";
		else if (mGunDir == Vector2::Up)
		{
			if ((mState & PlayerState_LookLeft) == PlayerState_LookLeft)
				ret = L"UpLeft";
			else
				ret = L"UpRight";
		}
		else if (mGunDir == Vector2::Down)
		{
			if ((mState & PlayerState_LookLeft) == PlayerState_LookLeft)
				ret = L"DownLeft";
			else
				ret = L"DownRight";
		}
		return ret;
	}

	std::wstring Player::GetPlayerXDir()
	{
		std::wstring xDir = L"";
		if ((mState & PlayerState_LookLeft) == PlayerState_LookLeft)
			xDir = L"Left";
		else
			xDir = L"Right";
		return xDir;
	}

	void Player::Shoot()
	{
		std::wstring wstrPlDir = GetPlayerStrDir();

		Bullet* bullet = nullptr;
		if(mCurGunType == eGunType::PeaShooter)
			bullet = new PeaShooter();
		
		//총알 위치
		Vector2 bulletStartPos = {};
		float addYPos = 0.0f;
		if(mShootPoint ==1)
			addYPos -= 10.0f;
		else if(mShootPoint == 2)
			addYPos -= 20.0f;
		bulletStartPos.x = GetPos().x + GetScale().x / 2 + bullet->GetScale().x / 2;
		bulletStartPos.y = GetPos().y + bullet->GetScale().y - GetScale().y / 2 + addYPos;
		bullet->SetPos(bulletStartPos);
		if (++mShootPoint > 3)
			mShootPoint = 0;
		//총알 방향
		bullet->SetDir(mGunDir);
		Scene* curScene = SceneManager::GetCurScene();
		curScene->AddGameObject(bullet, eColliderLayer::Player_Projecttile);
		mState |= PlayerState_CoolShoot ;
		mAnimator->Play(L"Shoot" + wstrPlDir, false);
	}
}