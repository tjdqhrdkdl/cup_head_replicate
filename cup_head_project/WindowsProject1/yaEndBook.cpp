#include "yaEndBook.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaApplication.h"
#include "yaTime.h"
namespace ya
{
	EndBook::EndBook()
		:mPage(1)
	{

		SetName(L"EndBook");
		mAnimator = new Animator();
		mArrowAnimator = new Animator();
		AddComponent(mAnimator);
		AddComponent(mArrowAnimator);

		mArrowAnimator->CreateAnimation(L"Arrow", L"..\\Resources\\Image\\Books\\Arrow_", 2, 0.05, false, false);

		mAnimator->CreateAnimation(L"TurnPage_1", L"..\\Resources\\Image\\Books\\End\\Page 13-14\\book_p12b_turn_00", 24, 0.05f, false, false);
		mAnimator->CreateAnimation(L"TurnPage_2", L"..\\Resources\\Image\\Books\\End\\Page 14-15\\book_p13_turn_00", 24, 0.05f, false, false);
		mAnimator->CreateAnimation(L"TurnPage_3", L"..\\Resources\\Image\\Books\\End\\Page 15-16\\book_p14_turn_00", 24, 0.05f, false, false);
		mAnimator->CreateAnimation(L"TurnPage_4", L"..\\Resources\\Image\\Books\\End\\Page 16-17\\book_p15_turn_00", 24, 0.05f, false, false);
		mAnimator->CreateAnimation(L"TurnPage_5", L"..\\Resources\\Image\\Books\\End\\Page 17-18\\book_p16_turn_00", 28, 0.05f, false, false);
		mAnimator->CreateAnimation(L"TurnPage_6", L"..\\Resources\\Image\\Books\\End\\Page 18-End (Outro)\\book_outro_00", 108, 0.05f, false, false);

		mAnimator->GetCompleteEvent(L"TurnPage_1") = std::bind(&EndBook::PageTurnCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"TurnPage_2") = std::bind(&EndBook::PageTurnCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"TurnPage_3") = std::bind(&EndBook::PageTurnCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"TurnPage_4") = std::bind(&EndBook::PageTurnCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"TurnPage_5") = std::bind(&EndBook::PageTurnCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"TurnPage_6") = std::bind(&EndBook::EndCompleteEvent, this);

		mAnimator->Play(L"TurnPage_1", false);
		mAnimator->SetStop(true);
		mArrowAnimator->Play(L"Arrow", true);

		mArrowAnimator->SetAddPos({ 800,-50 });
	}

	EndBook::~EndBook()
	{
	}

	void EndBook::Tick()
	{
		GameObject::Tick();
		if (KEY_DOWN(eKeyCode::Z))
		{
			if (mAnimator->GetPlayAnimation()->haveCompleted())
			{
				std::wstring key = L"TurnPage_" + std::to_wstring(++mPage);
				mAnimator->Play(key, false);
				mAnimator->SetStop(false);
			}
			else
			{
				mAnimator->SetStop(false);
			}
			mArrowAnimator->SetPlayAnimation(nullptr);
		}
		if (mArrowAnimator->GetPlayAnimation() != nullptr)
		{
				if (mbArrowMoveRight)
					mArrowAnimator->SetAddPos({ mArrowAnimator->GetAddPos().x + Time::DeltaTime() * 20, mArrowAnimator->GetAddPos().y });
				else
					mArrowAnimator->SetAddPos({ mArrowAnimator->GetAddPos().x - Time::DeltaTime() * 20, mArrowAnimator->GetAddPos().y });

				if (mArrowAnimator->GetAddPos().x < 595)
					mbArrowMoveRight = true;
				else if (mArrowAnimator->GetAddPos().x > 605)
					mbArrowMoveRight = false;
		}
	}

	void EndBook::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void EndBook::PageTurnCompleteEvent()
	{
		mAnimator->SetStop(true);
		mArrowAnimator->Play(L"Arrow", true);
	}

	void EndBook::EndCompleteEvent()
	{
		DestroyWindow(Application::GetInstance().GetWindowData().hWnd);
	}

}