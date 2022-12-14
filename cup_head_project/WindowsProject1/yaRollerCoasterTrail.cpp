#include "yaRollerCoasterTrail.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaObjectManager.h"
namespace ya
{
	RollerCoasterTrail::RollerCoasterTrail(bool blue, bool person, bool init)
		:
		mAliveTime(13.0f)
		, mAliveTimeChecker(0)
	{
		
		SetName(L"CoasterTrail");
		SetScale({ 270,170 });
		misBlue = blue;
		mWithPassenger = person;
		mBackAnimator = new Animator();
		mFrontAnimator = new Animator();
		mChairAnimator = new Animator();
		mPersonXAnimator1 = new Animator();
		mPersonYAnimator1 = new Animator();
		mPersonXAnimator2 = new Animator();
		mPersonYAnimator2 = new Animator();
		AddComponent(mBackAnimator);
		AddComponent(mChairAnimator);
		AddComponent(mPersonXAnimator1);
		AddComponent(mPersonYAnimator1);
		AddComponent(mPersonYAnimator2);
		AddComponent(mPersonXAnimator2);
		AddComponent(mFrontAnimator);

		mBackAnimator->CreateAnimation(L"TrailBack", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Midcart2_", 3, 0.1f, true, false);
		mFrontAnimator->CreateAnimation(L"TrailFrontBlue", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Midcart_Blue_", 3, 0.1f, true, false,{28,27});
		mFrontAnimator->CreateAnimation(L"TrailFrontRed", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Midcart_Red_", 3, 0.1f, true, false, { 28,27 });
		mChairAnimator->CreateAnimation(L"TrailChair", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Seat_", 3, 0.1f, true, false);
		mPersonXAnimator1->CreateAnimation(L"TrailPersonX", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Passenger_", 8, 0.04f, true, false, { -90,-36 });
		mPersonYAnimator1->CreateAnimation(L"TrailPersonY", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_PassengerY_", 8, 0.04f, true, false, { -65,-5 });
		mPersonXAnimator2->CreateAnimation(L"TrailPersonX", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Passenger_", 8, 0.04f, true, false, { 55,-5 });
		mPersonYAnimator2->CreateAnimation(L"TrailPersonY", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_PassengerY_", 8, 0.04f, true, false, { 30, -30 });
		if (mWithPassenger)
		{
			AddComponent(new Collider());
			mChairAnimator->Play(L"TrailChair", true);
			mPersonXAnimator1->Play(L"TrailPersonX", true);
			mPersonYAnimator1->Play(L"TrailPersonY", true);
			mPersonXAnimator2->Play(L"TrailPersonX", true);
			mPersonYAnimator2->Play(L"TrailPersonY", true);

		}
		mBackAnimator->Play(L"TrailBack", true);
		if (misBlue)
			mFrontAnimator->Play(L"TrailFrontBlue", true);
		else
			mFrontAnimator->Play(L"TrailFrontRed", true);

	}

	RollerCoasterTrail::~RollerCoasterTrail()
	{
	}

	void RollerCoasterTrail::Tick()
	{
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
			ObjectManager::Destroy(this);
		GameObject::Tick();

	}

	void RollerCoasterTrail::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RollerCoasterTrail::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void RollerCoasterTrail::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void RollerCoasterTrail::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void RollerCoasterTrail::Release()
	{
		mBackAnimator->Release();
		mChairAnimator->Release();
		mPersonXAnimator1->Release();
		mPersonYAnimator1->Release();
		mFrontAnimator->Release();
	}

}