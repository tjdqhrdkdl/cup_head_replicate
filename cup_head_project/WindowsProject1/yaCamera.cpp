#include "yaCamera.h"
#include "yaApplication.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaPicture.h"

namespace ya
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	eCameraEffect Camera::mEffect = eCameraEffect::None;;
	Picture* Camera::mCutton = nullptr;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mCuttonAlpha = 0.0f;
	float Camera::mEndTime = 5.0f;

	void Camera::Initialize()
	{
		WindowData data = Application::GetInstance().GetWindowData();
		mResolution = Vector2(data.width, data.height);
		mLookPosition = (mResolution / 2.0f);

		//mEffect = eCameraEffect::FadeOut;
		mCutton = Picture::Create(L"CameraCutton", 1600, 900);
	}

	void Camera::Tick()
	{
		if (mAlphaTime <= mEndTime)
		{
			mAlphaTime += Time::DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (eCameraEffect::FadeIn == mEffect)
			{
				mCuttonAlpha = 1.0f - ratio;
			}
			else if (eCameraEffect::FadeOut == mEffect)
			{
				mCuttonAlpha = ratio;
			}
		}


		if (KEY_PRESSED(eKeyCode::NUM_8))
		{
			mLookPosition.y -= 600.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::NUM_2))
		{
			mLookPosition.y += 600.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::NUM_4))
		{
			mLookPosition.x -= 600.0f * Time::DeltaTime();
		}
		if (KEY_PRESSED(eKeyCode::NUM_6))
		{
			mLookPosition.x += 600.0f * Time::DeltaTime();
		}


		if (mTarget != nullptr)
		{
			mLookPosition = mTarget->GetPos();
			Vector2 pos = mTarget->GetPos();
			if (pos.x < 800)
				mLookPosition.x = 800;
			else if(pos.x >3200)
				mLookPosition.x = 3200;
			if(pos.y <470)
				mLookPosition.y = 470;
			else if (pos.y > 1850)
				mLookPosition.y = 1850;
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		if (mCuttonAlpha >= 1.0f)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		AlphaBlend(hdc, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, mCutton->GetDC(), 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, func);
	}
}