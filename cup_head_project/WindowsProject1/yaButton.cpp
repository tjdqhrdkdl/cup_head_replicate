#include "yaButton.h"
#include "yaPicture.h"
#include "yaInput.h"
#include "yaResources.h"
namespace ya
{
	Button::Button(eUIType type)
		: UiBase(type)
	{
		mOnClick = std::bind(&Button::Click, this);
	}
	Button::~Button()
	{

	}

	void Button::OnInit()
	{

	}

	void Button::OnActive()
	{

	}

	void Button::OnInActive()
	{
	}

	void Button::OnTick()
	{
		Vector2 mousePos = Input::GetMousePos();
		Vector2 size = GetSize();

		if (mScreenPos.x <= mousePos.x && mousePos.x < mScreenPos.x + size.x
			&& mScreenPos.y <= mousePos.y && mousePos.y < mScreenPos.y + size.y)
		{
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}

		if (mbMouseOn)
		{
			mOnClick();
		}
	}

	void Button::OnRender(HDC hdc)
	{

		if(mbMouseOn)
		{
			TransparentBlt(hdc, (int)mScreenPos.x, (int)mScreenPos.y,
				mClickImage->GetWidth(), mClickImage->GetHeight(),
				mClickImage->GetDC(), 0, 0, mClickImage->GetWidth(),
				mClickImage->GetHeight(), RGB(255, 0, 255));
		}
		else {
			TransparentBlt(hdc, (int)mScreenPos.x, (int)mScreenPos.y,
				mImage->GetWidth(), mImage->GetHeight(),
				mImage->GetDC(), 0, 0, mImage->GetWidth(),
				mImage->GetHeight(), RGB(255, 0, 255));
		}
	}

	void Button::OnClear()
	{

	}

	void Button::Click()
	{
		
	}
	void Button::SetClickImage(const std::wstring& key, const std::wstring& path)
	{
		mClickImage = Resources::Load<Picture>(key, path);

		SetSize(Vector2(mClickImage->GetWidth(), mClickImage->GetHeight()));
	}
}
