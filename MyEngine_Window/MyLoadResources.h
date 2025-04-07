#pragma once
#include "..\\MyEngine_SOURCE\\MyResources.h"
#include "..\\MyEngine_SOURCE\\MyTexture.h"

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
    }
}