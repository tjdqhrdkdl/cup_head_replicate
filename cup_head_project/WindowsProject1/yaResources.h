#pragma once
#include "Common.h"
#include "yaResource.h"
namespace ya {

	class Resources
	{
	public:

		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			if (resource == nullptr
				|| key == L"")
				return;

			mResources.insert(std::make_pair(key, resource));
		}

		template <typename T>
		static T* Find(const std::wstring& key)
		{
			if (mResources.find(key) != mResources.end())
			{
				return (T*)mResources.find(key)->second;
			}
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}
			
			resource = new T();

			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Image Load Failed!!!", L"Error", MB_OK);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return resource;
		}
		
		static void Release()
		{
			for (std::pair<std::wstring, Resource*> pair : mResources )
			{
				if (pair.second == nullptr)
					continue;
				delete pair.second;
				pair.second = nullptr;
			}
		}
		
	private:
		static std::map<std::wstring, Resource*> mResources;
	};

}
