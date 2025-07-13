#pragma once
#include "MyComponent.h"
#include "MyAudioClip.h"

namespace Source
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Play();
		void Stop();

		void SetAudioClip(AudioClip* audioClip) { _audioClip = audioClip; }
		AudioClip* GetAudioClip() { return _audioClip; }
		void SetIsLoop(bool isLoop) { _isLoop = isLoop; }
	private:
		AudioClip* _audioClip;
		FMOD::Channel* _channel;

		bool _isLoop;
	};
}