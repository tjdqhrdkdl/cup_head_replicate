#pragma once
#include "yaHUD.h"
#define HealthUI_Image_Num 11


namespace ya 
{
	class Picture;
	class HealthUI : public HUD
	{
	public:
		HealthUI(eUIType);
		~HealthUI();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
		Picture* mPictures[HealthUI_Image_Num];
		UINT mHP;

		float mAnimationTimeChecker;
		UINT mAnimationCounter;
	};
}
