#include "yaWorldMap.h"
#include "yaResources.h"
#include "yaWorldPlayer.h"
#include "yaCamera.h"

namespace ya
{
	WorldMap::WorldMap()
	{
		mBackImage = Resources::Load<Picture>(L"WorldMap_BackImage", L"..\\Resources\\Image\\Map\\PinkMap.png");
	}

	WorldMap::~WorldMap()
	{
	}

	void WorldMap::Tick()
	{
		GameObject::Tick();
		
		Vector2 pos = mWorldPlayer->GetPos();
		Vector2 scale = mWorldPlayer->GetScale();
		Pixel pixelUp = mBackImage->GetPixelImage(pos.x, pos.y-1);
		Pixel pixelRight = mBackImage->GetPixelImage(pos.x+1, pos.y );
		Pixel pixelLeft = mBackImage->GetPixelImage(pos.x-1, pos.y );
		Pixel pixelDown = mBackImage->GetPixelImage(pos.x, pos.y + 1);

		if ((pixelUp.R == 255 && pixelUp.G == 0 && pixelUp.B == 255)
			|| (pixelRight.R == 255 && pixelRight.G == 0 && pixelRight.B == 255)
			|| (pixelLeft.R == 255 && pixelLeft.G == 0 && pixelLeft.B == 255)
			|| (pixelDown.R == 255 && pixelDown.G == 0 && pixelDown.B == 255)
			)
		{
			pos = mWorldPlayer->GetBeforePos();

			if (pixelUp.R == 255 && pixelUp.G == 0 && pixelUp.B == 255)
				pos.y += 1;
			if (pixelRight.R == 255 && pixelRight.G == 0 && pixelRight.B == 255)
				pos.x -= 1;
			if (pixelLeft.R == 255 && pixelLeft.G == 0 && pixelLeft.B == 255)
				pos.x += 1;
			if (pixelDown.R == 255 && pixelDown.G == 0 && pixelDown.B == 255)
				pos.y -= 1;

			mWorldPlayer->SetPos(pos);		
		}
		else			
			mWorldPlayer->SetBeforePos(pos);
	}

	void WorldMap::Render(HDC hdc)
	{
		GameObject::Tick();
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 finalPos = pos;
		finalPos = Camera::CalculatePos(finalPos);
		BitBlt(hdc, finalPos.x, finalPos.y, mBackImage->GetWidth(), mBackImage->GetHeight(), mBackImage->GetDC(), 0, 0, SRCCOPY);
	}

}