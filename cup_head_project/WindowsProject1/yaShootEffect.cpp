#include "yaShootEffect.h"
#include "yaAnimator.h"
#include "yaObjectManager.h"
#include "yaCollider.h"
namespace ya 
{

	ShootEffect::ShootEffect()
	{
		SetName(L"ShootEffect");
		SetScale({ 100,100 });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
	}

	ShootEffect::~ShootEffect()
	{
	}

	void ShootEffect::Tick()
	{
		GameObject::Tick();
	}

	void ShootEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ShootEffect::ShootEffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

}