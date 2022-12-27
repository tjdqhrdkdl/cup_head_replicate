#pragma once
#include "Common.h"
#include "yaComponent.h"
namespace ya
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetScale(Vector2 scale) { mScale = scale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetOffset(Vector2 pos) { mOffset = pos; }
		void SetOff(bool off) { mOff = off; }
		void SetHitBox(bool off) { misHitBox = off; }
		void SetBulletPassing(bool off) { misBulletPassing = off; }
		void SetAddPos(Vector2 pos) { mAddPos = pos; }
		void SetDanger(bool off) { misDanger = off; }
		Vector2 GetAddPos() { return mAddPos; }
		Vector2 GetPos() { return mPos; }
		Vector2 GetOffset() { return mOffset; }
		Vector2 GetScale() { return mScale; }
		bool isOff() { return mOff; }

		bool isHitBox() { return misHitBox; }
		bool isDanger() { return misDanger; }
		bool isBulletPassing() { return misBulletPassing; }
		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);
	private:
		Vector2 mPos;
		Vector2 mAddPos;
		Vector2 mOffset;
		Vector2 mScale;
		UINT mCollisionCount;

		bool mOff;
		bool misHitBox;
		bool misBulletPassing;
		bool misDanger;
	};
}
