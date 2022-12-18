#include "yaWernerWermanPh2.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaPh2WallGround.h"
#include "yaDisc.h"
#include "yaBossCanRatScene.h"
namespace ya 
{
	WernerWermanPh2::WernerWermanPh2(bool right, bool init)
		:mbRight(right)
		,mBeforeScissorHeight(64)
		, mDiscTimeChecker(0)
	{
		SetName(L"WernerWermanPh2");
		mHp = 200;
		SetPos({ 800,800 });
		SetScale({ 250.0f,220.0f });
		mCollider = new Collider();
		mHeadCollider = new Collider();
		mFireLeftSmallCollider = new Collider();
		mFireLeftLargeCollider = new Collider();
		mFireRightSmallCollider = new Collider();
		mFireRightLargeCollider = new Collider();
		mHeadCollider->SetScale({ 140,120 });
		mFireLeftSmallCollider->SetScale({ 350,80 });
		mFireRightSmallCollider->SetScale({ 350,80 });
		mFireLeftLargeCollider->SetScale({ 170,200 });
		mFireRightLargeCollider->SetScale({ 170,200 });

		if (mbRight)
			mHeadCollider->SetAddPos({ -50,-300 });
		else
			mHeadCollider->SetAddPos({ 50,-300 });

		mCollider->SetAddPos({ 0,-150 });
		mFireLeftSmallCollider->SetAddPos({ -300,0 });
		mFireRightSmallCollider->SetAddPos({ 300,0 });
		mFireLeftLargeCollider->SetAddPos({ -450,-50 });
		mFireRightLargeCollider->SetAddPos({ 450,-50 });

		mFireLeftSmallCollider->SetBulletPassing(true);
			mFireLeftLargeCollider->SetBulletPassing(true);
			mFireRightSmallCollider->SetBulletPassing(true);
			mFireRightLargeCollider->SetBulletPassing(true);


		mFireLeftSmallCollider->SetOff(true);
		mFireLeftLargeCollider->SetOff(true);
		mFireRightSmallCollider->SetOff(true);
		mFireRightLargeCollider->SetOff(true);

		AddComponent(mCollider);
		AddComponent(mHeadCollider);
		AddComponent(mFireLeftSmallCollider);
		AddComponent(mFireRightSmallCollider);
		AddComponent(mFireLeftLargeCollider);
		AddComponent(mFireRightLargeCollider);

		if (!init)
		{
			mWoodCart = ObjectManager::Instantiate<BottomWoodCart>(SceneManager::GetCurScene(), eColliderLayer::FrontObject);
			mBottomAnimator = mWoodCart->GetAnimator();
		}
		else
		{
			mBottomAnimator = new Animator();
			AddComponent(mBottomAnimator);
		}
		mAnimator = new Animator();

		mTinBackAnimator = new Animator();
		mScissorAnimator = new Animator();
		mLeftCannonAnimator = new Animator();
		mRightCannonAnimator = new Animator();
		mMouseAnimator = new Animator();
		mTinFrontAnimator = new Animator();
		mLeftFireAnimator = new Animator();
		mRightFireAnimator = new Animator();

		AddComponent(mAnimator);
		AddComponent(mTinBackAnimator);
		AddComponent(mScissorAnimator);
		AddComponent(mLeftCannonAnimator);
		AddComponent(mRightCannonAnimator);
		AddComponent(mMouseAnimator);
		AddComponent(mTinFrontAnimator);
		AddComponent(mLeftFireAnimator);
		AddComponent(mRightFireAnimator);

		mBottomAnimator->SetLightenAnimation(mBottomAnimator->CreateAnimation(L"BottomIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Bottom\\Boil\\can_phase2_boil_00", 4, 0.06f, false, false)
			, mBottomAnimator->CreateAnimation(L"LightenBottomIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Bottom\\Boil\\can_phase2_boil_00", 4, 0.06f, false, false));
		mBottomAnimator->SetLightenAnimation(mBottomAnimator->CreateAnimation(L"BottomIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Bottom\\Boil\\can_phase2_boil_00", 4, 0.06f, false, true)
			, mBottomAnimator->CreateAnimation(L"LightenBottomIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Bottom\\Boil\\can_phase2_boil_00", 4, 0.06f, false, true));
		mBottomAnimator->SetLightenAnimation(mBottomAnimator->CreateAnimation(L"BottomMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Bottom\\Move\\can_phase2_move_00", 12, 0.05f, false, false)
			, mBottomAnimator->CreateAnimation(L"LightenBottomMoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Bottom\\Move\\can_phase2_move_00", 12, 0.05f, false, false));
		mBottomAnimator->SetLightenAnimation(mBottomAnimator->CreateAnimation(L"BottomMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Bottom\\Move\\can_phase2_move_00", 12, 0.05f, false, true)
			, mBottomAnimator->CreateAnimation(L"LightenBottomMoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Bottom\\Move\\can_phase2_move_00", 12, 0.05f, false, true));

		mTinBackAnimator->SetLightenAnimation(mTinBackAnimator->CreateAnimation(L"TinBackIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Tin\\Boil\\Back\\can_phase2_tin_boil_back_00", 4, 0.06f, false, false)
			, mTinBackAnimator->CreateAnimation(L"LightenTinBackIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Tin\\Boil\\Back\\can_phase2_tin_boil_back_00", 4, 0.06f, false, false));
		mTinBackAnimator->SetLightenAnimation(mTinBackAnimator->CreateAnimation(L"TinBackIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Tin\\Boil\\Back\\can_phase2_tin_boil_back_00", 4, 0.06f, false, true)
			, mTinBackAnimator->CreateAnimation(L"LightenTinBackIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Tin\\Boil\\Back\\can_phase2_tin_boil_back_00", 4, 0.06f, false, true));
		mTinFrontAnimator->SetLightenAnimation(mTinFrontAnimator->CreateAnimation(L"TinFrontIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Tin\\Boil\\can_phase2_tin_boil_00", 4, 0.06f, false, false,{-3,0})
			, mTinFrontAnimator->CreateAnimation(L"LightenTinFrontIdleLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Tin\\Boil\\can_phase2_tin_boil_00", 4, 0.06f, false, false, { -3,0 }));
		mTinFrontAnimator->SetLightenAnimation(mTinFrontAnimator->CreateAnimation(L"TinFrontIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Tin\\Boil\\can_phase2_tin_boil_00", 4, 0.06f, false, true, { 3,0 })
			, mTinFrontAnimator->CreateAnimation(L"LightenTinFrontIdleRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Tin\\Boil\\can_phase2_tin_boil_00", 4, 0.06f, false, true, { 3,0 }));


		mScissorAnimator->CreateAnimation(L"ScissorUp", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Scissor\\Up\\can_phase2_scissor_00", 16, 0.05f, false, false);
		mScissorAnimator->CreateAnimation(L"ScissorDown", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Scissor\\Down\\can_phase2_scissor_00", 16, 0.05f, false, false);

		mLeftCannonAnimator->SetLightenAnimation(mLeftCannonAnimator->CreateAnimation(L"CannonBoilLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Cannon\\Boil\\can_phase2_cannon_boil_00", 4, 0.05f, false, false)
			, mLeftCannonAnimator->CreateAnimation(L"LightenCannonBoilLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Cannon\\Boil\\can_phase2_cannon_boil_00", 4, 0.05f, false, false));
		mRightCannonAnimator->SetLightenAnimation(mRightCannonAnimator->CreateAnimation(L"CannonBoilRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Cannon\\Boil\\can_phase2_cannon_boil_00", 4, 0.05f, false, true)
			, mRightCannonAnimator->CreateAnimation(L"LightenCannonBoilRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Cannon\\Boil\\can_phase2_cannon_boil_00", 4, 0.05f, false, true));
		mLeftCannonAnimator->SetLightenAnimation(mLeftCannonAnimator->CreateAnimation(L"CannonShootLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Cannon\\Shoot\\can_phase2_cannon_shoot_00", 6, 0.07f, false, false, {0,40})
			, mLeftCannonAnimator->CreateAnimation(L"LightenCannonShootLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Cannon\\Shoot\\can_phase2_cannon_shoot_00", 6, 0.07f, false, false, { 0,40 }));
		mRightCannonAnimator->SetLightenAnimation(mRightCannonAnimator->CreateAnimation(L"CannonShootRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Cannon\\Shoot\\can_phase2_cannon_shoot_00", 6, 0.07f, false, true, { 40,30 })
			, mRightCannonAnimator->CreateAnimation(L"LightenCannonShootRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Cannon\\Shoot\\can_phase2_cannon_shoot_00", 6, 0.07f, false, true, { 40,30 }));

		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Intro\\Intro\\mouse_can_explode_trans_00", 4, 0.06f, false, false,{0, 275})
			, mMouseAnimator->CreateAnimation(L"LightenMouseIntroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Intro\\Intro\\mouse_can_explode_trans_00", 4, 0.06f, false, false, { 0, 275 }));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Intro\\Intro\\mouse_can_explode_trans_00", 4, 0.06f, false, true, { 0, 275 })
			, mMouseAnimator->CreateAnimation(L"LightenMouseIntroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Intro\\Intro\\mouse_can_explode_trans_00", 4, 0.06f, false, true, { 0, 275 }));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionAEnterLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\A\\mouse_phase2_transA_00", 3, 0.06f, true, false)
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionAEnterLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\A\\mouse_phase2_transA_00", 3, 0.06f, true, false));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionAEnterRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\A\\mouse_phase2_transA_00", 3, 0.06f, true, true)
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionAEnterRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\A\\mouse_phase2_transA_00", 3, 0.06f, true, true));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionABoilLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\A\\Boil\\mouse_phase2_transA_00", 2, 0.05f, true, false)
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionABoilLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\A\\Boil\\mouse_phase2_transA_00", 2, 0.05f, true, false));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionABoilRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\A\\Boil\\mouse_phase2_transA_00", 2, 0.05f, true, true)
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionABoilRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\A\\Boil\\mouse_phase2_transA_00", 2, 0.05f, true, true));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionDEnterLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\D\\mouse_phase2_transD_00", 3, 0.06f, true, false,{20,0})
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionDEnterLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\D\\mouse_phase2_transD_00", 3, 0.06f, true, false, { 20,0 }));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionDEnterRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\D\\mouse_phase2_transD_00", 3, 0.06f, true, true, { -20,0 })
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionDEnterRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\D\\mouse_phase2_transD_00", 3, 0.06f, true, true, { -20,0 }));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionDBoilLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\D\\Boil\\mouse_phase2_transD_00", 2, 0.05f, true, false, {20,0})
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionDBoilLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\D\\Boil\\mouse_phase2_transD_00", 2, 0.05f, true, false, { 20,0 }));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseTransitionDBoilRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\D\\Boil\\mouse_phase2_transD_00", 2, 0.05f, true, true, { -20,0 })
			, mMouseAnimator->CreateAnimation(L"LightenMouseTransitionDBoilRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\D\\Boil\\mouse_phase2_transD_00", 2, 0.05f, true, true, { -20,0 }));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseEndRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\B\\mouse_phase2_transB_00", 7, 0.05f, false, true)
			, mMouseAnimator->CreateAnimation(L"LightenMouseEndRight", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\B\\mouse_phase2_transB_00", 7, 0.05f, false, true));
		mMouseAnimator->SetLightenAnimation(mMouseAnimator->CreateAnimation(L"MouseEndLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Transition\\B\\mouse_phase2_transB_00", 7, 0.05f, false, false)
			, mMouseAnimator->CreateAnimation(L"LightenMouseEndLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Lighten\\Transition\\B\\mouse_phase2_transB_00", 7, 0.05f, false, false));


		mRightFireAnimator->CreateAnimation(L"RightFire", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Flamethrower\\mouse_flamethrower_00", 24, 0.07f, false, false);
		mLeftFireAnimator->CreateAnimation(L"LeftFire", L"..\\Resources\\Image\\Werner Werman\\Phase 2\\Flamethrower\\mouse_flamethrower_00", 24, 0.07f, false, true);

		mMouseAnimator->GetCompleteEvent(L"MouseIntroLeft") = std::bind(&WernerWermanPh2::MouseIntroCompleteEvent, this);
		mMouseAnimator->GetCompleteEvent(L"MouseIntroRight") = std::bind(&WernerWermanPh2::MouseIntroCompleteEvent, this);
		mMouseAnimator->GetCompleteEvent(L"MouseTransitionAEnterLeft") = std::bind(&WernerWermanPh2::TransitionEnterCompleteEvent, this);
		mMouseAnimator->GetCompleteEvent(L"MouseTransitionAEnterRight") = std::bind(&WernerWermanPh2::TransitionEnterCompleteEvent, this);
		mMouseAnimator->GetCompleteEvent(L"MouseTransitionDEnterLeft") = std::bind(&WernerWermanPh2::TransitionEnterCompleteEvent, this);
		mMouseAnimator->GetCompleteEvent(L"MouseTransitionDEnterRight") = std::bind(&WernerWermanPh2::TransitionEnterCompleteEvent, this);

		mRightFireAnimator->GetCompleteEvent(L"RightFire") = std::bind(&WernerWermanPh2::FireCompleteEvent, this);
		mLeftFireAnimator->GetCompleteEvent(L"LeftFire") = std::bind(&WernerWermanPh2::FireCompleteEvent, this);

		mScissorAnimator->GetCompleteEvent(L"ScissorUp") = std::bind(&WernerWermanPh2::ScissorMoveCompleteEvent, this);
		mScissorAnimator->GetCompleteEvent(L"ScissorDown") = std::bind(&WernerWermanPh2::ScissorMoveCompleteEvent, this);

		if (mbRight)
		{
			mBottomAnimator->Play(L"BottomIdleRight", true);
			mTinBackAnimator->SetPlayAnimation(nullptr);
			mScissorAnimator->SetPlayAnimation(nullptr);
			mLeftCannonAnimator->SetPlayAnimation(nullptr);
			mRightCannonAnimator->SetPlayAnimation(nullptr);
			mMouseAnimator->Play(L"MouseIntroRight", false);
			mTinFrontAnimator->SetPlayAnimation(nullptr);
			mLeftFireAnimator->SetPlayAnimation(nullptr);
			mRightFireAnimator->SetPlayAnimation(nullptr);

		}
		else
		{
			mBottomAnimator->Play(L"BottomIdleLeft", true);
			mTinBackAnimator->SetPlayAnimation(nullptr);
			mScissorAnimator->SetPlayAnimation(nullptr);
			mLeftCannonAnimator->SetPlayAnimation(nullptr);
			mRightCannonAnimator->SetPlayAnimation(nullptr);
			mMouseAnimator->Play(L"MouseIntroLeft", false);
			mTinFrontAnimator->SetPlayAnimation(nullptr);
			mLeftFireAnimator->SetPlayAnimation(nullptr);
			mRightFireAnimator->SetPlayAnimation(nullptr);

		}
		mBottomAnimator;
		mTinBackAnimator->SetAddPos({ 0,-175 });
		mScissorAnimator->SetAddPos({ 0,-85 });
		mLeftCannonAnimator->SetAddPos({-60,-120});
		mRightCannonAnimator->SetAddPos({ 60,-120 });
		if (mbRight)
			mMouseAnimator->SetAddPos({ 15,-175 });
		else
			mMouseAnimator->SetAddPos({ -15,-175 });
		mTinFrontAnimator->SetAddPos({ 0,-130 });
		mLeftFireAnimator->SetAddPos({ -340,-35 });
		mRightFireAnimator->SetAddPos({ 340,-35 });

		if (init)
		{
			Disc(true);
		}
		else
		{

		}



	}

	WernerWermanPh2::~WernerWermanPh2()
	{
	}

	void WernerWermanPh2::Tick()
	{
		if (mAnimator->isLighten())
		{
			mTinBackAnimator->SetLighten(true);
			mLeftCannonAnimator->SetLighten(true);
			mRightCannonAnimator->SetLighten(true);
			mMouseAnimator->SetLighten(true);
			mTinFrontAnimator->SetLighten(true);

		}
		else
		{
			mTinBackAnimator->SetLighten(false);
			mLeftCannonAnimator->SetLighten(false);
			mRightCannonAnimator->SetLighten(false);
			mMouseAnimator->SetLighten(false);
			mTinFrontAnimator->SetLighten(false);
		}
		Monster::Tick();
		if (mMouseAnimator->GetPlayAnimation()->GetName() != L"MouseEndRight"
			&& mMouseAnimator->GetPlayAnimation()->GetName() != L"MouseEndLeft")
		{
			Scissor();
			Fire();
			ChoiceDisc();
		}
		Move();
		Vector2 cartPos =  mWoodCart->GetPos();
		cartPos.x = GetPos().x;
		mWoodCart->Move(cartPos);
		
		if (mMouseAnimator->GetPlayAnimation()->GetName() == L"MouseEndLeft"
			|| mMouseAnimator->GetPlayAnimation()->GetName() == L"MouseEndRight")
		{
			mDeathTimeChecker += Time::DeltaTime();
			if (mDeathTimeChecker > 1)
			{
				mDeathTimeChecker = 0;
				dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->SetPhase(3);
			}
		}
	}

	void WernerWermanPh2::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void WernerWermanPh2::Scissor()
	{
		if (mbScissorMove)
		{
			mScissorAnimator->SetStop(false);
			mScissorMoveTimeChecker += Time::DeltaTime();
			Vector2 pos = GetPos();
			if (mScissorMoveTimeChecker > 0.05)
			{
				pos.y -= mScissorAnimator->GetPlayAnimation()->GetPlayPicture()->GetHeight() - mBeforeScissorHeight;
				Vector2 addPos = mScissorAnimator->GetAddPos();
				addPos.y += mScissorAnimator->GetPlayAnimation()->GetPlayPicture()->GetHeight() - mBeforeScissorHeight;
				mScissorAnimator->SetAddPos(addPos);
				mBeforeScissorHeight = mScissorAnimator->GetPlayAnimation()->GetPlayPicture()->GetHeight();
				mScissorMoveTimeChecker = 0;
			}
			SetPos(pos);
		}
	}

	void WernerWermanPh2::Fire()
	{
		if (!mbScissorMove)
		{
			mFireTimeChecker += Time::DeltaTime();
			if (mFireTimeChecker > 2.5)
			{
				mFireTimeChecker = 0;
				mLeftFireAnimator->Play(L"LeftFire", false);
				mRightFireAnimator->Play(L"RightFire", false);
			}

			if (mLeftFireAnimator->GetPlayAnimation() != nullptr)
			{
				if (mFireTimeChecker > 0.7)
				{
					mFireLeftSmallCollider->SetOff(false);
					mFireLeftLargeCollider->SetOff(false);
					mFireRightSmallCollider->SetOff(false);
					mFireRightLargeCollider->SetOff(false);
				}

				if (mFireTimeChecker > 1.4)
				{
					mFireLeftSmallCollider->SetOff(true);
					mFireLeftLargeCollider->SetOff(true);
					mFireRightSmallCollider->SetOff(true);
					mFireRightLargeCollider->SetOff(true);
				}
			}
		}


	}

	void WernerWermanPh2::ChoiceDisc()
	{
		mDiscTimeChecker += Time::DeltaTime();
		if (mDiscTimeChecker > 3)
		{
			UINT a = rand() % 14;
			UINT b = rand() % 14;
			UINT bGo = rand() % 3;
			mDiscs[a / 7][a % 7]->SetGo();
			if (bGo > 0)
				mDiscs[b / 7][b % 7]->SetGo();
			
			if (a == b)
			{
				for (size_t i = 0; i < 7; i++)
				{
					mDiscs[a / 7][i]->SetGo();
				}
			}
			mDiscTimeChecker = 0;
		}
	}

	void WernerWermanPh2::Move()
	{

		Vector2 pos = GetPos();
		std::wstring dir;
		if (mbRight)
			dir = L"Right";
		else
			dir = L"Left";
		if (mMouseAnimator->GetPlayAnimation()->GetName() != L"MouseIntro"+dir
			&& mMouseAnimator->GetPlayAnimation()->GetName() != L"MouseEnd"+dir)
		{
			if (mbSpeedUp)
				mSpeed += 300 * Time::DeltaTime();
			else
				mSpeed -= 300 * Time::DeltaTime();
			pos.x += mSpeed * Time::DeltaTime();
			if (mSpeed > 100)
				mbSpeedUp = false;
			else if (mSpeed < -100)
				mbSpeedUp = true;
		}
		if (mMouseAnimator->GetPlayAnimation()->GetName() == L"MouseEnd" + dir)
		{
			if (pos.x < 801)
			{
				pos.x += 300 * Time::DeltaTime();
				if (pos.x > 800)
					pos.x = 800;
			}
			else if (pos.x > 799)
			{
				pos.x -= 300 * Time::DeltaTime();
				if (pos.x < 800)
					pos.x = 800;
			}
		}
		SetPos(pos);
	}

	void WernerWermanPh2::DestroyWoodCart()
	{
		if (mWoodCart != nullptr)
			ObjectManager::Destroy(mWoodCart);
	}

	void WernerWermanPh2::SetDiscs(Disc* disc, int i)
	{
		mDiscs[i].push_back(disc);
		SceneManager::GetCurScene()->AddGameObject(disc, eColliderLayer::FrontMonster);
	}

	void WernerWermanPh2::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void WernerWermanPh2::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void WernerWermanPh2::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void WernerWermanPh2::MouseIntroCompleteEvent()
	{
		std::wstring dir;
		if (mbRight)
			dir = L"Right";
		else
			dir = L"Left";
		mBottomAnimator->Play(L"BottomMove"+dir, true);
		mTinBackAnimator->Play(L"TinBackIdle" + dir, true);
		mScissorAnimator->Play(L"ScissorUp", false);
		mScissorAnimator->SetStop(true);
		mLeftCannonAnimator->Play(L"CannonBoilLeft", true);
		mRightCannonAnimator->Play(L"CannonBoilRight", true);
		mMouseAnimator->Play(L"MouseTransitionAEnter"+dir, false);
		mTinFrontAnimator->Play(L"TinFrontIdle" + dir, true);
		mLeftFireAnimator->SetPlayAnimation(nullptr);
		mRightFireAnimator->SetPlayAnimation(nullptr);
	}

	void WernerWermanPh2::TransitionEnterCompleteEvent()
	{
		std::wstring dir;
		if (mbRight)
			dir = L"Right";
		else
			dir = L"Left";
		if (mMouseAnimator->GetPlayAnimation()->GetName() == L"MouseTransitionAEnter" + dir)
			mMouseAnimator->Play(L"MouseTransitionABoil" + dir, true);
		else
			mMouseAnimator->Play(L"MouseTransitionDBoil" + dir, true);
	}

	void WernerWermanPh2::ScissorMoveCompleteEvent()
	{
		mbScissorMove = false;
		if (mScissorAnimator->GetPlayAnimation()->GetName() == L"ScissorUp")
			mScissorAnimator->Play(L"ScissorDown", false);
		else
		{
			if (mHp < 0)
			{
				if (mbRight)
					mMouseAnimator->Play(L"MouseEndRight", true);
				else
					mMouseAnimator->Play(L"MouseEndLeft", true);

				for (size_t i = 0; i < 7; i++)
				{
					for (size_t k = 0; k < 2; k++)
					{
						mDiscs[k][i]->SetFin(true);
					}
				}


			}
			else
			{
				mScissorAnimator->Play(L"ScissorUp", false);
			}
		}
		mScissorAnimator->SetStop(true);
	}


	void WernerWermanPh2::FireCompleteEvent()
	{
		std::wstring dir;
		if (mbRight)
			dir = L"Right";
		else
			dir = L"Left";
		mLeftFireAnimator->SetPlayAnimation(nullptr);
		mRightFireAnimator->SetPlayAnimation(nullptr);
		if (mMouseAnimator->GetPlayAnimation()->GetName() == L"MouseTransitionABoil" + dir)
			mMouseAnimator->Play(L"MouseTransitionDEnter" + dir, true);
		else
			mMouseAnimator->Play(L"MouseTransitionAEnter" + dir, true);
		mbScissorMove = true;
		mFireTimeChecker = 0;
	}

	void WernerWermanPh2::Release()
	{
	}

}