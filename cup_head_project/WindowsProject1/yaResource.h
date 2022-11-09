#pragma once
#include "Common.h"
namespace ya 
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const void SetKey(const std::wstring& key) { mKey = key; }
		const std::wstring& GetPath() { return mPath; }
		const void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mPath;
		std::wstring mKey;
	};
}

