#pragma once
#include "MyEntity.h"

namespace Source
{
	class Resource : public Entity // 추상 클래스(순수 가상 함수가 포함된 클래스), 메모리 할당 불가
	{
	public:
		Resource(const Enums::ResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring path) = 0;
		// = 0 순수 가상 함수 선언, 실제 메모리 할당 불가능해지는 문법
		//HRESULT, 0 > 인가, bool과 같은 역할을 대신하는 원도우 문법

		const std::wstring& GetPath() { return _path; };
		void SetPath(const std::wstring& path) { _path = path; };
	private:
		std::wstring _path;
		const Enums::ResourceType _type;
	};
}
