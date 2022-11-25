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
#include "yaRigidbody.h"
#include "yaParryEffect.h"
#include "yaSpecialAttackEffect.h"
#include "yaDashEffect.h"
#include "yaOnHitEffect.h"

#define STATE_HAVE(STATE) (mCurState & STATE) == STATE
namespace ya 
{
	float ShootAnimTime = 0.1f;
	float DashTime = 0.3f;
	Vector2 Gravity = { 0, 5000 };
	Vector2 playerScaleBasic = { 90.0f, 120.0f };
	Vector2 playerScaleDuck = { 90.0f, 60.0f };

	Player::Player()
		:mSpeed(500.0f)
		, mGunDir(Vector2::Right)
		, mCurState(PlayerState_LookRight)
		, mShooterCoolTime(PeaShooter::GetCoolTime())
		, mShooterCoolTimeChecker(0.0f)
		, mCurGunType(eGunType::PeaShooter)
		, mShootPoint(0)
		, mReloading(false)
		, mShootAnimationTimeChecker(0.0f)
		, mFalling(true)
		, mCanDash(true)
		, mCanEX(true)
		, mHP(3)
	{
		SetName(L"Player");
		SetPos({ 400.0f, 700.0f });
		SetScale({ 90.0f, 120.0f });
		AddComponent(new Collider());
		mRigidbody = new Rigidbody();
		AddComponent(mRigidbody);


		mAnimator = new Animator();
		AddComponent(mAnimator);
		{
			mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_00", 5, 0.1f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Cuphead\\Idle\\cuphead_idle_00", 5, 0.1f, false, true, { 0, 0 }, true, true);

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
			mAnimator->CreateAnimation(L"ShootBoilDiagonalRightUp", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_boil_00", 3, 0.1f, false, false, { 10, 0 }, true, true);
			mAnimator->CreateAnimation(L"ShootBoilDiagonalLeftUp", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Up\\cuphead_shoot_diagonal_up_boil_00", 3, 0.1f, false, true, { -10, 0 }, true, true);

			mAnimator->CreateAnimation(L"ShootDiagonalRightDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"ShootDiagonalLeftDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_down_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"ShootBoilDiagonalRightDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_Down_boil_00", 3, 0.1f, false, false, { 10, 0 }, true, true);
			mAnimator->CreateAnimation(L"ShootBoilDiagonalLeftDown", L"..\\Resources\\Image\\Cuphead\\Shoot\\Diagonal Down\\cuphead_shoot_diagonal_Down_boil_00", 3, 0.1f, false, true, { -10, 0 }, true, true);

			mAnimator->CreateAnimation(L"DuckRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_00", 9, 0.05f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DuckLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_00", 9, 0.05f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"DuckIdleRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_idle_00", 6, 0.1f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DuckIdleLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Idle\\cuphead_duck_idle_00", 6, 0.1f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"DuckShootRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_00", 4, ShootAnimTime, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DuckShootLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_00", 4, ShootAnimTime, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DuckShootBoilRight", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_boil_00", 4, 0.1f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DuckShootBoilLeft", L"..\\Resources\\Image\\Cuphead\\Duck\\Shoot\\cuphead_duck_shoot_boil_00", 4, 0.1f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"JumpRight", L"..\\Resources\\Image\\Cuphead\\Jump\\Cuphead\\cuphead_jump_00", 9, 0.02f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"JumpLeft", L"..\\Resources\\Image\\Cuphead\\Jump\\Cuphead\\cuphead_jump_00", 9, 0.02f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"DashRight", L"..\\Resources\\Image\\Cuphead\\Dash\\Ground\\cuphead_dash_00", 9, 0.03f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DashLeft", L"..\\Resources\\Image\\Cuphead\\Dash\\Ground\\cuphead_dash_00", 9, 0.03f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"DashAirRight", L"..\\Resources\\Image\\Cuphead\\Dash\\Air\\cuphead_dash_air_00", 9, 0.05f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"DashAirLeft", L"..\\Resources\\Image\\Cuphead\\Dash\\Air\\cuphead_dash_air_00", 9, 0.05f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"HitRight", L"..\\Resources\\Image\\Cuphead\\HIt\\Ground\\cuphead_hit_00", 7, 0.05f, false, false, { -30, 30 }, true, true);
			mAnimator->CreateAnimation(L"HitLeft", L"..\\Resources\\Image\\Cuphead\\HIt\\Ground\\cuphead_hit_00", 7, 0.05f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"HitAirRight", L"..\\Resources\\Image\\Cuphead\\HIt\\Air\\cuphead_hit_air_00", 7, 0.05f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"HitAirLeft", L"..\\Resources\\Image\\Cuphead\\Hit\\Air\\cuphead_hit_air_00", 7, 0.05f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"ParryRight", L"..\\Resources\\Image\\Cuphead\\Parry\\Hand\\cuphead_parry_00", 9, 0.03f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"ParryLeft", L"..\\Resources\\Image\\Cuphead\\Parry\\Hand\\cuphead_parry_00", 9, 0.03f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"EXRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Straight\\Ground\\cuphead_ex_straight_00", 14, 0.03f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Straight\\Ground\\cuphead_ex_straight_00", 14, 0.03f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Straight\\Air\\cuphead_ex_straight_air_00", 7, 0.06f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Straight\\Air\\cuphead_ex_straight_air_00", 7, 0.06f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXUpRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Up\\Ground\\cuphead_ex_up_00", 14, 0.03f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXUpLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Up\\Ground\\cuphead_ex_up_00", 14, 0.03f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirUpRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Up\\Air\\cuphead_ex_up_air_00", 7, 0.06f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirUpLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Up\\Air\\cuphead_ex_up_air_00", 7, 0.06f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXDownRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Down\\Ground\\cuphead_ex_down_00", 14, 0.04f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXDownLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Down\\Ground\\cuphead_ex_down_00", 14, 0.04f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirDownRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Down\\Air\\cuphead_ex_down_air_00", 7, 0.06f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirDownLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Down\\Air\\cuphead_ex_down_air_00", 7, 0.06f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXDiagonalUpRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Up\\Ground\\cuphead_ex_diagonal_up_00", 14, 0.03f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXDiagonalUpLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Up\\Ground\\cuphead_ex_diagonal_up_00", 14, 0.03f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirDiagonalUpRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Up\\Air\\cuphead_ex_diagonal_up_air_00", 7, 0.06f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirDiagonalUpLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Up\\Air\\cuphead_ex_diagonal_up_air_00", 7, 0.06f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXDiagonalDownRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Down\\Ground\\cuphead_ex_diagonal_down_00", 14, 0.03f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXDiagonalDownLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Down\\Ground\\cuphead_ex_diagonal_down_00", 14, 0.03f, false, true, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirDiagonalDownRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Down\\Air\\cuphead_ex_diagonal_down_air_00", 7, 0.06f, false, false, { 0, 0 }, true, true);
			mAnimator->CreateAnimation(L"EXAirDiagonalDownLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\Diagonal Down\\Air\\cuphead_ex_diagonal_down_air_00", 7, 0.06f, false, true, { 0, 0 }, true, true);

			mAnimator->CreateAnimation(L"Intro", L"..\\Resources\\Image\\Cuphead\\Intros\\Regular\\cuphead_intro_a_00", 39, 0.035f, false, false, { 0 ,0 }, true, true);


			mAnimator->GetCompleteEvent(L"EXRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXUpRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXUpLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirUpRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirUpLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXDownRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXDownLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirDownRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirDownLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXDiagonalUpRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXDiagonalUpLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirDiagonalUpRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirDiagonalUpLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXDiagonalDownRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXDiagonalDownLeft") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirDiagonalDownRight") = std::bind(&Player::EXCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"EXAirDiagonalDownLeft") = std::bind(&Player::EXCompleteEvent, this);

			mAnimator->GetCompleteEvent(L"HitRight") = std::bind(&Player::OnHitCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"HitLeft") = std::bind(&Player::OnHitCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"HitAirRight") = std::bind(&Player::OnHitCompleteEvent, this);
			mAnimator->GetCompleteEvent(L"HitAirLeft") = std::bind(&Player::OnHitCompleteEvent, this);


		}
		mAnimator->SetBaseAnimation(L"IdleRight");
		mAnimator->Play(L"Intro", false);
		//Initialize시 이미지 로드
		{
			PeaShooter({ 1,0 });
			ParryEffect();
			DashEffect();
			SpecialAttackEffect({ 1,0 });
			OnHitEffect();
		}
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		mPrevPos = GetPos();
		PlayerKeyInput();
		if (!(mAnimator->GetPlayAnimation()->GetName() == L"Intro"))
		{
			SetAnimation();
			Shoot();
			Move();
			Duck();
			Dash();
			Jump();
			EX();
			Parry();
			OnHit();
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

	void Player::OnCollisonEnter(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{		
			//패링 성공
			if (other->GetOwner()->isParryable()
				&& STATE_HAVE(PlayerState_OnParry))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y = -1500.0f;
				mRigidbody->SetVelocity(velocity);

				mCurState &= ~PlayerState_OnParry;
				other->GetOwner()->SetParried(true);
				if (mSpecialPoint < 5)
				{
					mSpecialPoint += 1;
				}
				ParryEffect* parryEffect = new ParryEffect();

				Vector2 effectPos;
				if (other->GetPos().x > my->GetPos().x)
					effectPos.x = my->GetPos().x + (my->GetScale().x / 2);
				else
					effectPos.x = my->GetPos().x - (my->GetScale().x / 2);

				//상수 k = my->getpos().y - (my->getpos().x * 기울기)
				float gradient = (other->GetPos().y - my->GetPos().y) / (other->GetPos().x - my->GetPos().x);
				float k = my->GetPos().y - (my->GetPos().x * gradient);
				effectPos.y = gradient * effectPos.x + k;
				if( other->GetPos().y > my->GetPos().y)
				{
					if (effectPos.y < my->GetPos().y - my->GetScale().y / 2)
					{
						effectPos.y = my->GetPos().y + my->GetScale().y / 2;
						effectPos.x = (effectPos.y - k) / gradient;
					}
				}
				else
				{
					if (effectPos.y > my->GetPos().y + my->GetScale().y / 2)
					{
						effectPos.y = my->GetPos().y + my->GetScale().y / 2;
						effectPos.x = (effectPos.y - k) / gradient;
					}
				}
				parryEffect->SetPos(effectPos);
				Scene* curscene = SceneManager::GetCurScene();
				curscene->AddGameObject(parryEffect, eColliderLayer::Effect);
				Time::SlowDown(true);
				mParrySlow = true;
			}

			//몬스터와 부딪힘
			else if (mInvincibile == false
				&& other->isHitBox() 
				&& !(STATE_HAVE(PlayerState_OnHit))
				&& ((other->GetOwner()->GetLayer() == eColliderLayer::Monster
					|| other->GetOwner()->GetLayer() == eColliderLayer::Monster_Projecttile))
				)
			{
				if(mHP > 0)
				{
					mHP -= 1;
					mCurState |= PlayerState_OnHit;
					mRigidbody->SetGravity(Gravity);
					mRigidbody->SetGround(false);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y = -1000.0f;
					if (STATE_HAVE(PlayerState_LookRight))
						velocity.x = -100.0f;
					else
						velocity.x = 100.0f;
					mRigidbody->SetVelocity(velocity);

					mInvincibile = true;
					mCurState &= ~PlayerState_OnDash;
					mDashTimeChecker = 0;
					OnHitEffect* onhitEffect = new OnHitEffect();
					onhitEffect->SetPos(GetPos());
					Scene* curscene = SceneManager::GetCurScene();
					curscene->AddGameObject(onhitEffect, eColliderLayer::Effect);
				}
			}
		}
	}

	void Player::OnCollisonStay(Collider* other, Collider* my)
	{
		Scene* curscene = SceneManager::GetCurScene();
		if (!(curscene->isIntro()))
		{
			//패링 성공
			if (other->GetOwner()->isParryable()
				&& STATE_HAVE(PlayerState_OnParry))
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.y = -1500.0f;
				mRigidbody->SetVelocity(velocity);

				mCurState &= ~PlayerState_OnParry;
				other->GetOwner()->SetParried(true);
				if (mSpecialPoint < 5)
				{
					mSpecialPoint += 1;
				}
				ParryEffect* parryEffect = new ParryEffect();

				Vector2 effectPos;
				if (other->GetPos().x > my->GetPos().x)
					effectPos.x = my->GetPos().x + (my->GetScale().x / 2);
				else
					effectPos.x = my->GetPos().x - (my->GetScale().x / 2);

				//상수 k = my->getpos().y - (my->getpos().x * 기울기)
				float gradient = (other->GetPos().y - my->GetPos().y) / (other->GetPos().x - my->GetPos().x);
				float k = my->GetPos().y - (my->GetPos().x * gradient);
				effectPos.y = gradient * effectPos.x + k;
				if (other->GetPos().y > my->GetPos().y)
				{
					if (effectPos.y < my->GetPos().y - my->GetScale().y / 2)
					{
						effectPos.y = my->GetPos().y + my->GetScale().y / 2;
						effectPos.x = (effectPos.y - k) / gradient;
					}
				}
				else
				{
					if (effectPos.y > my->GetPos().y + my->GetScale().y / 2)
					{
						effectPos.y = my->GetPos().y + my->GetScale().y / 2;
						effectPos.x = (effectPos.y - k) / gradient;
					}
				}
				parryEffect->SetPos(effectPos);
				Scene* curscene = SceneManager::GetCurScene();
				curscene->AddGameObject(parryEffect, eColliderLayer::Effect);
				Time::SlowDown(true);
				mParrySlow = true;
			}

			//몬스터와 부딪힘
			else if (mInvincibile == false
				&& other->isHitBox()
				&& !(STATE_HAVE(PlayerState_OnHit))
				&& ((other->GetOwner()->GetLayer() == eColliderLayer::Monster
					|| other->GetOwner()->GetLayer() == eColliderLayer::Monster_Projecttile))
				)
			{
				if (mHP > 0)
				{
					mHP -= 1;
					mCurState |= PlayerState_OnHit;
					mRigidbody->SetGravity(Gravity);
					mRigidbody->SetGround(false);
					Vector2 velocity = mRigidbody->GetVelocity();
					velocity.y = -1000.0f;
					if (STATE_HAVE(PlayerState_LookRight))
						velocity.x = -100.0f;
					else
						velocity.x = 100.0f;
					mRigidbody->SetVelocity(velocity);

					mInvincibile = true;
					mCurState &= ~PlayerState_OnDash;
					mDashTimeChecker = 0;
					OnHitEffect* onhitEffect = new OnHitEffect();
					onhitEffect->SetPos(GetPos());
					Scene* curscene = SceneManager::GetCurScene();
					curscene->AddGameObject(onhitEffect, eColliderLayer::Effect);
				}
			}
		}
	}

	void Player::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Player::PlayerKeyInput()
	{
		if (!(STATE_HAVE(PlayerState_OnHit)))
		{
			// 키 눌러진 상태
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
				if (!(STATE_HAVE(PlayerState_OnDash)))
					mCurState &= ~PlayerState_LookRight;
			}
			if (KEY_PRESSED(eKeyCode::RIGHT))
			{
				mCurState |= PlayerState_Input_Right;

				if (!(STATE_HAVE(PlayerState_OnDash)))
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
		}

		// 키 누르는 순간
		// 중복키

		//키 떼는 순간
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

		if (KEY_DOWN(eKeyCode::R))
		{
			SetPos({ 400,700 });
			mSpecialPoint = 5;
			mHP = 5;
			//Jump()
		}
	}

	void Player::SetAnimation()
	{
		// 끝나면 자동으로 다음 애니메이션 나오는 것들 -> shoot류, Duckstart류.
		std::wstring playAnimationName = L"";
		bool loop = true;
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
			else if (STATE_HAVE(PlayerState_OnEX))
			{
				return;
			}
			else if ((StateR & PlayerState_OnDash) == PlayerState_OnDash)
			{
				if ((StateR & PlayerState_OnJump) == PlayerState_OnJump)
					playAnimationName = L"DashAirRight";
				else
					playAnimationName = L"DashRight";
			}
			else if (STATE_HAVE(PlayerState_OnParry))
			{
				playAnimationName = L"ParryRight";
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
					//끝나면 자동으로 리로딩 애니메이션 play
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
				//점프, 대쉬, 온힛, Ex, 조준, 슛 아닌상태
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

				else
					playAnimationName = L"RunRight";
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
			else if (STATE_HAVE(PlayerState_OnEX))
			{
				return;
			}

			else if ((StateL & PlayerState_OnDash) == PlayerState_OnDash)
			{
				if ((StateL & PlayerState_OnJump) == PlayerState_OnJump)
					playAnimationName = L"DashAirLeft";
				else
					playAnimationName = L"DashLeft";
			}
			else if (STATE_HAVE(PlayerState_OnParry))
			{
				playAnimationName = L"ParryLeft";
				loop = false;
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
					//끝나면 자동으로 리로딩 애니메이션 play
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
					//끝나면 자동으로 리로딩 애니메이션 play
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
				//점프, 대쉬, 온힛, Ex, 조준, 슛 아닌상태
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

				else
					playAnimationName = L"RunLeft";
			}
		}


		if (playAnimationName != L""
			&& mAnimator->GetPlayAnimation() != mAnimator->FindAnimation(playAnimationName)
			)
		{
			mAnimator->Play(playAnimationName, loop);
		}
	}

	void Player::Shoot()
	{
		if (	!mReloading
			&&	(mCurState & PlayerState_OnHit) != PlayerState_OnHit
			&&	(mCurState & PlayerState_OnEX) != PlayerState_OnEX
			&&	(mCurState & PlayerState_OnDash) != PlayerState_OnDash
			&&	(mCurState & PlayerState_OnUlt) != PlayerState_OnUlt
			&&	!(STATE_HAVE(PlayerState_OnShoot))
			&&	STATE_HAVE(PlayerState_Input_X)
			)
		{
			Bullet* bullet = nullptr;
			
			SetGunDir();
			if (mCurGunType == eGunType::PeaShooter)
				bullet = new PeaShooter(mGunDir);
			SetBulletStartPos(bullet);
			bullet->Initialize();
			bullet->SetOwner(this);


			Scene* curScene = SceneManager::GetCurScene();
			curScene->AddGameObject(bullet, eColliderLayer::Player_Projecttile);
			mCurState |= PlayerState_OnShoot;
			mReloading = true;
		}

		if (KEY_UP(eKeyCode::X))
		{
			mCurState &= ~PlayerState_OnShoot;
		}

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
			if (mShootAnimationTimeChecker >= mShooterCoolTime)
			{
				mCurState &= ~PlayerState_OnShoot;
				mShootAnimationTimeChecker = 0.0f;
			}
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
			&& !(GetScale() == playerScaleDuck)
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

	void Player::Duck()
	{
		if (!(STATE_HAVE(PlayerState_OnHit))
			&& !(STATE_HAVE(PlayerState_OnDash))
			&& !(STATE_HAVE(PlayerState_OnJump))
			&& !(STATE_HAVE(PlayerState_OnUlt))
			&& !(STATE_HAVE(PlayerState_Input_C))
			&& !(STATE_HAVE(PlayerState_OnEX))
			&& STATE_HAVE(PlayerState_Input_Down)
			)
		{
			GetComponent<Collider>()->SetScale({ playerScaleDuck });
			SetScale(playerScaleDuck);
		}
		else
		{
			if (GetScale() == playerScaleDuck)
			{
				GetComponent<Collider>()->SetScale({ playerScaleBasic });
				SetScale(playerScaleBasic);
				mCurState &= ~PlayerState_OnShoot;
			}
		}
	}

	void Player::Dash()
	{
		if (!(STATE_HAVE(PlayerState_OnHit))
			&& !(STATE_HAVE(PlayerState_OnDash))
			&& !(STATE_HAVE(PlayerState_OnUlt))
			&& !(STATE_HAVE(PlayerState_OnEX))
			&& !(STATE_HAVE(PlayerState_Input_C))
			&& !(STATE_HAVE(PlayerState_Input_Down))
			&& mCanDash
			&& KEY_DOWN(eKeyCode::LSHIFT)
			)
		{
			mCurState |= PlayerState_OnDash;
			mCurState &= ~PlayerState_OnParry;
			if (STATE_HAVE(PlayerState_OnJump))
				mCanDash = false;
			dynamic_cast<Rigidbody*>(GetComponent(eComponentType::Rigidbody))->SetVelocity({ 0,0 });
			dynamic_cast<Rigidbody*>(GetComponent(eComponentType::Rigidbody))->SetGravity({ 0,0 });
			
			
			DashEffect* dashEffect;
			bool isLeft = true;
			if(STATE_HAVE(PlayerState_LookRight))
				dashEffect = new DashEffect();
			else
				dashEffect = new DashEffect(isLeft);

			dashEffect->SetPos(GetPos());
			Scene* curscene = SceneManager::GetCurScene();
			curscene->AddGameObject(dashEffect, eColliderLayer::Effect);

		}
		if (STATE_HAVE(PlayerState_OnDash))
		{
			mDashTimeChecker += Time::DeltaTime();
			if (mDashTimeChecker >= DashTime)
			{
				mCurState &= ~PlayerState_OnDash;

				dynamic_cast<Rigidbody*>(GetComponent(eComponentType::Rigidbody))->SetGravity({ 0,5000 });
				mDashTimeChecker = 0;
			}
			Vector2 pos = GetPos();
			if(STATE_HAVE(PlayerState_LookRight))
				pos.x += 1300 * Time::DeltaTime();
			else
				pos.x -= 1300 * Time::DeltaTime();
			SetPos(pos);
		}
	}

	void Player::Jump()
	{
		if (!(STATE_HAVE(PlayerState_OnHit))
			&& !(STATE_HAVE(PlayerState_OnDash))
			&& !(STATE_HAVE(PlayerState_OnUlt))
			&& !(STATE_HAVE(PlayerState_Input_C))
			&& !(STATE_HAVE(PlayerState_OnEX))
			&& !(STATE_HAVE(PlayerState_OnJump))
			&& KEY_DOWN(eKeyCode::Z)
			)
		{
			mCurState |= PlayerState_OnJump;
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y = -1850.0f;
			mRigidbody->SetVelocity(velocity);

			mRigidbody->SetGround(false);
		}
		if (STATE_HAVE(PlayerState_OnJump))
		{
			mJumpTimeChecker += Time::DeltaTime();
			if (mRigidbody->isGround()) 
			{
				mCurState &= ~PlayerState_OnJump;
				mJumpTimeChecker = 0;
				mCanDash = true;
				mCanEX = true;
			}
		}
	}

	void Player::EX()
	{
		if (!(STATE_HAVE(PlayerState_OnHit))
			&& !(STATE_HAVE(PlayerState_OnDash))
			&& !(STATE_HAVE(PlayerState_OnUlt))
			&& !(STATE_HAVE(PlayerState_OnEX))
			&& mCanEX
			&& KEY_DOWN(eKeyCode::V)
			&& mSpecialPoint > 0
			)
		{
			mSpecialPoint -= 1;
			mCurState |= PlayerState_OnEX;
			//애니메이션
			{
				bool loop = false;
				std::wstring playAnimationName = L"";
				if ((mCurState & PlayerState_LookRight) == PlayerState_LookRight)
				{

					if (STATE_HAVE(PlayerState_OnJump))
					{
						playAnimationName = L"EXAirRight";
						if ((STATE_HAVE(PlayerState_Input_Right)) && (STATE_HAVE(PlayerState_Input_Down)))
							playAnimationName = L"EXAirDiagonalDownRight";
						else if ((STATE_HAVE(PlayerState_Input_Right)) && (STATE_HAVE(PlayerState_Input_Up)))
							playAnimationName = L"EXAirDiagonalUpRight";
						else if ((STATE_HAVE(PlayerState_Input_Left)) && (STATE_HAVE(PlayerState_Input_Down)))
							playAnimationName = L"EXAirDiagonalDownLeft";
						else if ((STATE_HAVE(PlayerState_Input_Left)) && (STATE_HAVE(PlayerState_Input_Up)))
							playAnimationName = L"EXAirDiagonalUpLeft";
						else if (STATE_HAVE(PlayerState_Input_Right))
							playAnimationName = L"EXAirRight";
						else if (STATE_HAVE(PlayerState_Input_Left))
							playAnimationName = L"EXAirLeft";
						else if (STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXAirUpRight";
						else if (STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXAirDownRight";


					}
					else
					{
						playAnimationName = L"EXRight";
						if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXDiagonalDownRight";
						else if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXDiagonalUpRight";
						else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXDiagonalDownLeft";
						else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXDiagonalUpLeft";
						else if (STATE_HAVE(PlayerState_Input_Right))
							playAnimationName = L"EXRight";
						else if (STATE_HAVE(PlayerState_Input_Left))
							playAnimationName = L"EXLeft";
						else if (STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXUpRight";
						else if (STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXDownRight";

					}
				}
				else
				{
					if (STATE_HAVE(PlayerState_OnJump))
					{
						playAnimationName = L"EXAirLeft";
						if ((STATE_HAVE(PlayerState_Input_Right)) && (STATE_HAVE(PlayerState_Input_Down)))
							playAnimationName = L"EXAirDiagonalDownRight";
						else if ((STATE_HAVE(PlayerState_Input_Right)) && (STATE_HAVE(PlayerState_Input_Up)))
							playAnimationName = L"EXAirDiagonalUpRight";
						else if ((STATE_HAVE(PlayerState_Input_Left)) && (STATE_HAVE(PlayerState_Input_Down)))
							playAnimationName = L"EXAirDiagonalDownLeft";
						else if ((STATE_HAVE(PlayerState_Input_Left)) && (STATE_HAVE(PlayerState_Input_Up)))
							playAnimationName = L"EXAirDiagonalUpLeft";
						else if (STATE_HAVE(PlayerState_Input_Right))
							playAnimationName = L"EXAirRight";
						else if (STATE_HAVE(PlayerState_Input_Left))
							playAnimationName = L"EXAirLeft";
						else if (STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXAirUpLeft";
						else if (STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXAirDownLeft";


					}
					else
					{
						playAnimationName = L"EXLeft";
						if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXDiagonalDownRight";
						else if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXDiagonalUpRight";
						else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXDiagonalDownLeft";
						else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXDiagonalUpLeft";
						else if (STATE_HAVE(PlayerState_Input_Right))
							playAnimationName = L"EXRight";
						else if (STATE_HAVE(PlayerState_Input_Left))
							playAnimationName = L"EXLeft";
						else if (STATE_HAVE(PlayerState_Input_Up))
							playAnimationName = L"EXUpLeft";
						else if (STATE_HAVE(PlayerState_Input_Down))
							playAnimationName = L"EXDownLeft";

					}

				}
				if (playAnimationName != L"" and
					mAnimator->GetPlayAnimation() != mAnimator->FindAnimation(playAnimationName))
					mAnimator->Play(playAnimationName, loop);
			}
			//EXbullet
			{
				Bullet* bullet = nullptr;

				SetGunEXDir();
				if (mCurGunType == eGunType::PeaShooter)
				{
					bool isSpecial = true;
					bullet = new PeaShooter(mGunDir, isSpecial);
				}
				SetEXBulletStartPos(bullet);
				bullet->Initialize();
				bullet->SetOwner(this);



				Scene* curScene = SceneManager::GetCurScene();
				curScene->AddGameObject(bullet, eColliderLayer::Player_Projecttile);
				mReloading = true;
			}
			dynamic_cast<Rigidbody*>(GetComponent(eComponentType::Rigidbody))->SetVelocity({ 0,0 });
			dynamic_cast<Rigidbody*>(GetComponent(eComponentType::Rigidbody))->SetGravity({ 0,0 });

			if (STATE_HAVE(PlayerState_OnJump))
				mCanEX = false;

			SpecialAttackEffect* exEffect = new SpecialAttackEffect(mGunDir);
			exEffect->SetPos(GetPos());
			Scene* curscene = SceneManager::GetCurScene();
			curscene->AddGameObject(exEffect, eColliderLayer::Effect);
		}

		if (mSpecialPoint == 5)
			mSpecialPointFloat = 0;
		if (mSpecialPointFloat > 1)
		{
			if (mSpecialPoint < 5)
				mSpecialPoint += 1;
			mSpecialPointFloat = 0;
		}
	}

	void Player::Parry()
	{
		if (!(STATE_HAVE(PlayerState_OnHit))
			&& !(STATE_HAVE(PlayerState_OnDash))
			&& !(STATE_HAVE(PlayerState_OnUlt))
			&& !(STATE_HAVE(PlayerState_Input_C))
			&& !(STATE_HAVE(PlayerState_OnParry))
			&& STATE_HAVE(PlayerState_OnJump)
			&& mJumpTimeChecker > 0.1
			&& KEY_DOWN(eKeyCode::Z)
			)
		{
			mCurState |= PlayerState_OnParry;
		}
		if (STATE_HAVE(PlayerState_OnParry))
		{
			if (mRigidbody->isGround()) 
			{
				mCurState &= ~PlayerState_OnParry;
			}
		}
		if (mParrySlow)
		{
			mParrySlowTimeChecker += Time::DeltaTime();
			if (mParrySlowTimeChecker > 0.0002f)
			{
				Time::SlowDown(false);
				mParrySlowTimeChecker = 0;
				mParrySlow = false;
			}
		}
	}

	void Player::OnHit()
	{
		
		if (mInvincibile)
		{
			mInvincibileTimeChecker += Time::DeltaTime();
			if (mInvincibileTimeChecker > 2.0f)
			{
				mInvincibile = false;
				mInvincibileTimeChecker = 0;
				mAnimator->SetMatrixToBase();
				mAnimator->GetPlayAnimation()->SetHaveAlpha(true);
			}
			Blink();
		}
	}

	void Player::Blink()
	{
		if (mInvincibile
			&&!(STATE_HAVE(PlayerState_OnHit)))
		{
			if (!mBlinkChecker)
				mBlinkTimeChecker += Time::DeltaTime() * 8;
			else
				mBlinkTimeChecker -= Time::DeltaTime() * 8;
			
			if (mBlinkTimeChecker > 1)
				mBlinkChecker = true;
			else if (mBlinkTimeChecker < 0)
				mBlinkChecker = false;

			mAnimator->SetMatrixToTransparent(mBlinkTimeChecker);
		}
	}

	void Player::EXCompleteEvent()
	{
		mCurState &= ~PlayerState_OnEX;
		dynamic_cast<Rigidbody*>(GetComponent(eComponentType::Rigidbody))->SetGravity(Gravity);
	}

	void Player::OnHitCompleteEvent()
	{
		mCurState &= ~PlayerState_OnHit;
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
		bullet->GetShootEffect()->SetPos(bulletStartPos + addPos/2);
		return bulletStartPos;
	}

	Vector2 Player::SetEXBulletStartPos(Bullet* bullet)
	{
		Vector2 bulletStartPos = {};
		Vector2 addPos = {};
		bulletStartPos = { GetPos().x , GetPos().y - GetScale().y / 2 };

		addPos = { GetScale().x / 2, 0};
		addPos = addPos * mGunDir;
		bulletStartPos += addPos;
		bullet->SetPos(bulletStartPos);
		bullet->GetShootEffect()->SetPos(bulletStartPos + addPos / 2);
		return bulletStartPos;
	}

	void Player::SetGunDir()
	{
		if (STATE_HAVE(PlayerState_LookRight))
			mGunDir = Vector2::Right;
		else
			mGunDir = Vector2::Left;

		if (!(STATE_HAVE(PlayerState_OnJump)))
		{
			if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Up))
				mGunDir = Vector2::RightUp;
			else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Up))
				mGunDir = Vector2::LeftUp;
			else if (STATE_HAVE(PlayerState_Input_Right))
				mGunDir = Vector2::Right;
			else if (STATE_HAVE(PlayerState_Input_Up))
				mGunDir = Vector2::Up;
			else if (STATE_HAVE(PlayerState_Input_Left))
				mGunDir = Vector2::Left;
			if (STATE_HAVE(PlayerState_Input_C))
			{
				if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Down))
					mGunDir = Vector2::RightDown;
				else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Down))
					mGunDir = Vector2::LeftDown;
				else if (STATE_HAVE(PlayerState_Input_Down))
					mGunDir = Vector2::Down;

			}
		}
		else
		{
			if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Up))
				mGunDir = Vector2::RightUp;
			else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Up))
				mGunDir = Vector2::LeftUp;
			else if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Down))
				mGunDir = Vector2::RightDown;
			else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Down))
				mGunDir = Vector2::LeftDown;
			else if (STATE_HAVE(PlayerState_Input_Down))
				mGunDir = Vector2::Down;
			else if (STATE_HAVE(PlayerState_Input_Right))
				mGunDir = Vector2::Right;
			else if (STATE_HAVE(PlayerState_Input_Up))
				mGunDir = Vector2::Up;
			else if (STATE_HAVE(PlayerState_Input_Left))
				mGunDir = Vector2::Left;
		}

	}

	void Player::SetGunEXDir()
	{
		if (STATE_HAVE(PlayerState_LookRight))
			mGunDir = Vector2::Right;
		else
			mGunDir = Vector2::Left;
		if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Up))
			mGunDir = Vector2::RightUp;
		else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Up))
			mGunDir = Vector2::LeftUp;
		else if (STATE_HAVE(PlayerState_Input_Right) && STATE_HAVE(PlayerState_Input_Down))
			mGunDir = Vector2::RightDown;
		else if (STATE_HAVE(PlayerState_Input_Left) && STATE_HAVE(PlayerState_Input_Down))
			mGunDir = Vector2::LeftDown;
		else if (STATE_HAVE(PlayerState_Input_Down))
			mGunDir = Vector2::Down;
		else if (STATE_HAVE(PlayerState_Input_Right))
			mGunDir = Vector2::Right;
		else if (STATE_HAVE(PlayerState_Input_Up))
			mGunDir = Vector2::Up;
		else if (STATE_HAVE(PlayerState_Input_Left))
			mGunDir = Vector2::Left;


	}


}