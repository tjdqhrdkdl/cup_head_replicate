#pragma once
#include "yaUiBase.h"

namespace ya
{
	class Button : public UiBase
	{
	public:
		Button(eUIType type);
		~Button();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		virtual void Click();

		void SetClickImage(const std::wstring& key, const std::wstring& path);
		std::function<void()>& GetOnClickEvent() { return mOnClick.mEvent; };

	private:
		Event mOnClick;
		bool mbMouseOn;
		Picture* mClickImage;
	};

}