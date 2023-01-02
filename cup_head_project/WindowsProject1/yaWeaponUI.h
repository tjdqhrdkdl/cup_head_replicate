#pragma once
#include "yaHUD.h"


namespace ya
{
	class Picture;
	class WeaponUI : public HUD
	{
	public:
		WeaponUI(eUIType);
		~WeaponUI();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
		Picture* mPictures[UINT(eGunType::End)];
		eGunType mGunType;

		float mPushTimeChecker;
	};
}
