#include "yaEXPointUI.h"
#include "yaPlayer.h"
#include "yaPicture.h"
#include "yaResources.h"

namespace ya
{
	EXPointUI::EXPointUI(eUIType type)
		:HUD(type)
	{
		for (size_t i = 1; i < 6; i++)
		{
			std::wstring key = L"EXPointUI_IMG" + std::to_wstring(i);
			std::wstring path = L"..\\Resources\\Image\\UI\\EXPoint\\wizard_peashot_card_pink_a_000" + std::to_wstring(i) + L".png";
			mPictures[i-1] = Resources::Load<Picture>(key, path);
		}
		mBasePicture = mPictures[0];
		SetPos({ 140, 800 });
	}

	EXPointUI::~EXPointUI()
	{
	}

	void EXPointUI::OnInit()
	{
	}

	void EXPointUI::OnActive()
	{
	}

	void EXPointUI::OnInActive()
	{
	}

	void EXPointUI::OnTick()
	{
		if (mTarget != nullptr)
		{
			Player* player = dynamic_cast<Player*>(mTarget);
			mPoint = player->GetSpecialPoint();
			mFloatPoint = player->GetSpecialPointFloat();
		}
	}

	void EXPointUI::OnRender(HDC hdc)
	{
		if (mTarget != nullptr)
		{
			for (size_t i = 0; i < mPoint; i++)
			{
				TransparentBlt(hdc, GetPos().x + i * 26, GetPos().y,
					mBasePicture->GetWidth(), mBasePicture->GetHeight(),
					mBasePicture->GetDC(), 0, 0, mBasePicture->GetWidth(),
					mBasePicture->GetHeight(), RGB(255, 0, 255));
			}

			TransparentBlt(hdc, GetPos().x + mPoint * 26, GetPos().y,
				mBasePicture->GetWidth(), mBasePicture->GetHeight() * mFloatPoint,
				mBasePicture->GetDC(), 0, 0, mBasePicture->GetWidth(),
				mBasePicture->GetHeight() * mFloatPoint, RGB(255, 0, 255));
		}
	}

	void EXPointUI::OnClear()
	{
	}

}