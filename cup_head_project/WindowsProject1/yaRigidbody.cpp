#include "yaGameObject.h"
#include "yaRigidbody.h"
#include "yaTime.h"

namespace ya
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(100.0f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 3000000.f;
		mbGround = false;
		mGravity = Vector2(0.0f, 5000.0f);
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Tick()
	{
		//�̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ������ ������
			mVelocity = Vector2::Zero;
		}
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}


		// �ִ� �ӵ� ����
		//Vector2 gravity = mGravity;
		//gravity.Normalize();
		//float dot = ya::math::Dot(mVelocity, gravity);
		//gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitVelocity.y;
		//}

		//if (mLimitVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitVelocity.x;
		//}
		//mVelocity = gravity + sideVelocity;

		////������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// �ӵ��� �ݴ� �������� �������� ����
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

		//	// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		// �ӵ��� 0 �� �����.
		//		mVelocity = Vector2(0.f, 0.f);
		//	}
		//	else
		//	{
		//		// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
		//		mVelocity += friction;
		//	}
		//}

		// �ӵ��� �°� ��ü�� �̵���Ų��.
		Vector2 pos = GetOwner()->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();
		GetOwner()->SetPos(pos);
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{

	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}

}
