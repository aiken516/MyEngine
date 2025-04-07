#include "MyResources.h"

namespace Source
{
	std::map<std::wstring, Resource*> Resources::_resources = {};

	Resources::Resources()
	{
	}

	Resources::~Resources()
	{
	}

	void Resources::Release()
	{
		for (auto& resource : _resources)
		{
			if (resource.second != nullptr)
			{
				delete resource.second;
				resource.second = nullptr;
			}
		}
		_resources.clear();
	}
}