#pragma once
#include "CommonInclude.h"

namespace Source
{
	enum class KeyState
	{
		None,
		Down,
		Pressed,
		Up
	};

	enum class KeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		LEFT, RIGHT, DOWN, UP,
		LBUTTON, RBUTTON, MBUTTON,
		End
	};

	class Input
	{
	public:
		struct Key
		{
			KeyCode keyCode;
			KeyState state;
			bool pressed;
		};

		static void Initailize();
		static void CreateKeys();
		static void Update();

		__forceinline static bool GetKeyDown(KeyCode keyCode) { return _keys[(UINT)keyCode].state == KeyState::Down; }
		__forceinline static bool GetKeyUp(KeyCode keyCode) { return _keys[(UINT)keyCode].state == KeyState::Up; }
		__forceinline static bool GetKey(KeyCode keyCode) { return _keys[(UINT)keyCode].state == KeyState::Pressed; }

		__forceinline static Math::Vector2 GetMousePosition() { return _mousePosition; }

		static void ClearKey();
	private:
		static std::vector<Key> _keys;
		static Math::Vector2 _mousePosition;
	};
}



