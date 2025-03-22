#pragma once
#include "..\\MyEngine_SOURCE\\MyResources.h"
#include "..\\MyEngine_SOURCE\\MyTexture.h"

using namespace Source;

namespace Client
{
    void LoadResources()
    {
        Resources::Load<Graphics::Texture>(L"background", L"C:\\Users\\User\\Documents\\GitHub\\MyEngine\\Resources\\background.png");
        Resources::Load<Graphics::Texture>(L"Pacman", L"C:\\Users\\User\\Documents\\GitHub\\MyEngine\\Resources\\Pacman\\0.png");
    }
}