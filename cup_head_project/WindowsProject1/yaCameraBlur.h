#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Picture;
	class CameraBlur : public GameObject
	{
	public:
		CameraBlur();
		~CameraBlur();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetOn(bool on) { mbOn = on; }

	private:
		bool mbOn;
		Picture* mImage;
	};
}
