#pragma once
#include <random>

namespace Source
{
	class Random
	{
	public:
		static int Range(int minInclude, int maxInclude)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());

			std::uniform_int_distribution<> dis(minInclude, maxInclude);
			return dis(gen);
		}

		static float Range(float minInclude, float maxInclude)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());

			std::uniform_real_distribution<float> dis(minInclude, maxInclude);
			return dis(gen);
		}
	};
}