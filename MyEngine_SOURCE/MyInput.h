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
		static void Update();

		static bool GetKeyDown(KeyCode keyCode) { return keys[(UINT)keyCode].state == KeyState::Down; }
		static bool GetKeyUp(KeyCode keyCode) { return keys[(UINT)keyCode].state == KeyState::Up; }
		static bool GetKey(KeyCode keyCode) { return keys[(UINT)keyCode].state == KeyState::Pressed; }

	private:
		static std::vector<Key> keys;
	};
}



