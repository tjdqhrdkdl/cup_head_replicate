#include "yaBgImageObject.h"
#include "yaResources.h"

namespace ya {

	BgImageObject::BgImageObject()
		:mImage(nullptr)
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

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		//BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetDC(), mImage->GetWidth(), mImage->GetHeight(), 0);
		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));
		GameObject::Render(hdc);
	}

	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Picture>(key, path);

	}
}