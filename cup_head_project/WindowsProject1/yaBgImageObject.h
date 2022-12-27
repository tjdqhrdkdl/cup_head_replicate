#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya {

	class BgImageObject : public GameObject
	{
	public:
		BgImageObject();
		~BgImageObject();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key,const std::wstring& path, UINT color = RGB(255,0,255), bool isTransparent = false);

		void SetOff(bool off) { mbOff = off; }

	private:
		Picture* mImage;
		bool mbOff;
		bool mIsTransparent;
		UINT mColor;
	};
}
