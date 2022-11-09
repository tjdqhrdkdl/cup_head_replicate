#pragma once
#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>

#include "def.h"
#include "Maths.h"


#pragma comment(lib, "Msimg32.lib")
#include <ole2.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
class WindowData
{
public:
	HWND hWnd;
	HDC hdc;
	HBITMAP backTexture;
	HDC backBuffer;
	UINT height;
	UINT width;

	void clear()
	{
		hWnd = nullptr;
		hdc = nullptr;
		backTexture = nullptr;
		backBuffer = nullptr;
		height = 0;
		width = 0;
	}
private:
	
};
namespace ya {
	class Pen
	{
	public:
		Pen(HDC hdc, HPEN hpen, bool _del = true)
		{
			mHdc = hdc;
			bDel = _del;
			mOldPen = (HPEN)SelectObject(mHdc, hpen);
		}
		~Pen()
		{
			if (bDel)
				DeleteObject(SelectObject(mHdc, mOldPen));
			else
				SelectObject(mHdc, mOldPen);
		}
	private:
		HDC mHdc;
		HPEN mOldPen;
		bool bDel;
	};

	class Brush
	{
	public:
		Brush(HDC hdc, HBRUSH hbrush, bool _del = true)
		{
			mHdc = hdc;
			bDel = _del;
			mOldBrush = (HBRUSH)SelectObject(mHdc, hbrush);
		}
		~Brush()
		{
			if (bDel)
				DeleteObject(SelectObject(mHdc, mOldBrush));
			else
				SelectObject(mHdc, mOldBrush);
		}
	private:
		HDC mHdc;
		HBRUSH mOldBrush;
		bool bDel;
	};

	
}


