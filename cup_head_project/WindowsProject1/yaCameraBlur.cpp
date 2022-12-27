#include "yaCameraBlur.h"
#include "yaPicture.h"
#include "yaResources.h"


namespace ya 
{
	CameraBlur::CameraBlur()
	{
		mImage = Resources::Load<Picture>(L"UICameraBlur", L"..\\Resources\\Image\\UI\\PlayScene\\CameraBlur.png");
	}

	CameraBlur::~CameraBlur()
	{
	}

	void CameraBlur::Tick()
	{
		if (mbOn)
			GameObject::Tick();
	}

	void CameraBlur::Render(HDC hdc)
	{
		if (mbOn)
		{
			GameObject::Render(hdc);

			Graphics graphic(hdc);


			graphic.DrawImage(
				mImage->GetImage()
				, 0, 0
				, mImage->GetWidth()
				, mImage->GetHeight());
		}
	}

}