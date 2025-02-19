#include "MyInput.h"

namespace Source
{
	std::vector<Input::Key> Input::keys = {};

	int ASCII[(UINT)KeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
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

			keys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0; i < (UINT)KeyCode::End/*keys.size()*/; i++)
		{
			//키가 눌림
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (keys[i].pressed)
				{
					//이미 눌러져 있었음
					keys[i].state = KeyState::Pressed;
				}
				else
				{
					//처음 눌림
					keys[i].state = KeyState::Down;
				}

				keys[i].pressed = true;
			}
			else //키가 안 눌림
			{
				if (keys[i].pressed)
				{
					//이미 눌러져 있었음
					keys[i].state = KeyState::Up;
				}
				else
				{
					//처음 눌림
					keys[i].state = KeyState::None;
				}

				keys[i].pressed = false;
			}
		}
	}
}