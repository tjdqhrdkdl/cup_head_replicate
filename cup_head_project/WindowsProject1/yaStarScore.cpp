#include "yaStarScore.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSound.h"
namespace ya
{
	StarScore::StarScore()
	{
		SetName(L"StarScore");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"WinStarScoreAnim", L"..\\Resources\\Image\\WinScreen\\Star\\winscreen_star_appear_00", 10, 0.06f, true, false);
	
		mAnimator->Play(L"WinStarScoreAnim", false);
		mAnimator->SetStop(true);

		mSound = Resources::Load<Sound>(L"AwardPingSound", L"..\\Resources\\Sound\\Win\\win_award_ping_01.wav");

	}
	StarScore::~StarScore()
	{
	}

	void StarScore::playsound()
	{
		mSound->Play(false);
	}
	void StarScore::Tick()
	{
		GameObject::Tick();


	}
	void StarScore::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
}
