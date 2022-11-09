#pragma once
#include "Common.h"
namespace ya {
	class Entity
	{
	public:
		Entity();
		~Entity();
		void SetName(std::wstring _name) { mName = _name; }
		std::wstring GetName(){ return mName; }
		UINT32 GetId() { return mID; }
	private:
		std::wstring mName;
		UINT32 mID;
	};
}
