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

		void SetImage(const std::wstring& key,const std::wstring& path);
	private:
		Picture* mImage;
	};
}
