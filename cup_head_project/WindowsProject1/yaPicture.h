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
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		void FlipX();
		void RotateImage(UINT degree);
		UINT GetRotationDegree() { return mRotationDegree; }
		bool isFliped() { return mFliped; }
		Gdiplus::Bitmap* GetImage() { return mImage; }
		static Picture* Create(const std::wstring& key, UINT width, UINT height);


		void DeleteGDIPlusImage() { 
			if (mImage != nullptr && (mbDeletedGDIPlusImage == false)) 
			{
				delete mImage;
				mImage = nullptr;
				mbDeletedGDIPlusImage = true;
			}
			
		}
		
		void DeleteBitmap();
		



		bool mbDeletedGDIPlusImage;
	private:
		HBITMAP mBitmap;
		HDC mHdc;
		Gdiplus::Bitmap* mImage;

		float mWidth;
		float mHeight;

		UINT mRotationDegree;
		bool mFliped;
	};
}
