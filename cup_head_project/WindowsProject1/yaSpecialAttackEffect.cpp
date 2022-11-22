#include "yaSpecialAttackEffect.h"


namespace ya
{
	SpecialAttackEffect::SpecialAttackEffect(Vector2 dir)
	{
		mDir = dir;
		SetName(L"SpecialAttackEffect");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"BoomRight", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, false, { 0,200 });
		mAnimator->CreateAnimation(L"BoomLeft", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, true, { 0,200 });
		mAnimator->CreateAnimation(L"BoomUp", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, false, { 0,200 }, true, false, 270);
		mAnimator->CreateAnimation(L"BoomDown", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, false, { 0,200 }, true, false, 90);
		mAnimator->CreateAnimation(L"BoomRightUp", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, false, { 0,200 });
		mAnimator->CreateAnimation(L"BoomLeftUp", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, true, { 0,200 });
		mAnimator->CreateAnimation(L"BoomRightDown", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, false, { 0,200 }, true, false, 270);
		mAnimator->CreateAnimation(L"BoomLeftDown", L"..\\Resources\\Image\\Cuphead\\Special Attck\\SFX\\Sprite\\A\\weapon_ex_dust_a_00", 21, 0.03f, false, false, { 0,200 }, true, false, 90);
		std::wstring dirStr = mDir.GetDirInStr();
		mAnimator->Play(L"Boom"+dirStr, false);
		mAnimator->GetCompleteEvent(L"BoomRight") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomLeft") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomUp") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomDown") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomRightUp") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomRightDown") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomLeftUp") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"BoomLeftDown") = std::bind(&SpecialAttackEffect::EffectCompleteEvent, this);

	}

	SpecialAttackEffect::~SpecialAttackEffect()
	{
	}

	void SpecialAttackEffect::Tick()
	{
		GameObject::Tick();
	}

	void SpecialAttackEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SpecialAttackEffect::EffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

}