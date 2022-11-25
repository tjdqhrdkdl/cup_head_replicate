#pragma once
#include "yaHUD.h"
#define HealthUI_Image_Num 11


namespace ya
{
	class Picture;
	class EXPointUI : public HUD
	{
	public:
		EXPointUI(eUIType);
		~EXPointUI();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
		Picture* mPictures[5];
		Picture* mBasePicture;
		UINT mPoint;
		float mFloatPoint;
	};
}
