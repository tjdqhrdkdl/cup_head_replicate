#include "yaHealthUI.h"
#include "yaPicture.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaTime.h"
namespace ya
{
	HealthUI::HealthUI(eUIType type)
		:HUD(type)
	{
		for (size_t i = 0; i < HealthUI_Image_Num; i++)
		{
			std::wstring key = L"HealthUI_IMG" + std::to_wstring(i);
			std::wstring path = L"..\\Resources\\Image\\UI\\HealthUI\\tile00" + std::to_wstring(i) + L".png";
			mPictures[i] = Resources::Load<Picture>(key, path);
		}
		SetPos({ 50,800 });
	}

	HealthUI::~HealthUI()
	{
	}

	void HealthUI::OnInit()
	{
	}

	void HealthUI::OnActive()
	{
	}

	void HealthUI::OnInActive()
	{
		mTarget = nullptr;
	}

	void HealthUI::OnTick()
	{
		if (mTarget != nullptr)
		{
			Player* player = dynamic_cast<Player*>(mTarget);
			mHP = player->GetHP();
			if (mHP == 1)
			{
				mAnimationTimeChecker += Time::DeltaTime();
				if (mAnimationTimeChecker > 0.1)
				{
					mAnimationCounter += 1;
					if (mAnimationCounter == 3)
						mAnimationCounter = 0;
					mAnimationTimeChecker = 0;
				}
			}
		}
	}

	void HealthUI::OnRender(HDC hdc)
	{

		if (mTarget != nullptr)
		{
			if (mHP > 1)
			{
				TransparentBlt(hdc, GetPos().x, GetPos().y,
					mPictures[mHP + 2]->GetWidth(), mPictures[mHP + 2]->GetHeight(),
					mPictures[mHP + 2]->GetDC(), 0, 0, mPictures[mHP + 2]->GetWidth(),
					mPictures[mHP + 2]->GetHeight(), RGB(255, 0, 255));
			}
			else if (mHP == 1)
			{
				TransparentBlt(hdc, GetPos().x, GetPos().y,
					mPictures[mHP + mAnimationCounter]->GetWidth(), mPictures[mHP + mAnimationCounter]->GetHeight(),
					mPictures[mHP + mAnimationCounter]->GetDC(), 0, 0, mPictures[mHP + mAnimationCounter]->GetWidth(),
					mPictures[mHP + mAnimationCounter]->GetHeight(), RGB(255, 0, 255));
			}
			else if (mHP == 0)
			{
				TransparentBlt(hdc, GetPos().x, GetPos().y,
					mPictures[mHP]->GetWidth(), mPictures[mHP]->GetHeight(),
					mPictures[mHP]->GetDC(), 0, 0, mPictures[mHP]->GetWidth(),
					mPictures[mHP]->GetHeight(), RGB(255, 0, 255));
			}
		}
	}

	void HealthUI::OnClear()
	{
	}

}