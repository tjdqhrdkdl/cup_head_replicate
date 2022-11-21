#pragma once
#include "yaGameObject.h"
#include "yaShootEffect.h"
namespace ya {

	class Bullet : public GameObject
	{
	public:
		Bullet(Vector2 dir, bool special = false);
		~Bullet();

		void SetDir(Vector2 vec) { mDir = vec; }
		Vector2 GetDir() { return mDir; }
		void SetDamage(float dmg) { mDamage = dmg; }
		float GetDamage() { return mDamage; }
		ShootEffect* GetShootEffect() { return mEffect; }
		Animator* GetAnimator() { return mAnimator; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void BulletDeathCompleteEvent();
	protected:
		bool mSpecial;
		Vector2 mDir;
		float mDamage;
		ShootEffect* mEffect;

		Animator* mAnimator;
	};
}
