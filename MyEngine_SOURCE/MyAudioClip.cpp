#include "MyAudioClip.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	AudioClip::AudioClip() :
		Resource(Enums::ResourceType::AudioClip),
		_sound(nullptr),
		_minDistance(1.0f),
		_maxDistance(1000.0f)
	{
	}

	AudioClip::~AudioClip()
	{
		_sound->release();
		_sound = nullptr;
	}

	HRESULT AudioClip::Load(const std::wstring path)
	{
		std::string pathString(path.begin(), path.end());

		if (!Fmod::CreateSound(pathString, &_sound))
		{
			return S_FALSE;
		}

		_sound->set3DMinMaxDistance(_minDistance, _maxDistance);

		return S_OK;
	}

	void AudioClip::SetMinMaxDistance(float min, float max)
	{
		_minDistance = min;
		_maxDistance = max;
		if (_sound != nullptr)
		{
			_sound->set3DMinMaxDistance(min, max);
		}
	}
}