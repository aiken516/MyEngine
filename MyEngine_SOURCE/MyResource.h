#pragma once
#include "MyEntity.h"

namespace Source
{
	class Resource : public Entity // �߻� Ŭ����(���� ���� �Լ��� ���Ե� Ŭ����), �޸� �Ҵ� �Ұ�
	{
	public:
		Resource(const Enums::ResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring path) = 0;
		// = 0 ���� ���� �Լ� ����, ���� �޸� �Ҵ� �Ұ��������� ����
		//HRESULT, 0 > �ΰ�, bool�� ���� ������ ����ϴ� ������ ����

		const std::wstring& GetPath() { return _path; };
		void SetPath(const std::wstring& path) { _path = path; };
	private:
		std::wstring _path;
		const Enums::ResourceType _type;
	};
}
