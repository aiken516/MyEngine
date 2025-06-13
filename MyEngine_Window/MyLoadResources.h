#pragma once
#include "..\\MyEngine_SOURCE\\MyResources.h"
#include "..\\MyEngine_SOURCE\\MyTexture.h"
#include "..\\MyEngine_SOURCE\\MyAudioClip.h"

using namespace Source;

namespace Client
{
    void LoadResources()
    {
        Resources::Load<Graphics::Texture>(L"background", L"..\\Resources\\background.png");
        Resources::Load<Graphics::Texture>(L"Pacman", L"..\\Resources\\Pacman\\0.png");
        Resources::Load<Graphics::Texture>(L"Chicken", L"..\\Resources\\chicken.bmp");
        Resources::Load<Graphics::Texture>(L"Cat", L"..\\Resources\\CatAlpha.bmp");
        Resources::Load<Graphics::Texture>(L"Punch", L"..\\Resources\\Punch.png");
        Resources::Load<Graphics::Texture>(L"Mushroom1", L"..\\Resources\\Mushroom\\1.bmp");
        Resources::Load<Graphics::Texture>(L"Mushroom2", L"..\\Resources\\Mushroom\\2.bmp");
        Resources::Load<Graphics::Texture>(L"Mushroom3", L"..\\Resources\\Mushroom\\3.bmp");

        Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sounds\\BGM.wav");

    }
}