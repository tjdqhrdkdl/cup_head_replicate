#include "yaPicture.h"
#include "yaApplication.h"
#include "yaResources.h"


namespace ya
{

	Picture::Picture()
		:mHdc(NULL)
		, mImage(nullptr)
	{}
	Picture::~Picture()
	{
		DeleteDC(mHdc);
		DeleteBitmap();
	}
	HRESULT Picture::Load(const std::wstring& path)
	{
		/*mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str()
				,IMAGE_BITMAP, 0, 0
				,LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
		{
			return E_FAIL;
		}

		BITMAP bitinfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitinfo);

		mWidth = bitinfo.bmWidth;
		mHeight = bitinfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit =  (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);

		return S_OK;*/
		mImage = new Gdiplus::Bitmap(path.c_str());
		mBitmap = nullptr;
		Gdiplus::Status status = mImage->GetHBITMAP(Color(255, 0, 255), &mBitmap);
		if (status != 0)
		{
			MessageBox(nullptr, L"bitmap Load Failed!!!", L"Error", MB_OK);
			return E_FAIL;
		}
		if (mImage->GetLastStatus() != 0)
		{
			return E_FAIL;
		}
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();
		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);

		return S_OK;
	}

	void Picture::FlipX()
	{
		mImage->RotateFlip(RotateFlipType::RotateNoneFlipX);
		Gdiplus::Status status = mImage->GetHBITMAP(Color(255, 0, 255), &mBitmap);
		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);
		mFliped = true;
	}

	void Picture::RotateImage(UINT degree)
	{
		switch (degree)
		{
		case 0:
			return;
			break;
		case 90:
			mImage->RotateFlip(RotateFlipType::Rotate90FlipNone);
			mRotationDegree = degree;
			break;
		case 180:
			mImage->RotateFlip(Rotate180FlipNone);
			mRotationDegree = degree;
			break;
		case 270:
			mImage->RotateFlip(Rotate270FlipNone);
			mRotationDegree = degree;
			break;
		}
		Gdiplus::Status status = mImage->GetHBITMAP(Color(255, 0, 255), &mBitmap);
		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);
	}

	Picture* Picture::Create(const std::wstring& key, UINT width, UINT height)
	{
		Picture* pic = Resources::Find<Picture>(key);
		if (pic != nullptr)
		{
			MessageBox(nullptr, L"중복 키 이미지 생성", L"이미지 생성 실패!", MB_OK);
			return nullptr;
		}
		pic = new Picture();
		Gdiplus::Bitmap* bmp1 = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
		pic->mImage = bmp1;
		Gdiplus::Status status = bmp1->GetHBITMAP(Color(0, 0, 0), &(pic->mBitmap));
		if (status != 0)
		{
			MessageBox(nullptr, L"bitmap Load Failed!!!", L"Error", MB_OK);
			return nullptr;
		}
		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		pic->mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(pic->mHdc, pic->mBitmap);
		DeleteObject(prevBit);

		pic->SetKey(key);
		Resources::Insert<Picture>(key, pic);
		return pic;
	}

	void Picture::DeleteBitmap()
	{
		if (mBitmap != nullptr) {
			DeleteObject(mBitmap);
			DeleteDC(mHdc);
		}

	}	
	Pixel Picture::GetPixelImage(int x, int y)
	{
		COLORREF rgba = GetPixel(mHdc, x, y);

		return Pixel(rgba);	
	}

	void Picture::SetPixel(int x, int y, Pixel pixel)
	{
		// 비트맵 좌표는 촤측하단이 0,0 
		// 윈도우좌표처럼 사용하려면 y를 반대로 바꾸어 주어야 한다.
		y = (UINT)mHeight - (y + 1);

		Pixel* bitmapPixel = (Pixel*)mBitmap;
		bitmapPixel += ((UINT)mWidth * y + x);

		*bitmapPixel = pixel;
	}
}