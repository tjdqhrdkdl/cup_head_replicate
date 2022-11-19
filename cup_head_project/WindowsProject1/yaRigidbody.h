#pragma once
#include "yaComponent.h"

namespace ya
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void Initialize() override;
		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool isGround() { return mbGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetGravity(Vector2 gravity) { mGravity = gravity; }
	private:
		// ���� �������� �̿��� �̵�
		float mMass;
		float mFriction;
		//float mMoveFriction;
		Vector2 mForce;
		Vector2 mVelocity;
		Vector2 mAccelation;

		// �߷� �̿��� ����
		Vector2 mGravity;
		bool mbGround;
		Vector2 mLimitVelocity;
	};
}