#pragma once
#include "CommonInclude.h"

namespace Source
{
	using namespace Math;

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		void SetName(const std::wstring& name) { _name = name; };
		std::wstring& GetName() { return _name; }
	private:
		std::wstring _name;
	};
}
