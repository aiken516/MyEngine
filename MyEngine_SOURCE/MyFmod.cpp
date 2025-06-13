#include "MyFmod.h"
#include "MyApplication.h"

extern Source::Application application;

namespace Source
{
	FMOD::Studio::System* Fmod::_system = nullptr;
	FMOD::System* Fmod::_coreSystem = nullptr;

	void Fmod::Initialize()
	{
		void* extraDriverData = nullptr;

		FMOD::Studio::System::create(&_system);

		_system->getCoreSystem(&_coreSystem);
		_coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

		_system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
	}

	bool Fmod::CreateSound(const std::string& path, FMOD::Sound** sound)
	{
		if (FMOD_OK != _coreSystem->createSound(path.c_str(), FMOD_3D, 0, sound))
		{
			return false;
		}

		return true;
	}

	void Fmod::SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		_coreSystem->playSound(sound, 0, false, channel);
	}

	void Fmod::Set3DListenerAttributes(const Vector2* position)
	{
		//-1 ~ 1
		float normalizedX = (position->x / application.GetWidth()) * 2.0f - 1.0f;
		float normalizedY = ((position->y / application.GetHeight()) * 2.0f - 1.0f) * -1.0f;

		FMOD_VECTOR fmodPos(normalizedX, normalizedY, 0.3f);
		FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);
		FMOD_VECTOR fmodForward(0.0f, 0.0f, 1.0f);
		FMOD_VECTOR fmodUp(0.0f, 1.0f, 0.0f);

		_coreSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodForward, &fmodUp);
	}

	void Fmod::Release()
	{
		_system->release();
		_system = nullptr;
	}
}