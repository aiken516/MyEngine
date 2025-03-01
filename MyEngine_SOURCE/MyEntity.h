#pragma once
#include "CommonInclude.h"

namespace Source
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		void SetName(const std::wstring& nameParam) { name_ = nameParam; };
		std::wstring& GetName() { return name_; }
	private:
		std::wstring name_;
	};
}
