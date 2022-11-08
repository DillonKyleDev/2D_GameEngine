#pragma once
#ifndef PerlinNoiseGenerator_h
#define PerlinNoiseGenerator_h

#include "Game.h"
#include "GameObject.h"

class PerlinNoiseGenerator
{
public:
	PerlinNoiseGenerator();
	~PerlinNoiseGenerator();

	void Generate1DNoiseSeed();
	void GenerateNoise1D(int count, float* seed, int octaves, float bias, float* output);
	void Draw1DNoise();

	void Generate2DNoiseSeed();
	void GenerateNoise2D(int width, int height, float* seed, int octaves, float bias, float* output);
	void Draw2DNoise();
	
	const static int divider = 20;
	GameObject* objectArray1D[256];
	GameObject* objectArray2D[Game::width / divider * Game::height / divider];


private:
	// 1 Dimensional noise variables
	int outputSize = 256;
	float* noiseSeed1D = nullptr;
	float* perlinNoise1D = nullptr;
	float highest1DNoiseValue = 0;

	// 2 Dimensional noise variables
	int outputWidth = Game::width / divider;
	int outputHeight = Game::height / divider;
	float* noiseSeed2D = nullptr;
	float* perlinNoise2D = nullptr;
	float highest2DNoiseValue = 0;
};

#endif