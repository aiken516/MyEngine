#include "MyAudioListener.h"
#include "MyTransform.h"
#include "MyGameObject.h"
#include "MyFmod.h"

namespace Source
{
	AudioListener::AudioListener() :
		Component(Enums::ComponentType::AudioListener)
	{
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Initialize()
	{
	}

	void AudioListener::Update()
	{
	}

	void AudioListener::LateUpdate()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 posisiotn = transform->GetPosition();

		Fmod::Set3DListenerAttributes(&posisiotn);
	}

	void AudioListener::Render()
	{
	}
}