#pragma once
#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <queue>
#include <stack>
#include <assert.h>
#include <unordered_map>
#include "def.h"
#include "Maths.h"


#pragma comment(lib, "Msimg32.lib")
#include <ole2.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")
union Pixel
{
	struct
	{
		BYTE R;
		BYTE G;
		BYTE B;
		BYTE A;
	};
	DWORD Color;

	Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
		:R(r), G(g), B(b), A(a)
	{

	}

	Pixel(COLORREF color)
		:Color(color)
	{

	}

};

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


