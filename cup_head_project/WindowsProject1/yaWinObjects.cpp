#include "yaWinObjects.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaResources.h"

namespace ya
{
	WinObjects::WinObjects()
	{
		SetName(L"WinObjects");
		mCupheadAnimator = new Animator();
		mBoardAnimator = new Animator();
		mTitleAnimator = new Animator();
		mCircleAnimator = new Animator();

		AddComponent(mBoardAnimator);
		AddComponent(mTitleAnimator);
		AddComponent(mCupheadAnimator);
		AddComponent(mCircleAnimator);

		mBoardAnimator->CreateAnimation(L"WinBoard", L"..\\Resources\\Image\\WinScreen\\Board\\winscreen_board_", 2, 0.08f, false, false, { 250,-100 });
		mTitleAnimator->CreateAnimation(L"WinTitle", L"..\\Resources\\Image\\WinScreen\\The Results\\English\\A\\winscreen_results_title_a_00", 4, 0.06f, false, false, { 0,-700 });
		mCupheadAnimator->CreateAnimation(L"WinCuphead", L"..\\Resources\\Image\\WinScreen\\Cuphead\\Idle\\winscreen_ch_00", 8, 0.08f, false, false, { -350,-100 });
		mCircleAnimator->CreateAnimation(L"WinCircle", L"..\\Resources\\Image\\WinScreen\\Circle Mark\\winscreen_circle_00", 13, 0.08f, false, false, { 300,-150 });

		mBoardAnimator->Play(L"WinBoard", true);
		mTitleAnimator->Play(L"WinTitle", true);
		mCupheadAnimator->Play(L"WinCuphead", true);
	}

	WinObjects::~WinObjects()
	{
	}

	void WinObjects::Tick()
	{
		GameObject::Tick();
	}

	void WinObjects::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}