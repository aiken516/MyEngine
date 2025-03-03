#pragma once
#include "CommonInclude.h"

namespace Source
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		void SetName(const std::wstring& nameParam) { _name = nameParam; };
		std::wstring& GetName() { return _name; }
	private:
		std::wstring _name;
	};
}
