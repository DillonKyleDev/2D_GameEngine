#pragma once
#ifndef PerlinNoiseGenerator_h
#define PerlinNoiseGenerator_h

#include "Game.h"

class PerlinNoiseGenerator
{
public:
	PerlinNoiseGenerator();
	~PerlinNoiseGenerator();

	void GenerateNoiseSeed();
	void GenerateNoise1D(int count, float* seed, int octaves, float* output);
	void Update();

private:
	float* noiseSeed1D = nullptr;
	float* perlinNoise1D = nullptr;
	int outputSize = 800;
};

#endif