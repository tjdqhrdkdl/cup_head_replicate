#include "yaWernerWermanPh1.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaPinkSpring.h"	
#include "yaTomatoBomb.h"
#include "yaJunk.h"
#include "yaWernerWermanPh2.h"
#include "yaBossCanRatScene.h"
namespace ya
{
	WernerWermanPh1::WernerWermanPh1()
		: mDashTimeChecker(0)
		, mSpeed(0)
		, mNowAttack(eWernerWermanAttacks::None)
		, mBeforeAttack(eWernerWermanAttacks::None)
		, mbChoiceAttack(false)
		, mbAccelerating(true)
		, mCannonShootTimeChecker(0)
		, mbCannonMode(false)
		, mbCatapultCharge(false)
		, mbCatapultExit(false)
		, mbCatapultIntroFin(false)
		, mbCatapultMode(false)
		, mbCatapultShooting(false)
		, mbDashFin(false)
		, mbDashIng(false)
		, mbIdleGoBack(false)
		, mbIdleMoving(false)
		, mbLookRight(false)
		, mbMouseDown(false)
		, mbEnd(false)
	{
		SetName(L"WernerWermanPh1");
		mHp = 200;
		SetPos({ 1400,800 });
		SetScale({ 250.0f,350.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mCanBackAnimator = new Animator();
		mCanFrontAnimator = new Animator();
		mContentAnimator = new Animator();
		mWheelsAnimator = new Animator();
		AddComponent(mCanBackAnimator);
		AddComponent(mContentAnimator);
		AddComponent(mCanFrontAnimator);
		AddComponent(mWheelsAnimator);

		//CanBack
		mCanBackAnimator->SetLightenAnimation(mCanBackAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Idle\\Back\\can_idle_back_00", 4, 0.08f, false, false, {-35,-293})
			, mCanBackAnimator->CreateAnimation(L"LightenIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Idle\\Back\\can_idle_back_00", 4, 0.08f, false, false, { -35,-293 }));
		mCanBackAnimator->SetLightenAnimation(mCanBackAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Idle\\Back\\can_idle_back_00", 4, 0.08f, false, true, { 35,-293 })
			, mCanBackAnimator->CreateAnimation(L"LightenIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Idle\\Back\\can_idle_back_00", 4, 0.08f, false, true, { 35,-293 }));
		mCanBackAnimator->SetLightenAnimation(mCanBackAnimator->CreateAnimation(L"MoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Move\\Back\\can_move_back_00", 25, 0.04f, false, false, {-30,-258})
			, mCanBackAnimator->CreateAnimation(L"LightenMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Move\\Back\\can_move_back_00", 25, 0.04f, false, false, { -30,-258 }));
		mCanBackAnimator->SetLightenAnimation(mCanBackAnimator->CreateAnimation(L"MoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Move\\Back\\can_move_back_00", 25, 0.04f, false, true, {30,-258 })
			, mCanBackAnimator->CreateAnimation(L"LightenMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Move\\Back\\can_move_back_00", 25, 0.04f, false, true, { 30,-258 }));

		//CanFront
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"IdleDownLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Idle\\Down\\can_idle_down_00", 4, 0.08f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenIdleDownLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Idle\\Down\\can_idle_down_00", 4, 0.08f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"IdleDownRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Idle\\Down\\can_idle_down_00", 4, 0.08f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenIdleDownRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Idle\\Down\\can_idle_down_00", 4, 0.08f, false, true));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"IdleUpLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Idle\\Up\\can_idle_up_00", 4, 0.08f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenIdleUpLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Idle\\Up\\can_idle_up_00", 4, 0.08f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"IdleUpRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Idle\\Up\\can_idle_up_00", 4, 0.08f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenIdleUpRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Idle\\Up\\can_idle_up_00", 4, 0.08f, false, true));

		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"MousePopingLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Stop\\can_stop_00", 4, 0.08f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenPopingLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Stop\\can_stop_00", 4, 0.08f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"MousePopingRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Stop\\can_stop_00", 4, 0.08f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenPopingRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Stop\\can_stop_00", 4, 0.08f, false, true));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"MouseDownigLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Stop\\can_stop_00", 4, 0.08f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenDownigLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Stop\\can_stop_00", 4, 0.08f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"MouseDownigRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Stop\\Reverse\\can_stop_00", 4, 0.08f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenDownigRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Stop\\Reverse\\can_stop_00", 4, 0.08f, false, true));

		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Move\\can_move_00", 25, 0.04f, false, false,{0,-30})
			, mCanFrontAnimator->CreateAnimation(L"LightenCanMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Move\\can_move_00", 25, 0.04f, false, false, { 0,-30 }));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Move\\can_move_00", 25, 0.04f, false, true, { 0,-30 })
			, mCanFrontAnimator->CreateAnimation(L"LightenCanMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Move\\can_move_00", 25, 0.04f, false, true, { 0,-30 }));

		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanDashStartLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Dash\\DashStart\\can_dash_00", 24, 0.04f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenCanDashStartLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Dash\\DashStart\\can_dash_00", 24, 0.04f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanDashStartRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Dash\\DashStart\\can_dash_00", 24, 0.04f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenCanDashStartRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Dash\\DashStart\\can_dash_00", 24, 0.04f, false, true));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanDashLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Dash\\Dash\\can_dash_00", 6, 0.04f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenCanDashLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Dash\\Dash\\can_dash_00", 6, 0.04f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanDashRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Dash\\Dash\\can_dash_00", 6, 0.04f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenCanDashRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Dash\\Dash\\can_dash_00", 6, 0.04f, false, true));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanDashStopLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Dash\\DashStop\\can_dash_00", 48, 0.04f, false, false)
			, mCanFrontAnimator->CreateAnimation(L"LightenCanStopLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Dash\\DashStop\\can_dash_00", 48, 0.04f, false, false));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanDashStopRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Dash\\DashStop\\can_dash_00", 48, 0.04f, false, true)
			, mCanFrontAnimator->CreateAnimation(L"LightenCanStopRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Dash\\DashStop\\can_dash_00", 48, 0.04f, false, true));
		
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanBoomLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Intro\\CanBoom\\mouse_can_explode_trans_00", 14, 0.08f, false, false,{0,110})
			, mCanFrontAnimator->CreateAnimation(L"LightenCanBoomLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Intro\\CanBoom\\mouse_can_explode_trans_00", 14, 0.08f, false, false, { 0,110 }));
		mCanFrontAnimator->SetLightenAnimation(mCanFrontAnimator->CreateAnimation(L"CanBoomRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Intro\\CanBoom\\mouse_can_explode_trans_00", 14, 0.08f, false, true, { 0,110 })
			, mCanFrontAnimator->CreateAnimation(L"LightenCanBoomRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Intro\\CanBoom\\mouse_can_explode_trans_00", 14, 0.08f, false, true, { 0,110 }));

		//CanContent
		mContentAnimator->CreateAnimation(L"MouseIntro", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Intro\\mouse_intro_00", 51, 0.05f, false, false, {-20,-140});
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"MousePopOutLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Pop Out\\mouse_pop_out_00", 21, 0.04f, false, false,{-55,-180})
			, mContentAnimator->CreateAnimation(L"LightenMousePopOutLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Pop Out\\mouse_pop_out_00", 21, 0.04f, false, false, { -55,-180 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"MousePopOutRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Pop Out\\mouse_pop_out_00", 21, 0.04f, false, true, { 55,-180 })
			, mContentAnimator->CreateAnimation(L"LightenMousePopOutRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Pop Out\\mouse_pop_out_00", 21, 0.04f, false, true, { 55,-180 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"MouseShakeFistLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Shake Fist\\mouse_shake_fist_00", 16, 0.04f, false, false, { -65,-195 })
			, mContentAnimator->CreateAnimation(L"LightenMouseShakeFistLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Shake Fist\\mouse_shake_fist_00", 9, 0.04f, false, false, { -65,-195 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"MouseShakeFistRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Shake Fist\\mouse_shake_fist_00", 16, 0.04f, false, true, { 65,-195 })
			, mContentAnimator->CreateAnimation(L"LightenMouseShakeFistRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Shake Fist\\mouse_shake_fist_00", 9, 0.08f, false, true, { 65,-195 }));

		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonEnterLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Enter\\mouse_cannon_enter_00", 17, 0.04f, false, false, { -20,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonEnterLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Enter\\mouse_cannon_enter_00", 17, 0.04f, false, false, { -20,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonEnterRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Enter\\mouse_cannon_enter_00", 17, 0.04f, false, true, { 20,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonEnterRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Enter\\mouse_cannon_enter_00", 17, 0.04f, false, true, { 20,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Idle\\mouse_cannon_idle_00", 21, 0.04f, false, false, { -30,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Idle\\mouse_cannon_idle_00", 21, 0.04f, false, false, { -30,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Idle\\mouse_cannon_idle_00", 21, 0.04f, false, true, { 30,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Idle\\mouse_cannon_idle_00", 21, 0.04f, false, true, { 30,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonShootLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Shoot\\mouse_cannon_shoot_00", 7, 0.04f, false, false, { -30,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonShootLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Shoot\\mouse_cannon_shoot_00", 7, 0.04f, false, false, { -30,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonShootRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Shoot\\mouse_cannon_shoot_00", 7, 0.04f, false, true, { 30,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonShootRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Shoot\\mouse_cannon_shoot_00", 7, 0.04f, false, true, { 30,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonExitLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Exit\\mouse_cannon_enter_00", 17, 0.04f, false, false, { -20,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonExitLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Exit\\mouse_cannon_enter_00", 17, 0.04f, false, false, { -20,-280 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CannonExitRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cannon\\Exit\\mouse_cannon_enter_00", 17, 0.04f, false, true, { 20,-280 })
			, mContentAnimator->CreateAnimation(L"LightenCannonExitRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Cannon\\Exit\\mouse_cannon_enter_00", 17, 0.04f, false, true, { 20,-280 }));

		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Boil\\mouse_catapult_boil_00", 4, 0.08f, false, false, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Boil\\mouse_catapult_boil_00", 4, 0.08f, false, false, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Boil\\mouse_catapult_boil_00", 4, 0.08f, false, true, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Boil\\mouse_catapult_boil_00", 4, 0.08f, false, true, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultThrowChargeLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Throw\\Charge\\mouse_catapult_0", 5, 0.08f, false, false, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultThrowChargeLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Throw\\Charge\\mouse_catapult_0", 5, 0.08f, false, false, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultThrowChargeRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Throw\\Charge\\mouse_catapult_0", 5, 0.08f, false, true, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultThrowChargeRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Throw\\Charge\\mouse_catapult_0", 5, 0.08f, false, true, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultThrowBackLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Throw\\Back\\mouse_catapult_00", 11, 0.04f, false, false, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultThrowBackLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Throw\\Back\\mouse_catapult_00", 11, 0.04f, false, false, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultThrowBackRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Throw\\Back\\mouse_catapult_00", 11, 0.04f, false, true, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultThrowBackRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Throw\\Back\\mouse_catapult_00", 11, 0.04f, false, true, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultThrowGoLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Throw\\Go\\mouse_catapult_0", 10, 0.04f, false, false, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultThrowGoLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Throw\\Go\\mouse_catapult_0", 10, 0.04f, false, false, { 0,-60 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"CatapultThrowGoRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Catapult\\Throw\\Go\\mouse_catapult_0", 10, 0.04f, false, true, { 0,-60 })
			, mContentAnimator->CreateAnimation(L"LightenCatapultThrowGoRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Catapult\\Throw\\Go\\mouse_catapult_0", 10, 0.04f, false, true, { 0,-60 }));

		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"EndArrowLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Intro\\Arrow\\mouse_can_explode_trans_00", 18, 0.07f, false, false, { -30,-200 })
			, mContentAnimator->CreateAnimation(L"LightenEndArrowLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Intro\\Arrow\\mouse_can_explode_trans_00", 18, 0.07f, false, false, { -30,-200 }));
		mContentAnimator->SetLightenAnimation(mContentAnimator->CreateAnimation(L"EndArrowRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Intro\\Arrow\\mouse_can_explode_trans_00", 18, 0.07f, false, true, { 30,-200 })
			, mContentAnimator->CreateAnimation(L"LightenEndArrowRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Intro\\Arrow\\mouse_can_explode_trans_00", 18, 0.07f, false, true, { 30,-200 }));

		//Wheel
		mWheelsAnimator->SetLightenAnimation(mWheelsAnimator->CreateAnimation(L"WheelMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Wheels\\Move\\can_wheels_move_00", 13, 0.07f, false, false)
			, mWheelsAnimator->CreateAnimation(L"LightenWheelMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Wheels\\Move\\can_wheels_move_00", 13, 0.07f, false, false));
		mWheelsAnimator->SetLightenAnimation(mWheelsAnimator->CreateAnimation(L"WheelMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Wheels\\Move\\can_wheels_move_00", 13, 0.07f, false, true)
			, mWheelsAnimator->CreateAnimation(L"LightenWheelMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Lighten\\Wheels\\Move\\can_wheels_move_00", 13, 0.07f, false, true));


		mContentAnimator->GetCompleteEvent(L"MouseIntro") = std::bind(&WernerWermanPh1::MouseIntroCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"MousePopOutLeft") = std::bind(&WernerWermanPh1::MousePopOutCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"MousePopOutRight") = std::bind(&WernerWermanPh1::MousePopOutCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"MouseShakeFistLeft") = std::bind(&WernerWermanPh1::MouseShakeFistCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"MouseShakeFistRight") = std::bind(&WernerWermanPh1::MouseShakeFistCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CannonEnterLeft") = std::bind(&WernerWermanPh1::CannonEnterCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CannonEnterRight") = std::bind(&WernerWermanPh1::CannonEnterCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CannonShootRight") = std::bind(&WernerWermanPh1::CannonShootCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CannonShootLeft") = std::bind(&WernerWermanPh1::CannonShootCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CannonExitLeft") = std::bind(&WernerWermanPh1::CannonExitCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CannonExitRight") = std::bind(&WernerWermanPh1::CannonExitCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CatapultThrowBackLeft") = std::bind(&WernerWermanPh1::CatapultThrowBackCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CatapultThrowBackRight") = std::bind(&WernerWermanPh1::CatapultThrowBackCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CatapultThrowGoLeft") = std::bind(&WernerWermanPh1::CatapultThrowGoCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"CatapultThrowGoRight") = std::bind(&WernerWermanPh1::CatapultThrowGoCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"EndArrowLeft") = std::bind(&WernerWermanPh1::EndArrowCompleteEvent, this);
		mContentAnimator->GetCompleteEvent(L"EndArrowRight") = std::bind(&WernerWermanPh1::EndArrowCompleteEvent, this);

		mCanFrontAnimator->GetCompleteEvent(L"MousePopingLeft") = std::bind(&WernerWermanPh1::CanContentChangeCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"MousePopingRight") = std::bind(&WernerWermanPh1::CanContentChangeCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"MouseDownigLeft") = std::bind(&WernerWermanPh1::CanContentChangeCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"MouseDownigRight") = std::bind(&WernerWermanPh1::CanContentChangeCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"CanDashStopLeft") = std::bind(&WernerWermanPh1::DashStopCopmleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"CanDashStopRight") = std::bind(&WernerWermanPh1::DashStopCopmleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"CanDashStartLeft") = std::bind(&WernerWermanPh1::DashStartCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"CanDashStartRight") = std::bind(&WernerWermanPh1::DashStartCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"CanBoomLeft") = std::bind(&WernerWermanPh1::CanBoomCompleteEvent, this);
		mCanFrontAnimator->GetCompleteEvent(L"CanBoomRight") = std::bind(&WernerWermanPh1::CanBoomCompleteEvent, this);


		mCanFrontAnimator->Play(L"IdleUpLeft", true);
		mCanBackAnimator->Play(L"IdleLeft", true);
		mContentAnimator->Play(L"MouseIntro", false);
	}

	WernerWermanPh1::~WernerWermanPh1()
	{
	}

	void WernerWermanPh1::Tick()
	{
		if (mAnimator->isLighten())
		{
			mCanFrontAnimator->SetLighten(true);
			mCanBackAnimator->SetLighten(true);
			mContentAnimator->SetLighten(true);
			mWheelsAnimator->SetLighten(true);
		}
		else
		{
			mCanFrontAnimator->SetLighten(false);
			mCanBackAnimator->SetLighten(false);
			mContentAnimator->SetLighten(false);
			mWheelsAnimator->SetLighten(false);
		}
		Monster::Tick();
		if (mContentAnimator->GetPlayAnimation() == nullptr
			or mContentAnimator->GetPlayAnimation()->GetName() != L"MouseIntro")
		{
			ChoiceAttack();
			Move();
			Dash();
			Cannon();
			Catapult();
			End();
			if (mbIdleMoving)
			{

				if (mCanBackAnimator->GetPlayAnimation()->GetName() != L"MoveRight"
					&& mCanBackAnimator->GetPlayAnimation()->GetName() != L"MoveLeft")
				{
					if (mbLookRight)
					{

						mCanBackAnimator->Play(L"MoveRight", true);
						mCanFrontAnimator->Play(L"CanMoveRight", true);
						mWheelsAnimator->Play(L"WheelMoveRight", true);
					}
					else
					{
						mCanBackAnimator->Play(L"MoveLeft", true);
						mCanFrontAnimator->Play(L"CanMoveLeft", true);
						mWheelsAnimator->Play(L"WheelMoveLeft", true);
					}
				}
			}
		}
	}

	void WernerWermanPh1::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void WernerWermanPh1::ChoiceAttack()
	{
		if (mbChoiceAttack)
		{
			mChoiceTime += Time::DeltaTime();
			if (mChoiceTime > 2)
			{
				mChoiceTime = 0;
				UINT atkNum = rand() % 3;
				eWernerWermanAttacks attack = (eWernerWermanAttacks)atkNum;
				if (mBeforeAttack == eWernerWermanAttacks::None)
					attack = (eWernerWermanAttacks)(atkNum % 2);
				if (mBeforeAttack == attack)
					attack = (eWernerWermanAttacks)((atkNum + 1) % 3);

				if (attack == eWernerWermanAttacks::Mouse_attack_cannon)
					mNowAttack = eWernerWermanAttacks::Mouse_attack_cannon;
				else if (attack == eWernerWermanAttacks::Mouse_attack_catapult)
					mNowAttack = eWernerWermanAttacks::Mouse_attack_catapult;
				else if (attack == eWernerWermanAttacks::Mouse_attack_dash)
					SummonSpring();

				mbChoiceAttack = false;
			}
			if (mHp < 0)
			{
				mbEnd = true;
			}
		}
	}

	void WernerWermanPh1::Move()
	{
		Vector2 pos = GetPos();
		if (mbIdleMoving)
		{
			if (mbAccelerating)
				mSpeed += 500 * Time::DeltaTime();
			else
				mSpeed -= 500 * Time::DeltaTime();

			if (mSpeed > 500)
				mbAccelerating = false;

			if (!mbAccelerating && mSpeed < 0)
			{
				if (mbIdleGoBack)
				{
					mbIdleGoBack = false;
					mbAccelerating = true;
				}
				else
				{
					mbIdleGoBack = true;
					mbAccelerating = true;
				}
			}

			if (mbLookRight)
			{
				if (mbIdleGoBack)
					pos.x -= mSpeed * Time::DeltaTime();
				else
					pos.x += mSpeed * Time::DeltaTime();
			}
			else
			{
				if (mbIdleGoBack)
					pos.x += mSpeed * Time::DeltaTime();
				else
					pos.x -= mSpeed * Time::DeltaTime();

			}
		}

		else if (mbDashIng)
		{
			if (mSpeed < 1000)
				mSpeed += 1000 * Time::DeltaTime();

			if (mbLookRight)
			{
				pos.x += mSpeed * Time::DeltaTime();
				if (pos.x > 1460)
				{
					pos.x = 1460;
					mbDashIng = false;
					mCanFrontAnimator->Play(L"CanDashStopRight", false);
				}
			}
			else
			{
				pos.x -= mSpeed * Time::DeltaTime();
				if (pos.x < 140)
				{
					pos.x = 140;
					mbDashIng = false;
					mCanFrontAnimator->Play(L"CanDashStopLeft", false);
				}
			}
		}
		SetPos(pos);
	}

	void WernerWermanPh1::Dash()
	{
		if (mbSummonedSpring)
		{
			mDashTimeChecker += Time::DeltaTime();
			if (mDashTimeChecker > 5)
			{
				mbIdleMoving = false;
				if (mbLookRight)
				{
					mCanBackAnimator->Play(L"IdleRight", true);
					mCanFrontAnimator->Play(L"MousePopingRight", false);
					mContentAnimator->Play(L"MousePopOutRight", false);
					mWheelsAnimator->SetPlayAnimation(nullptr);
				}
				else
				{
					mCanBackAnimator->Play(L"IdleLeft", true);
					mCanFrontAnimator->Play(L"MousePopingLeft", false);
					mContentAnimator->Play(L"MousePopOutLeft", false);
					mWheelsAnimator->SetPlayAnimation(nullptr);
				}
				mbMouseDown = false;
				mDashTimeChecker = 0;
				mbIdleMoving = false;
				mbSummonedSpring = false;
				
			}
		}
		if (mbDashFin)
		{
			mDashTimeChecker += Time::DeltaTime();
			if (mDashTimeChecker > 0.5)
			{


				mDashTimeChecker = 0;
				mSpeed = 0;
				mbDashFin = false;
				mbIdleMoving = true;
				mbIdleGoBack = false;
				mbAccelerating = true;
				mbChoiceAttack = true;
			}
		}
	}

	void WernerWermanPh1::Cannon()
	{
		if (mNowAttack == eWernerWermanAttacks::Mouse_attack_cannon
			&& !mbCannonMode)
		{
			mbIdleMoving = true;
			if (mbLookRight)
				mContentAnimator->Play(L"CannonEnterRight", false);
			else
				mContentAnimator->Play(L"CannonEnterLeft", false);
			mbCannonMode = true;
		} 

		if (mbCannonMode)
		{
			mCannonShootTimeChecker += Time::DeltaTime();
			if (mCannonShootTimeChecker > 2 && mCannonShootCount == 0
				|| mCannonShootTimeChecker > 3 && mCannonShootCount == 1
				|| mCannonShootTimeChecker > 5.2 && mCannonShootCount == 2
				|| mCannonShootTimeChecker > 5.8 && mCannonShootCount == 3
				|| mCannonShootTimeChecker > 6.6 && mCannonShootCount == 4)
			{
				if (mbLookRight)
					mContentAnimator->Play(L"CannonShootRight", false);
				else
					mContentAnimator->Play(L"CannonShootLeft", false);
				mCannonShootCount += 1;
				Vector2 pos = GetPos();
				pos.y -= GetScale().y + 200;
				TomatoBomb* bomb = new TomatoBomb(mbLookRight);
				bomb->SetPos(pos);
				SceneManager::GetCurScene()->AddGameObject(bomb, eColliderLayer::Monster_Projecttile);
			}
			if (mCannonShootTimeChecker > 9)
			{
				if (mbLookRight)
					mContentAnimator->Play(L"CannonExitRight", false);
				else
					mContentAnimator->Play(L"CannonExitLeft", false);
				mCannonShootTimeChecker = 0;
			}
		}
	}

	void WernerWermanPh1::Catapult()
	{
		if (mNowAttack == eWernerWermanAttacks::Mouse_attack_catapult
			&& !mbCatapultMode)
		{
			mbIdleMoving = true;
			if (mbLookRight)
				mContentAnimator->Play(L"CatapultIdleRight", false);
			else
				mContentAnimator->Play(L"CatapultIdleLeft", false);
			mbCatapultMode = true;
		}
		
		if (mbCatapultMode)
		{
			if (mContentAnimator->GetAddPos().y > -200
				&& !mbCatapultExit)
			{
				Vector2 pos = mContentAnimator->GetAddPos();
				if (mbLookRight)
					pos.x = 30;
				else
					pos.x = -30;
				pos.y -= 500 * Time::DeltaTime();
				mContentAnimator->SetAddPos(pos);
			}

			else if (!mbCatapultIntroFin)
			{

				mCatapultShootTimeChecker += Time::DeltaTime();
				if (mCatapultShootTimeChecker > 1)
				{
					if (mCatapultShootCount < 3)
					{
						Vector2 pos = mContentAnimator->GetAddPos();
						pos.y = -200;
						mContentAnimator->SetAddPos(pos);
						mCatapultShootTimeChecker = 0;
						if (mbLookRight)
							mContentAnimator->Play(L"CatapultThrowBackRight", false);
						else
							mContentAnimator->Play(L"CatapultThrowBackLeft", false);
						mbCatapultIntroFin = true;
					}
					else
					{
						mbCatapultExit = true;
					}
				}
			}

			if (mbCatapultCharge)
			{
				mCatapultChargeTimeChecker += Time::DeltaTime();
				if (mCatapultChargeTimeChecker > 2)
				{
					mCatapultChargeTimeChecker = 0;
					if (mbLookRight)
						mContentAnimator->Play(L"CatapultThrowGoRight", false);
					else
						mContentAnimator->Play(L"CatapultThrowGoLeft", false);
					mbCatapultCharge = false;
					mbCatapultShooting = true;
				}
			}

			if (mbCatapultShooting)
			{
				mCatapultShootTimeChecker += Time::DeltaTime();
				if (mCatapultShootTimeChecker > 0.19)
				{
					mCatapultShootTimeChecker = 0;
					mbCatapultShooting = false;
					mCatapultShootCount += 1;

					std::vector<UCHAR> pinknum = {};
					switch (rand()%4)
					{
					case 0:
						pinknum = { 1,4 };
						break;
					case 1:
						pinknum = { 2,4 };
						break;
					case 2:
						pinknum = { 0,3 };
						break;
					case 3:
						pinknum = { 0,2 };
						break;
					}
					for (size_t i = 0; i < 5; i++)
					{
						bool pink = false;
						for (size_t k = 0; k < 2; k++)
						{
							if (i == pinknum[k])
								pink = true;
						}
						Junk* junk = new Junk(mbLookRight, pink);
						Vector2 pos = GetPos();
						pos.y -= GetScale().y + 200;
						junk->SetPos(pos);
						Vector2 dir;
						if (mbLookRight)
						{
							dir =Vector2(1600, 250) - pos;
							junk->SetDestDir(math::Rotate(dir,i*17 + 340));
						}
						else
						{
							dir =Vector2(0, 150) - pos;
							junk->SetDestDir(math::Rotate(dir, i*17 + 310));
						}
						SceneManager::GetCurScene()->AddGameObject(junk, eColliderLayer::Monster_Projecttile);
					}
				}
			}

			if (mbCatapultExit)
			{
				Vector2 pos = mContentAnimator->GetAddPos();
				pos.y += 500 * Time::DeltaTime();
				mContentAnimator->SetAddPos(pos);
				if (pos.y > 0)
				{
					mbCatapultExit = false;
					mContentAnimator->SetPlayAnimation(nullptr);
					mCatapultShootCount = 0;
					mBeforeAttack = eWernerWermanAttacks::Mouse_attack_catapult;
					mNowAttack = eWernerWermanAttacks::None;
					mContentAnimator->SetAddPos({ 0,0 });
					mbCatapultMode = false;
					mbChoiceAttack = true;
				}
			}
		}
	}

	void WernerWermanPh1::SummonSpring()
	{
		mbIdleMoving = true;
		Vector2 pos = GetPos();
		pos.y -= GetScale().y;
		if (!mbLookRight)
		{
			PinkSpring* spring1 = new PinkSpring(-5, mbLookRight);
			spring1->SetPos(pos);
			PinkSpring* spring2 = new PinkSpring(-45, mbLookRight);
			pos.x += 100;
			spring2->SetPos(pos);
			SceneManager::GetCurScene()->AddGameObject(spring1, eColliderLayer::FrontMonster);
			SceneManager::GetCurScene()->AddGameObject(spring2, eColliderLayer::FrontMonster);
		}
		else
		{
			PinkSpring* spring1 = new PinkSpring(-5, mbLookRight);
			spring1->SetPos(pos);
			PinkSpring* spring2 = new PinkSpring(-45, mbLookRight);
			pos.x -= 100;
			spring2->SetPos(pos);
			SceneManager::GetCurScene()->AddGameObject(spring1, eColliderLayer::FrontMonster);
			SceneManager::GetCurScene()->AddGameObject(spring2, eColliderLayer::FrontMonster);
		}
		mbSummonedSpring = true;
		mBeforeAttack = eWernerWermanAttacks::Mouse_attack_dash;
	}

	void WernerWermanPh1::End()
	{
		if (mbEnd)
		{
			if (mCanBackAnimator->GetPlayAnimation()->GetName() != L"MoveRight"
				&& mCanBackAnimator->GetPlayAnimation()->GetName() != L"MoveLeft")
			{
				if (mbLookRight)
				{

					mCanBackAnimator->Play(L"MoveRight", true);
					mCanFrontAnimator->Play(L"CanMoveRight", true);
					mWheelsAnimator->Play(L"WheelMoveRight", true);
				}
				else
				{
					mCanBackAnimator->Play(L"MoveLeft", true);
					mCanFrontAnimator->Play(L"CanMoveLeft", true);
					mWheelsAnimator->Play(L"WheelMoveLeft", true);
				}
			}
			Vector2 pos = GetPos();
			mbIdleMoving = false;
			if (mbLookRight)
			{
				pos.x += 500 * Time::DeltaTime();
				if (pos.x > 800)
				{
					pos.x = 800;
					if (mContentAnimator->GetPlayAnimation() == nullptr
						or mContentAnimator->GetPlayAnimation()->GetName() != L"EndArrowRight")
						mContentAnimator->Play(L"EndArrowRight", false);
				}
				SetPos(pos);
			}
			else
			{
				pos.x -= 500 * Time::DeltaTime();
				if (pos.x < 800)
				{
					pos.x = 800;
					if(mContentAnimator->GetPlayAnimation() == nullptr
						or mContentAnimator->GetPlayAnimation()->GetName() != L"EndArrowLeft")
						mContentAnimator->Play(L"EndArrowLeft", false);
				}
				SetPos(pos);
			}
			mbChoiceAttack = false;
		}
	}

	void WernerWermanPh1::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void WernerWermanPh1::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void WernerWermanPh1::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void WernerWermanPh1::MouseIntroCompleteEvent()
	{
		mbMouseDown = true;
		mCanFrontAnimator->Play(L"MouseDownigLeft", false);
		mContentAnimator->SetPlayAnimation(nullptr);
		mbChoiceAttack = true;
	}

	void WernerWermanPh1::CanContentChangeCompleteEvent()
	{
		if (mbMouseDown)
		{
			if (mbLookRight)
			{
				mCanFrontAnimator->Play(L"IdleDownRight", true);
			}
			else
			{
				mCanFrontAnimator->Play(L"IdleDownLeft", true);
			}
		}
		else
		{
			if (mbLookRight)
				mCanFrontAnimator->Play(L"IdleUpRight", true);
			else
				mCanFrontAnimator->Play(L"IdleUpLeft", true);

		}
	}
	void WernerWermanPh1::MouseShakeFistCompleteEvent()
	{
		if (mbLookRight)
		{
			mCanBackAnimator->SetPlayAnimation(nullptr);
			mCanFrontAnimator->Play(L"CanDashStartRight", false);
			mContentAnimator->SetPlayAnimation(nullptr);
			mWheelsAnimator->SetPlayAnimation(nullptr);
		}
		else
		{
			mCanBackAnimator->SetPlayAnimation(nullptr);
			mCanFrontAnimator->Play(L"CanDashStartLeft", false);
			mContentAnimator->SetPlayAnimation(nullptr);
			mWheelsAnimator->SetPlayAnimation(nullptr);
		}
	}
	void WernerWermanPh1::MousePopOutCompleteEvent()
	{
		if (mbLookRight)
		{
			mContentAnimator->Play(L"MouseShakeFistRight", false);
		}
		else
		{
			mContentAnimator->Play(L"MouseShakeFistLeft", false);
		}
	}

	void WernerWermanPh1::DashStartCompleteEvent()
	{
		if (mbLookRight)
		{
			mCanFrontAnimator->Play(L"CanDashRight", true);
		}
		else
		{
			mCanFrontAnimator->Play(L"CanDashLeft", true);
		}
		mbDashIng = true;
	}

	void WernerWermanPh1::DashStopCopmleteEvent()
	{
		mbDashFin = true;
		mbLookRight = !mbLookRight;
		if (mbLookRight)
		{
			mCanBackAnimator->Play(L"IdleRight", true);
			mCanFrontAnimator->Play(L"IdleDownRight", false);
			mContentAnimator->SetPlayAnimation(nullptr);
			mWheelsAnimator->SetPlayAnimation(nullptr);
		}
		else
		{
			mCanBackAnimator->Play(L"IdleLeft", true);
			mCanFrontAnimator->Play(L"IdleDownLeft", false);
			mContentAnimator->SetPlayAnimation(nullptr);
			mWheelsAnimator->SetPlayAnimation(nullptr);
		}
		mNowAttack = eWernerWermanAttacks::None;
		mBeforeAttack = eWernerWermanAttacks::Mouse_attack_dash;
	}

	void WernerWermanPh1::CannonEnterCompleteEvent()
	{
		if (mbLookRight)
		{
			mContentAnimator->Play(L"CannonIdleRight", true);
		}
		else
		{
			mContentAnimator->Play(L"CannonIdleLeft", true);
		}
	}

	void WernerWermanPh1::CannonShootCompleteEvent()
	{
		if (mbLookRight)
		{
			mContentAnimator->Play(L"CannonIdleRight", true);
		}
		else
		{
			mContentAnimator->Play(L"CannonIdleLeft", true);
		}
	}

	void WernerWermanPh1::CannonExitCompleteEvent()
	{
		mContentAnimator->SetPlayAnimation(nullptr);
		mbCannonMode = false;
		mbChoiceAttack = true;
		mCannonShootCount = 0;
		mNowAttack = eWernerWermanAttacks::None;
		mBeforeAttack = eWernerWermanAttacks::Mouse_attack_cannon;
	}

	void WernerWermanPh1::CatapultThrowBackCompleteEvent()
	{
		if (mbLookRight)
			mContentAnimator->Play(L"CatapultThrowChargeRight", true);
		else
			mContentAnimator->Play(L"CatapultThrowChargeLeft", true);
		mbCatapultCharge = true;
	}

	void WernerWermanPh1::CatapultThrowGoCompleteEvent()
	{
		if (mbLookRight)
			mContentAnimator->Play(L"CatapultIdleRight", true);
		else
			mContentAnimator->Play(L"CatapultIdleLeft", true);
		mbCatapultIntroFin = false;
	}

	void WernerWermanPh1::EndArrowCompleteEvent()
	{
		mCanBackAnimator->SetPlayAnimation(nullptr);
		mWheelsAnimator->SetPlayAnimation(nullptr);
		mContentAnimator->SetPlayAnimation(nullptr);
		mbEnd = false;
		if (mbLookRight)
		{
			mCanFrontAnimator->Play(L"CanBoomRight", false);
		}
		else
		{
			mCanFrontAnimator->Play(L"CanBoomLeft", false);
		}
	}

	void WernerWermanPh1::CanBoomCompleteEvent()
	{
		ObjectManager::Destroy(this);
		WernerWermanPh2* nextPhase = new WernerWermanPh2(mbLookRight);
		SceneManager::GetCurScene()->AddGameObject(nextPhase, eColliderLayer::FrontMonster);
		dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->SetPhase2Object(nextPhase);
		dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->SetPhase(2);
	}

	void WernerWermanPh1::Release()
	{
	}

}