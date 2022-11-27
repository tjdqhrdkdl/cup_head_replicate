#include "yaAnimation.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaCamera.h"
#include "yaTime.h"
namespace ya 
{
	Animation::Animation()
	{
	}

	Animation::~Animation()
	{

	}

	void Animation::Tick()
	{
		if (mComplete)
			return;


		mTime += Time::DeltaTime();
		if (mTime > mPictureDuration)
		{
			mTime = 0.0f;
			if (mPictureIndex >= mPictures.size() - 1)
				mComplete = true;
			else
				++mPictureIndex;
		}
	}

	void Animation::Render(HDC hdc)
	{
		GameObject* gameObj = mAnimator->GetOwner();
		Vector2 pos = gameObj->GetPos();
		
		Vector2 finalPos;
		finalPos.x = pos.x - (mPictures[mPictureIndex]->GetWidth() / 2) + mFixPos.x;
		finalPos.y = pos.y - (mPictures[mPictureIndex]->GetHeight()) + mFixPos.y	;
		
		Vector2 rect;
		rect.x = mPictures[mPictureIndex]->GetWidth();
		rect.y = mPictures[mPictureIndex]->GetHeight();

		if (mAffectedCamera)
			finalPos = Camera::CalculatePos(finalPos);

		Graphics graphic(hdc);
		if (mbHaveAlpha)
		{
			Gdiplus::ColorMatrix matrix = mAnimator->GetMatrix();
			Gdiplus::ImageAttributes attr;
			attr.SetColorMatrix(&matrix,
				Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

			Gdiplus::RectF rect(finalPos.x,finalPos.y,
				mPictures[mPictureIndex]->GetWidth(),
				mPictures[mPictureIndex]->GetHeight());
			
			graphic.DrawImage(
				mPictures[mPictureIndex]->GetImage()
				,rect
				, 0, 0
				, mPictures[mPictureIndex]->GetWidth()
				, mPictures[mPictureIndex]->GetHeight()
				, Gdiplus::UnitPixel, &attr);
		}
		else
		{
			if (mAnimator->isLighten())
			{
				TransparentBlt(hdc, finalPos.x, finalPos.y,
					mLightenAnimation->mPictures[mPictureIndex]->GetWidth(), mLightenAnimation->mPictures[mPictureIndex]->GetHeight(),
					mLightenAnimation->mPictures[mPictureIndex]->GetDC(), 0, 0, mLightenAnimation->mPictures[mPictureIndex]->GetWidth(),
					mLightenAnimation->mPictures[mPictureIndex]->GetHeight(), RGB(255, 0, 255));
			}
			else
			{
				TransparentBlt(hdc, finalPos.x, finalPos.y,
					mPictures[mPictureIndex]->GetWidth(), mPictures[mPictureIndex]->GetHeight(),
					mPictures[mPictureIndex]->GetDC(), 0, 0, mPictures[mPictureIndex]->GetWidth(),
					mPictures[mPictureIndex]->GetHeight(), RGB(255, 0, 255));
			}
		}
	}

	void Animation::Reset()
	{
		mTime = 0;
		mComplete = false;
		mPictureIndex = 0;
		mbHaveCompleted = false;
	}

	void Animation::Create(const std::wstring& key, const std::wstring& path
		, UINT imageNum, float duration, bool imageReversed, bool fromZero ,Vector2 fixPos,  bool bAffectedCamera , bool haveAlpha, UINT imageDegree)
	{
		size_t i = 0;
		if (fromZero == false)
			i = 1;
		for (; i < imageNum && i < 100; i++)
		{
			std::wstring addInfo = L"";
			if (i >= 10)
				addInfo = std::to_wstring(i) + L".png";
			else
				addInfo = L"0" + std::to_wstring(i) + L".png";
			

			Picture* pic = Resources::Load<Picture>(key + addInfo, path + addInfo);
			if (imageReversed && !(pic->isFliped()))
			{
				pic->FlipX();
			}
			if (pic->GetRotationDegree() != imageDegree)
				pic->RotateImage(imageDegree);
			mPictures.push_back(pic);
		}
		mPictureDuration = duration	;
		mAffectedCamera = bAffectedCamera;
		mbHaveAlpha = haveAlpha;
		mFixPos = fixPos;
	}
	
}