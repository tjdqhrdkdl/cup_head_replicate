#include "yaBgImageObject.h"
#include "yaResources.h"
#include "yaCamera.h"
namespace ya {

	BgImageObject::BgImageObject()
		:mImage(nullptr)
		, mbOff(false)
	{
	}

	BgImageObject::~BgImageObject()
	{
	}



	void BgImageObject::Tick()
	{
		GameObject::Tick();
	}

	void BgImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 finalPos = pos;

		finalPos = Camera::CalculatePos(finalPos);
		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;
		
		
		if (!mbOff) 
		{
			if (mIsTransparent)
			{
				TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
					, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
					, mColor);

			}
			else
				BitBlt(hdc, finalPos.x, finalPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetDC(), 0, 0, SRCCOPY);
		}
		GameObject::Render(hdc);
	}

	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& fileName,UINT color, bool isTransparent)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Picture>(key, path);
		mIsTransparent = isTransparent;
		mColor = color;

	}
}