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
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,//키보드 방향키
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,//마우스 버튼
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
			//현재 선택된 화면이 이 엔진이 아니면
			ClearKey();

			return;
		}

		for (size_t i = 0; i < (UINT)KeyCode::End/*keys.size()*/; i++)
		{
			//키가 눌림
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (_keys[i].pressed)
				{
					//이미 눌러져 있었음
					_keys[i].state = KeyState::Pressed;
				}
				else
				{
					//처음 눌림
					_keys[i].state = KeyState::Down;
				}

				_keys[i].pressed = true;
			}
			else //키가 안 눌림
			{
				if (_keys[i].pressed)
				{
					//이미 눌러져 있었음
					_keys[i].state = KeyState::Up;
				}
				else
				{
					//처음 눌림
					_keys[i].state = KeyState::None;
				}

				_keys[i].pressed = false;
			}
		}

		//마우스 위치 받아오기
		POINT mousePoint = {};
		GetCursorPos(&mousePoint);//윈도우 전체 화면 기준
		ScreenToClient(application.GetHWND(), &mousePoint);//엔진의 화면 기준으로
		_mousePosition.x = (float)mousePoint.x;
		_mousePosition.y = (float)mousePoint.y;
	}

	void Input::ClearKey()
	{
		for (Key& key : _keys)
		{
			//키 눌린 값 초기화
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