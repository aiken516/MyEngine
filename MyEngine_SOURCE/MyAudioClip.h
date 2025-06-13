#pragma once
#include "MyResource.h"
#include "MyFmod.h"

namespace Source
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		virtual HRESULT Load(const std::wstring path) override;

		FMOD::Sound* GetSound() { return _sound; }
		void SetMinMaxDistance(float min, float max);
	private:
		FMOD::Sound* _sound;

		float _minDistance;
		float _maxDistance;
	};
}