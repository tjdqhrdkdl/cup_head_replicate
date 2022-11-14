#pragma once
#include "yaResource.h"

namespace ya 
{
	class Picture: public Resource
	{
	public:
		Picture();
		~Picture();
		virtual HRESULT Load(const std::wstring& path) override;
		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return mImage->GetWidth(); }
		UINT GetHeight() { return mImage->GetHeight(); }
		void FlipX();
		void RotateImage(UINT degree);
		UINT GetRotationDegree() { return mRotationDegree; }
		bool isFliped() { return mFliped; }
		Gdiplus::Bitmap* GetImage() { return mImage; }
		static Picture* Create(const std::wstring& key, UINT width, UINT height);
		static void _forceinline DrawLightenImage(Graphics* graphic, Picture* mImage, Vector2 pos)
		{

			Gdiplus::ColorMatrix matrix = {

				 1.0f,    0.0f,    0.0f,    0.0f,    0.0f,

				 0.0f,    1.0f,    0.0f,    0.0f,    0.0f,

				 0.0f,    0.0f,    1.0f,    0.0f,    0.0f,

				 0.0f,    0.0f,    0.0f,    1.0f,    0.0f,

				 0.2f, 0.2f, 0.2f, 0.0f,    1.0f

			};
			Gdiplus::ImageAttributes attr;
			attr.SetColorMatrix(&matrix,
				Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

			Gdiplus::RectF rect(
				pos.x,
				pos.y,
				mImage->GetWidth(),
				mImage->GetHeight());
			graphic->DrawImage(mImage->GetImage(), rect, 0, 0, mImage->GetWidth(), mImage->GetHeight(), Gdiplus::UnitPixel, &attr);
		}

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		Gdiplus::Bitmap* mImage;
		UINT mRotationDegree;
		bool mFliped;
	};
}
