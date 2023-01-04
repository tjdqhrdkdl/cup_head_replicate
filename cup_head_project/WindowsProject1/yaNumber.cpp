#include "yaNumber.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"

namespace ya
{
	Number::Number()
		:mStopIndex(20)
	{
		SetName(L"WinNumber");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->SetLightenAnimation(
			mAnimator->CreateAnimation(L"WinNumberAnim", L"..\\Resources\\Image\\WinScreen\\Number\\", 16, 0.05f, true, false)
			, mAnimator->CreateAnimation(L"LightenWinNumberAnim", L"..\\Resources\\Image\\WinScreen\\Number\\Lighten\\", 16, 0.05f, true, false)
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