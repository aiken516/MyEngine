#include "MyAudioSource.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyFmod.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	AudioSource::AudioSource() :
		Component(Enums::ComponentType::AudioSource),
		_audioClip(nullptr),
		_channel(nullptr),
		_isLoop(false)
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		float normalizedX = (position.x / application.GetWidth()) * 2.0f - 1.0f;
		float normalizedY = ((position.y / application.GetHeight()) * 2.0f - 1.0f) * -1.0f;

		FMOD_VECTOR fmodPos(normalizedX, normalizedY, 0.3f);
		FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);

		_channel->set3DAttributes(&fmodPos, &fmodVel);
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		if (_audioClip == nullptr)
		{
			return;
		}

		FMOD::Sound* sound = _audioClip->GetSound();
		if (sound == nullptr)
		{
			return;
		}

		FMOD::Channel* channel = nullptr;
		
		Fmod::SoundPlay(sound, &channel);
		if (_isLoop)
		{
			channel->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			channel->setMode(FMOD_LOOP_OFF);
		}

		_channel = channel; // 이 소스만의 채널
	}

	void AudioSource::Stop()
	{
		_channel->stop();
	}
}