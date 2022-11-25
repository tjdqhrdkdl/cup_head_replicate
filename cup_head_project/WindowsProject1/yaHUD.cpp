#include "yaHUD.h"
#include "yaPicture.h"
#include "yaPlayer.h"

namespace ya
{
	HUD::HUD(eUIType type)
		: UiBase(type)
	{
	}
	HUD::~HUD()
	{
	}
	void HUD::OnInit()
	{
	}
	void HUD::OnActive()
	{
	}
	void HUD::OnInActive()
	{

	}
	void HUD::OnTick()
	{
	}

	void HUD::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		if (mTarget == nullptr)
			return;
	}

	void HUD::OnClear()
	{

	}
}
