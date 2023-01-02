#include "yaWeaponUI.h"
#include "yaPicture.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaUIManager.h"

namespace ya
{
	WeaponUI::WeaponUI(eUIType type)
		:HUD(type)
	{
		SetPos({ 90,820 });
		SetName(L"WeaponUI");
		mPictures[UINT(eGunType::PeaShooter)] = Resources::Load<Picture>(L"Equip_PeaShooter", L"..\\Resources\\Image\\UI\\Equip\\equip_icon_weapon_peashot_0001.png");
		mPictures[UINT(eGunType::CrackShot)] = Resources::Load<Picture>(L"Equip_CrackShot", L"..\\Resources\\Image\\UI\\Equip\\equip_icon_weapon_crackshot_0001.png");
		mPictures[UINT(eGunType::Spreader)] = Resources::Load<Picture>(L"Equip_Spreader", L"..\\Resources\\Image\\UI\\Equip\\equip_icon_weapon_spread_0001.png");

	}

	WeaponUI::~WeaponUI()
	{
	}

	void WeaponUI::OnInit()
	{
	}

	void WeaponUI::OnActive()
	{
	}

	void WeaponUI::OnInActive()
	{
		mPushTimeChecker = 0;
	}

	void WeaponUI::OnTick()
	{
		mPushTimeChecker += Time::DeltaTime();
		mGunType = dynamic_cast<Player*>(mTarget)->GetGunType();
		if (mPushTimeChecker > 1.75)
		{
			InActive();
		}
	}

	void WeaponUI::OnRender(HDC hdc)
	{
		float finalHeight;
		if (mPushTimeChecker < 0.25)
		{
			finalHeight = 320 * mPushTimeChecker;
		}
		else if (mPushTimeChecker > 0.25 && mPushTimeChecker < 1.5)
		{
			finalHeight = 80;
		}
		else
		{
			finalHeight = 80 - 320 * (mPushTimeChecker - 1.5);
			if (finalHeight < 0)
				finalHeight = 0;
		}


		if (mTarget != nullptr)
		{
			TransparentBlt(hdc, GetPos().x - (mPictures[UINT(mGunType)]->GetWidth() / 2), GetPos().y - finalHeight,
				mPictures[UINT(mGunType)]->GetWidth(),finalHeight,
				mPictures[UINT(mGunType)]->GetDC(), 0, 0, mPictures[UINT(mGunType)]->GetWidth(),
				finalHeight, RGB(255, 0, 255));
		}
	}

	void WeaponUI::OnClear()
	{
	}

}