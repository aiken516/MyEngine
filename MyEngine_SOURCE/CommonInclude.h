#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <functional>
#include <filesystem>
#include <math.h>
#include <mutex>
#include <thread>

#include "MyMath.h"
#include "MyEnums.h"

#define CAST_UINT(value) static_cast<UINT>(value)
#define CAST_FLOAT(value) static_cast<float>(value)

#include <assert.h>

// --- Window GUI ---
#include <mmsystem.h>
#include <dinput.h>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")