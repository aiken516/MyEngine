#pragma once
#include "MyResource.h"

namespace Source
{
	class Resources
	{
	public:
		Resources();
		~Resources();

		static void Release();

		template <typename T>
		static T* Find(const std::wstring& key)
		{
			std::map<std::wstring, Resource*>::iterator iter = _resources.find(key);

			if (iter == _resources.end())
			{
				return nullptr;
			}

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
			}

			resource->SetName(key);
			resource->SetPath(path);
			_resources.insert(std::make_pair(key, resource));

			return resource;
		}

	private:
		static std::map<std::wstring, Resource*> _resources;
	};
}