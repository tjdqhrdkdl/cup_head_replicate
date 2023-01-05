#include "yaNumber.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSound.h"
namespace ya
{
	Number::Number()
		:mStopIndex(20)
	{
		SetName(L"WinNumber");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"WinNumberAnim", L"..\\Resources\\Image\\WinScreen\\Number\\", 10, 0.05f, true, false)
			, mAnimator->CreateAnimation(L"LightenWinNumberAnim", L"..\\Resources\\Image\\WinScreen\\Number\\Lighten\\", 10, 0.05f, true, false)
		);
		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"WinCharAnim", L"..\\Resources\\Image\\WinScreen\\Number\\L_", 5, 0.05f, true, false)
			, mAnimator->CreateAnimation(L"LightenWinCharAnim", L"..\\Resources\\Image\\WinScreen\\Number\\Lighten\\L_", 5, 0.05f, true, false)
		);
		mAnimator->Play(L"WinNumberAnim", false);
		mAnimator->SetStop(true);

		
	}

	Number::~Number()
	{
	}

	void Number::Tick()
	{
		GameObject::Tick();
		if (mAnimator->GetPlayAnimation()->GetIndex() >= mStopIndex)
		{
			mbFin = true;
		}
	}

	void Number::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}