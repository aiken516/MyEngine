#pragma once
#include "MyEntity.h"

namespace Source
{
	using namespace Enums;

	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				_event = std::move(func);
			}

			void operator()()
			{
				if (_event)
				{
					_event();
				}
			}

			std::function<void()> _event;
		};


		UIBase(UIType type);
		virtual ~UIBase();
		void Initialize();
		void Active();
		void InActive();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);
		void Clear();

		virtual void OnInitialize();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC hdc);
		virtual void OnClear();

		UIType GetType() const { return _type; }
		void SetType(UIType type) { _type = type; }
		void SetFullScreen(bool isFullScreen) { _isFullScreen = isFullScreen; }
		bool IsFullScreen() const { return _isFullScreen; }
		
		Vector2 GetPosition() const { return _position; }
		void SetPosition(const Vector2& position) { _position = position; }
		Vector2 GetSize() const { return _size; }
		void SetSize(const Vector2& size) { _size = size; }

	protected:
		Vector2 _position;
		Vector2 _size;
		bool _isMouseHover;

	private:
		UIType _type;
		bool _isFullScreen;
		bool _isActive;

		UIBase* _parent;
	};
}