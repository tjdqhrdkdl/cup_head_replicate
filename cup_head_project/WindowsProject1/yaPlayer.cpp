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
	float ShootAnimTime = 0.1f;
	Player::Player()
		:mSpeed(200.0f)
		, mGunDir(Vector2::Right)
		, mCurState(PlayerState_LookRight)
		, mShooterCoolTime(PeaShooter::GetCoolTime())
		, mShooterCoolTimeChecker(0.0f)
		, mCurGunType(eGunType::PeaShooter)
		, mShootPoint(0)
		, mReloading(false)
		, mShootAnimationTimeChecker(0.0f)
	{
		SetName(L"Player");
		SetPos({ 400.0f, 400.0f });
		SetScale({ 90.0f, 120.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator); 
		mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_00", 5, 0.1f, false, false, { 0, 0 }, true, true );
		mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_00", 5, 0.1f,false,true, { 0, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"RunRight", L"..\\Resources\\Image\\Cuphead\\Run\\Normal\\cuphead_run_00", 16, 0.03f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"RunLeft", L"..\\Resources\\Image\\Cuphead\\Run\\Normal\\cuphead_run_00", 16, 0.03f, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"RunShootingRight", L"..\\Resources\\Image\\Cuphead\\Run\\Shooting\\Straight\\cuphead_run_shoot_00", 17, 0.03f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"RunShootingLeft", L"..\\Resources\\Image\\Cuphead\\Run\\Shooting\\Straight\\cuphead_run_shoot_00", 17, 0.03f, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"RunShootingUpRight", L"..\\Resources\\Image\\Cuphead\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_00", 17, 0.03f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"RunShootingUpLeft", L"..\\Resources\\Image\\Cuphead\\Run\\Shooting\\Diagonal Up\\cuphead_run_shoot_diagonal_up_00", 17, 0.03f, false, true, { 0, 0 }, true, true);

		mAnimator->CreateAnimation(L"ShootRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_00", 4, ShootAnimTime, false, false, { 15, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_00", 4, ShootAnimTime, false, true, { -15, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"ShootBoilRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_boil_00", 3, 0.1f, false, false, { 18, -7 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Straight\\cuphead_shoot_straight_boil_00", 3, 0.1f, false, true, { -18, -7 }, true, true);
	
		mAnimator->CreateAnimation(L"ShootUpRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootUpLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilUpRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_boil_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilUpLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Up\\cuphead_shoot_up_boil_00", 3, 0.1f, false, true, { 0, 0 }, true, true);
	
		mAnimator->CreateAnimation(L"ShootDownRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootDownLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDownRight", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_boil_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDownLeft", L"..\\Resources\\Image\\Cuphead\\Shoot\\Down\\cuphead_shoot_down_boil_00", 3, 0.1f, false, true, { 0, 0 }, true, true);

		mAnimator->CreateAnimation(L"ShootDiagonalRightUp", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootDiagonalLeftUp", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDiagonalRightUp", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_boil_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDiagonalLeftUp", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_boil_00", 3, 0.1f, false, true, { 0, 0 }, true, true);

		mAnimator->CreateAnimation(L"ShootDiagonalRightDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootDiagonalLeftDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDiagonalRightDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_Down_boil_00", 3, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"ShootBoilDiagonalLeftDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_Down_boil_00", 3, 0.1f, false, true, { 0, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"DuckRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_00", 9, 0.05f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DuckLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_00", 9, 0.05f, false, true, { 0, 0 }, true, true);

		mAnimator->CreateAnimation(L"DuckIdleRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_idle_00", 6, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DuckIdleLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_idle_00", 6, 0.1f, false, true, { 0, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"DuckShootRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DuckShootLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DuckShootBoilRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_boil_00", 4, 0.1f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DuckShootBoilLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_boil_00", 4, 0.1f, false, true, { 0, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"JumpRight", L"..\\Resources\\Image\\Cuphead\\Jump\\Cuphead\\cuphead_jump_00", 9, 0.05f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"JumpLeft", L"..\\Resources\\Image\\Cuphead\\Jump\\Cuphead\\cuphead_jump_00", 9, 0.05f, false, true, { 0, 0 }, true, true);
		
		mAnimator->CreateAnimation(L"DashRight", L"..\\Resources\\Image\\Cuphead\\Dash\\Ground\\cuphead_dash_00", 9, 0.05f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DashLeft", L"..\\Resources\\Image\\Cuphead\\Dash\\Ground\\cuphead_dash_00", 9, 0.05f, false, true, { 0, 0 }, true, true);

		mAnimator->CreateAnimation(L"DashAirRight", L"..\\Resources\\Image\\Cuphead\\Dash\\Air\\cuphead_dash_air_00", 9, 0.05f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"DashAirLeft", L"..\\Resources\\Image\\Cuphead\\Dash\\Air\\cuphead_dash_air_00", 9, 0.05f, false, true, { 0, 0 }, true, true);

		mAnimator->CreateAnimation(L"HitRight", L"..\\Resources\\Image\\Cuphead\\HIt\\Ground\\cuphead_hit_00", 7, 0.05f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"HItLeft", L"..\\Resources\\Image\\Cuphead\\HIt\\Ground\\cuphead_hit_00", 7, 0.05f, false, true, { 0, 0 }, true, true);
	
		mAnimator->CreateAnimation(L"HitAirRight", L"..\\Resources\\Image\\Cuphead\\HIt\\Air\\cuphead_hit_air_00", 7, 0.04f, false, false, { 0, 0 }, true, true);
		mAnimator->CreateAnimation(L"HitAirLeft", L"..\\Resources\\Image\\Cuphead\\Hit\\Air\\cuphead_hit_air_00", 7, 0.04f, false, true, { 0, 0 }, true, true);



		mAnimator->Play(L"IdleRight", true);
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		PlayerKeyInput();
		SetAnimation();
		if ((mCurState & PlayerState_Input_X) == PlayerState_Input_X)
			Shoot();
		Move();
		if ((mReloading))
		{
			mShooterCoolTimeChecker += Time::DeltaTime();
			if (mShooterCoolTimeChecker >= mShooterCoolTime)
			{
				mReloading = false;
				mShooterCoolTimeChecker = 0.0f;
			}
		}
		if ((mCurState & PlayerState_OnShoot) == PlayerState_OnShoot)
		{
			mShootAnimationTimeChecker += Time::DeltaTime();
			if (mShootAnimationTimeChecker >= ShootAnimTime * 3)
			{
				mCurState &= ~PlayerState_OnShoot;
				mShootAnimationTimeChecker = 0.0f;
			}
		}
		
		GameObject::Tick();
	}

	void Player::Render(HDC hdc)
	{
		Graphics graphic(hdc);
		FontFamily  fontFamily(L"Arial");
		Font        font(&fontFamily, 12, 0, Gdiplus::UnitPoint);
		PointF      pointF(10.0f, 30.0f);
		SolidBrush  solidBrush(Color(255, 255, 0, 255));
		

		graphic.DrawString(std::to_wstring(mCurState).c_str(), -1, &font, pointF, &solidBrush);
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
		// Ű ������ ����
		if (KEY_PRESSED(eKeyCode::UP))
		{
			mCurState |= PlayerState_Input_Up;
		}
		if (KEY_PRESSED(eKeyCode::DOWN))
		{
			mCurState |= PlayerState_Input_Down;
		}
		if (KEY_PRESSED(eKeyCode::LEFT))
		{
			mCurState |= PlayerState_Input_Left;
			mCurState &= ~PlayerState_LookRight;
		}
		if (KEY_PRESSED(eKeyCode::RIGHT))
		{
			mCurState |= PlayerState_Input_Right;
			mCurState |= PlayerState_LookRight;
		}
		if (KEY_PRESSED(eKeyCode::X))
		{
			mCurState |= PlayerState_Input_X;

		}
		if (KEY_PRESSED(eKeyCode::C))
		{
			mCurState |= PlayerState_Input_C;
		}


		// Ű ������ ����
		// �ߺ�Ű

		//Ű ���� ����
		if (KEY_UP(eKeyCode::UP))
		{
			mCurState &= ~PlayerState_Input_Up;
		}
		if (KEY_UP(eKeyCode::DOWN))
		{
			mCurState &= ~PlayerState_Input_Down;
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mCurState &= ~PlayerState_Input_Left;
		}
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mCurState &= ~PlayerState_Input_Right;
		}
		if (KEY_UP(eKeyCode::X))
		{
			mCurState &= ~PlayerState_Input_X;
		}
		if (KEY_UP(eKeyCode::C))
		{
			mCurState &= ~PlayerState_Input_C;
		}

		if (KEY_DOWN(eKeyCode::Z))
		{
			//Jump()
		}
		if (KEY_DOWN(eKeyCode::V))
		{
			//EX()
		}
		if (KEY_DOWN(eKeyCode::LSHIFT))
		{
			//Dash()
		}
	}

	void Player::SetAnimation()
	{
		// ������ �ڵ����� ���� �ִϸ��̼� ������ �͵� -> shoot��, Duckstart��.
		std::wstring playAnimationName = L"";
		if ((mCurState & PlayerState_LookRight) == PlayerState_LookRight)
		{
			int StateR = mCurState - PlayerState_LookRight;

			if ((StateR & PlayerState_OnHit) == PlayerState_OnHit)
			{
				if ((StateR & PlayerState_OnJump) == PlayerState_OnJump)
					playAnimationName = L"HitAirRight";
				else
					playAnimationName = L"HitRight";
			}
			//else if ((StateLookRight & PlayerState_OnEX) == PlayerState_OnEX)
			//	playAnimationName = L"JumpRight";
			else if ((StateR & PlayerState_OnDash) == PlayerState_OnDash)
			{
				if ((StateR & PlayerState_OnJump) == PlayerState_OnJump)
					playAnimationName = L"DashAirRight";
				else
					playAnimationName = L"DashRight";
			}
			else if ((StateR & PlayerState_OnJump) == PlayerState_OnJump)
				playAnimationName = L"JumpRight";
			
			

			else if ((StateR & PlayerState_Input_C) == PlayerState_Input_C)
			{
				int StateRAim = StateR - PlayerState_Input_C;
				if (StateRAim == PlayerState_None)
					playAnimationName = L"IdleRight";
				else if (StateRAim == PlayerState_Input_Right)
					playAnimationName = L"ShootBoilRight";
				else if (StateRAim == PlayerState_Input_Left)
					playAnimationName = L"ShootBoilLeft";
				else if (StateRAim == PlayerState_Input_Up)
					playAnimationName = L"ShootBoilUpRight";
				else if (StateRAim == PlayerState_Input_Down)
					playAnimationName = L"ShootBoilDownRight";
				else if (StateRAim == PlayerState_Input_Right + PlayerState_Input_Down)
					playAnimationName = L"ShootBoilDiagonalRightDown";
				else if (StateRAim == PlayerState_Input_Right + PlayerState_Input_Up)
					playAnimationName = L"ShootBoilDiagonalRightUp";
				else if (StateRAim == PlayerState_Input_Left + PlayerState_Input_Down)
					playAnimationName = L"ShootBoilDiagonalLeftDown";
				else if (StateRAim == PlayerState_Input_Left + PlayerState_Input_Up)
					playAnimationName = L"ShootBoilDiagonalLeftUp";
				else if ((StateRAim & PlayerState_Input_X) == PlayerState_Input_X)
				{
					int StateRAimShoot = StateRAim - PlayerState_Input_X;
					
					if ((StateRAimShoot & PlayerState_OnShoot) != PlayerState_OnShoot && !mReloading)
					{
						if (StateRAimShoot == PlayerState_None)
							playAnimationName = L"ShootRight";
						else if (StateRAimShoot == PlayerState_Input_Right)
							playAnimationName = L"ShootRight";
						else if (StateRAimShoot == PlayerState_Input_Left)
							playAnimationName = L"ShootLeft";
						else if (StateRAimShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootUpRight";
						else if (StateRAimShoot == PlayerState_Input_Down)
							playAnimationName = L"ShootDownRight";
						else if (StateRAimShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"ShootDiagonalRightDown";
						else if (StateRAimShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"ShootDiagonalRightUp";
						else if (StateRAimShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"ShootDiagonalLeftDown";
						else if (StateRAimShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"ShootDiagonalLeftUp";
					}

					else if ((StateRAimShoot & PlayerState_OnShoot) != PlayerState_OnShoot && mReloading)
					{
						if (StateRAimShoot == PlayerState_None)
							playAnimationName = L"ShootBoilRight";
						else if (StateRAimShoot == PlayerState_Input_Right)
							playAnimationName = L"ShootBoilRight";
						else if (StateRAimShoot == PlayerState_Input_Left)
							playAnimationName = L"ShootBoilLeft";
						else if (StateRAimShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootBoilUpRight";
						else if (StateRAimShoot == PlayerState_Input_Down)
							playAnimationName = L"ShootBoilDownRight";
						else if (StateRAimShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"ShootBoilDiagonalRightDown";
						else if (StateRAimShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"ShootBoilDiagonalRightUp";
						else if (StateRAimShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"ShootBoilDiagonalLeftDown";
						else if (StateRAimShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"ShootBoilDiagonalLeftUp";
					}
				}

			}

			else
			{
				if ((StateR & PlayerState_Input_X) == PlayerState_Input_X)
				{
					int StateRShoot = StateR - PlayerState_Input_X;
					//������ �ڵ����� ���ε� �ִϸ��̼� play
					if ((StateRShoot & PlayerState_OnShoot) != PlayerState_OnShoot && !mReloading)
					{
						if (StateRShoot == PlayerState_None)
							playAnimationName = L"ShootRight";
						else if (StateRShoot == PlayerState_Input_Right)
							playAnimationName = L"RunShootingRight";
						else if (StateRShoot == PlayerState_Input_Left)
							playAnimationName = L"ShootLeft";
						else if (StateRShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootUpRight";
						else if (StateRShoot == PlayerState_Input_Down)
							playAnimationName = L"DuckShootRight";
						else if (StateRShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"DuckShootRight";
						else if (StateRShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpRight";
						else if (StateRShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"DuckShootLeft";
						else if (StateRShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"RunShootingLeftUp";
					}
					else if ((StateRShoot & PlayerState_OnShoot) != PlayerState_OnShoot && mReloading)
					{
						if (StateRShoot == PlayerState_None)
							playAnimationName = L"ShootBoilRight";
						else if (StateRShoot == PlayerState_Input_Right)
							playAnimationName = L"RunShootingRight";
						else if (StateRShoot == PlayerState_Input_Left)
							playAnimationName = L"RunShootingLeft";
						else if (StateRShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootBoilUpRight";
						else if (StateRShoot == PlayerState_Input_Down)
							playAnimationName = L"DuckShootBoilRight";
						else if (StateRShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"DuckShootBoilRight";
						else if (StateRShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpRight";
						else if (StateRShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"DuckShootBoilLeft";
						else if (StateRShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpLeft";
					}

				}
				//����, �뽬, ����, Ex, ����, �� �ƴѻ���
				else if ((StateR & PlayerState_Input_Down) == PlayerState_Input_Down)
					playAnimationName = L"DuckIdleRight";
				else if (StateR == PlayerState_None)
					playAnimationName = L"IdleRight";
				else if (StateR == PlayerState_Input_Right)
					playAnimationName = L"RunRight";
				else if (StateR == PlayerState_Input_Left)
					playAnimationName = L"RunLeft";
				else if (StateR == PlayerState_Input_Up)
					playAnimationName = L"ShootBoilUpRight";
				else if (StateR == PlayerState_Input_Right + PlayerState_Input_Up)
					playAnimationName = L"RunRight";
				else if (StateR == PlayerState_Input_Left + PlayerState_Input_Up)
					playAnimationName = L"RunLeft";

			}
		}
		else
		{
			int StateL = mCurState;
			if ((StateL & PlayerState_OnHit) == PlayerState_OnHit)
			{
				if ((StateL & PlayerState_OnJump) == PlayerState_OnJump)
					playAnimationName = L"HitAirLeft";
				else
					playAnimationName = L"HitLeft";
			}
			//else if ((StateLookRight & PlayerState_OnEX) == PlayerState_OnEX)
			//	playAnimationName = L"JumpRight";
			else if ((StateL & PlayerState_OnDash) == PlayerState_OnDash)
			{
				if ((StateL & PlayerState_OnJump) == PlayerState_OnJump)
					playAnimationName = L"DashAirLeft";
				else
					playAnimationName = L"DashLeft";
			}
			else if ((StateL & PlayerState_OnJump) == PlayerState_OnJump)
				playAnimationName = L"JumpLeft";
			
			

			else if ((StateL & PlayerState_Input_C) == PlayerState_Input_C)
			{
				int StateLAim = StateL - PlayerState_Input_C;
				if (StateLAim == PlayerState_None)
					playAnimationName = L"IdleLeft";
				else if (StateLAim == PlayerState_Input_Right)
					playAnimationName = L"ShootBoilRight";
				else if (StateLAim == PlayerState_Input_Left)
					playAnimationName = L"ShootBoilLeft";
				else if (StateLAim == PlayerState_Input_Up)
					playAnimationName = L"ShootBoilUpLeft";
				else if (StateLAim == PlayerState_Input_Down)
					playAnimationName = L"ShootBoilDownLeft";
				else if (StateLAim == PlayerState_Input_Right + PlayerState_Input_Down)
					playAnimationName = L"ShootBoilDiagonalRightDown";
				else if (StateLAim == PlayerState_Input_Right + PlayerState_Input_Up)
					playAnimationName = L"ShootBoilDiagonalRightUp";
				else if (StateLAim == PlayerState_Input_Left + PlayerState_Input_Down)
					playAnimationName = L"ShootBoilDiagonalLeftDown";
				else if (StateLAim == PlayerState_Input_Left + PlayerState_Input_Up)
					playAnimationName = L"ShootBoilDiagonalLeftUp";
				else if ((StateLAim & PlayerState_Input_X) == PlayerState_Input_X)
				{
					int StateLAimShoot = StateLAim - PlayerState_Input_X;
					//������ �ڵ����� ���ε� �ִϸ��̼� play
					if ((StateLAimShoot & PlayerState_OnShoot) != PlayerState_OnShoot && !mReloading)
					{
						if (StateLAimShoot == PlayerState_None)
							playAnimationName = L"ShootLeft";
						else if (StateLAimShoot == PlayerState_Input_Right)
							playAnimationName = L"ShootRight";
						else if (StateLAimShoot == PlayerState_Input_Left)
							playAnimationName = L"ShootLeft";
						else if (StateLAimShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootUpLeft";
						else if (StateLAimShoot == PlayerState_Input_Down)
							playAnimationName = L"ShootDownLeft";
						else if (StateLAimShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"ShootDiagonalRightDown";
						else if (StateLAimShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"ShootDiagonalRightUp";
						else if (StateLAimShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"ShootDiagonalLeftDown";
						else if (StateLAimShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"ShootDiagonalLeftUp";
					}

					else if ((StateLAimShoot & PlayerState_OnShoot) != PlayerState_OnShoot && mReloading)
					{
						if (StateLAimShoot == PlayerState_None)
							playAnimationName = L"ShootBoilLeft";
						else if (StateLAimShoot == PlayerState_Input_Right)
							playAnimationName = L"ShootBoilRight";
						else if (StateLAimShoot == PlayerState_Input_Left)
							playAnimationName = L"ShootBoilLeft";
						else if (StateLAimShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootBoilUpLeft";
						else if (StateLAimShoot == PlayerState_Input_Down)
							playAnimationName = L"ShootBoilDownLeft";
						else if (StateLAimShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"ShootBoilDiagonalRightDown";
						else if (StateLAimShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"ShootBoilDiagonalRightUp";
						else if (StateLAimShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"ShootBoilDiagonalLeftDown";
						else if (StateLAimShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"ShootBoilDiagonalLeftUp";
					}
				}

			}

			else
			{
				if ((StateL & PlayerState_Input_X) == PlayerState_Input_X)
				{
					int StateLShoot = StateL - PlayerState_Input_X;
					//������ �ڵ����� ���ε� �ִϸ��̼� play
					if ((StateLShoot & PlayerState_OnShoot) != PlayerState_OnShoot && !mReloading)
					{
						if (StateLShoot == PlayerState_None)
							playAnimationName = L"ShootLeft";
						else if (StateLShoot == PlayerState_Input_Right)
							playAnimationName = L"RunShootingRight";
						else if (StateLShoot == PlayerState_Input_Left)
							playAnimationName = L"RunShootingLeft";
						else if (StateLShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootUpLeft";
						else if (StateLShoot == PlayerState_Input_Down)
							playAnimationName = L"DuckShootLeft";
						else if (StateLShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"DuckShootRight";
						else if (StateLShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpRight";
						else if (StateLShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"DuckShootLeft";
						else if (StateLShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpLeft";
					}
					else if ((StateLShoot & PlayerState_OnShoot) != PlayerState_OnShoot && mReloading)
					{
						if (StateLShoot == PlayerState_None)
							playAnimationName = L"ShootBoilLeft";
						else if (StateLShoot == PlayerState_Input_Right)
							playAnimationName = L"RunShootingRight";
						else if (StateLShoot == PlayerState_Input_Left)
							playAnimationName = L"RunShootingLeft";
						else if (StateLShoot == PlayerState_Input_Up)
							playAnimationName = L"ShootBoilUpLeft";
						else if (StateLShoot == PlayerState_Input_Down)
							playAnimationName = L"DuckShootBoilLeft";
						else if (StateLShoot == PlayerState_Input_Right + PlayerState_Input_Down)
							playAnimationName = L"DuckShootBoilRight";
						else if (StateLShoot == PlayerState_Input_Right + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpRight";
						else if (StateLShoot == PlayerState_Input_Left + PlayerState_Input_Down)
							playAnimationName = L"DuckShootBoilLeft";
						else if (StateLShoot == PlayerState_Input_Left + PlayerState_Input_Up)
							playAnimationName = L"RunShootingUpLeft";
					}

				}
				//����, �뽬, ����, Ex, ����, �� �ƴѻ���
				else if ((StateL & PlayerState_Input_Down) == PlayerState_Input_Down)
					playAnimationName = L"DuckIdleLeft";
				else if (StateL == PlayerState_None)
					playAnimationName = L"IdleLeft";
				else if (StateL == PlayerState_Input_Right)
					playAnimationName = L"RunRight";
				else if (StateL == PlayerState_Input_Left)
					playAnimationName = L"RunLeft";
				else if (StateL == PlayerState_Input_Up)
					playAnimationName = L"ShootBoilUpLeft";
				else if (StateL == PlayerState_Input_Right + PlayerState_Input_Up)
					playAnimationName = L"RunRight";
				else if (StateL == PlayerState_Input_Left + PlayerState_Input_Up)
					playAnimationName = L"RunLeft";
			}
		}
		if (playAnimationName != L"" and
			mAnimator->GetPlayAnimation() != mAnimator->FindAnimation(playAnimationName))
			mAnimator->Play(playAnimationName, true);
	}

	void Player::Shoot()
	{
		if (	!mReloading
			&&	(mCurState & PlayerState_OnHit) != PlayerState_OnHit
			&&	(mCurState & PlayerState_OnEX) != PlayerState_OnEX
			&&	(mCurState & PlayerState_OnDash) != PlayerState_OnDash
			&&	(mCurState & PlayerState_OnUlt) != PlayerState_OnUlt
			)
		{
			Bullet* bullet = nullptr;

			if (mCurGunType == eGunType::PeaShooter)
				bullet = new PeaShooter(mGunDir);

			SetBulletStartPos(bullet);

			Scene* curScene = SceneManager::GetCurScene();
			curScene->AddGameObject(bullet, eColliderLayer::Player_Projecttile);
			mCurState |= PlayerState_OnShoot;
			mReloading = true;
		}
	}

	void Player::Move()
	{
		if (((mCurState & PlayerState_Input_Left) == PlayerState_Input_Left
			|| (mCurState & PlayerState_Input_Right) == PlayerState_Input_Right)
			&& (mCurState & PlayerState_OnHit) != PlayerState_OnHit
			&& (mCurState & PlayerState_OnEX) != PlayerState_OnEX
			&& (mCurState & PlayerState_OnDash) != PlayerState_OnDash
			&& (mCurState & PlayerState_OnUlt) != PlayerState_OnUlt
			&& (mCurState & PlayerState_Input_C) != PlayerState_Input_C
			&& (mCurState & PlayerState_Input_Down) != PlayerState_Input_Down
			)
		{
			Vector2 playerVec = {};
			if ((mCurState & PlayerState_LookRight) == PlayerState_LookRight)
				playerVec = Vector2::Right;
			else
				playerVec = Vector2::Left;
			Vector2 pos = GetPos();
			pos += playerVec * mSpeed * Time::DeltaTime();
			SetPos(pos);
			mCurState &= ~PlayerState_OnShoot;
		}
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

	Vector2 Player::SetBulletStartPos(Bullet* bullet)
	{
		Vector2 bulletStartPos = {};
		Vector2 addPos = {};
		bulletStartPos = { GetPos().x ,
					GetPos().y - GetScale().y / 2 };

		addPos = { GetScale().x / 2, GetScale().y / 2 };
		addPos = addPos * mGunDir;
		if (mGunDir.isDown() or mGunDir.isUp())
		{
			if ((mCurState & PlayerState_LookRight) == PlayerState_LookRight)
			{
				addPos.x -= 10;
				if (mShootPoint == 1)
					addPos.x += 10;
				else if (mShootPoint == 2)
					addPos.x += 20;
			}
			else
			{
				addPos.x += 10;
				if (mShootPoint == 1)
					addPos.x -= 10;
				else if (mShootPoint == 2)
					addPos.x -= 20;
			}
		}
		else
		{
			if (mShootPoint == 1)
				addPos.y -= 10;
			else if (mShootPoint == 2)
				addPos.y -= 20;
		}
		bulletStartPos += addPos;
		bullet->SetPos(bulletStartPos);
		if (++mShootPoint > 3)
			mShootPoint = 0;
		return bulletStartPos;
	}


}