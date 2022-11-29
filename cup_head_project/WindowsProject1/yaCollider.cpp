#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaCamera.h"
namespace ya {
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
		, mCollisionCount(0)
		, misHitBox(true)
		, misDanger(true)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
		if (mScale == Vector2::One)
			mScale = GetOwner()->GetScale();
	}

	void Collider::Tick()
	{ 
		GameObject* owner = GetOwner();
		mPos = Vector2(owner->GetPos().x, owner->GetPos().y - owner->GetScale().y / 2) + mAddPos;
	
	}

	void Collider::Render(HDC hdc)
	{
		if (!mOff)
		{
			HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
			Brush brush(hdc, tr);

			HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oldPen = NULL;

			if (mCollisionCount > 0)
				oldPen = (HPEN)SelectObject(hdc, redPen);
			else
				oldPen = (HPEN)SelectObject(hdc, greenPen);
			Vector2 finalPos;
			finalPos.x = mPos.x - mScale.x / 2.0f;
			finalPos.y = mPos.y - mScale.y / 2.0f;
			finalPos = Camera::CalculatePos(finalPos);
			Rectangle(hdc, finalPos.x, finalPos.y
				, finalPos.x + mScale.x, finalPos.y + mScale.y);
			SelectObject(hdc, oldPen);

			DeleteObject(redPen);
			DeleteObject(greenPen);
		}
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		mCollisionCount++;
		GetOwner()->OnCollisonEnter(other, this);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisonStay(other, this);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		mCollisionCount--;
		GetOwner()->OnCollisonExit(other, this);
	}
}