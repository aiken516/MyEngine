#include "MyInput.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	std::vector<Input::Key> Input::_keys = {};
	Math::Vector2 Input::_mousePosition = Math::Vector2::zero;

	int ASCII[(UINT)KeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,//Ű���� ����Ű
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,//���콺 ��ư
	};

	void Input::Initailize()
	{
		CreateKeys();
	}

	void Input::CreateKeys()
	{
		for (size_t i = 0; i < (UINT)KeyCode::End; i++)
		{
			Key key = {};
			key.pressed = false;
			key.state = KeyState::None;
			key.keyCode = (KeyCode)i;

			_keys.push_back(key);
		}
	}

	void Input::Update()
	{
		if (!GetFocus())
		{
			//���� ���õ� ȭ���� �� ������ �ƴϸ�
			ClearKey();

			return;
		}

		for (size_t i = 0; i < (UINT)KeyCode::End/*keys.size()*/; i++)
		{
			//Ű�� ����
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (_keys[i].pressed)
				{
					//�̹� ������ �־���
					_keys[i].state = KeyState::Pressed;
				}
				else
				{
					//ó�� ����
					_keys[i].state = KeyState::Down;
				}

				_keys[i].pressed = true;
			}
			else //Ű�� �� ����
			{
				if (_keys[i].pressed)
				{
					//�̹� ������ �־���
					_keys[i].state = KeyState::Up;
				}
				else
				{
					//ó�� ����
					_keys[i].state = KeyState::None;
				}

				_keys[i].pressed = false;
			}
		}

		//���콺 ��ġ �޾ƿ���
		POINT mousePoint = {};
		GetCursorPos(&mousePoint);//������ ��ü ȭ�� ����
		ScreenToClient(application.GetHWND(), &mousePoint);//������ ȭ�� ��������
		_mousePosition.x = (float)mousePoint.x;
		_mousePosition.y = (float)mousePoint.y;
	}

	void Input::ClearKey()
	{
		for (Key& key : _keys)
		{
			//Ű ���� �� �ʱ�ȭ
			if (key.state == KeyState::Down || key.state == KeyState::Pressed)
			{
				key.state = KeyState::Up;
			}
			else if (key.state == KeyState::Up)
			{
				key.state == KeyState::None;
			}

			key.pressed = false;
		}
	}
}