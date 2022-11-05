#include "PerlinNoiseGenerator.h"

PerlinNoiseGenerator::PerlinNoiseGenerator()
{
	GenerateNoiseSeed();
}

PerlinNoiseGenerator::~PerlinNoiseGenerator()
{

}

void PerlinNoiseGenerator::GenerateNoiseSeed()
{
	// Release the old noiseSeed1D from memory before assigning a new one
	if (noiseSeed1D != nullptr)
	{
		delete[] noiseSeed1D;
	}
	
	// Assign the new one
	noiseSeed1D = new float[outputSize];

	// Give it random values
	for (int i = 0; i < outputSize; i++)
	{
		noiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
	}
}

void PerlinNoiseGenerator::GenerateNoise1D(int count, float* seed, int octaves, float* output)
{
	// 1D Perlin Noise
	for (int x = 0; x < count; x++)
	{
		float noise = 0.0f;
		float scale = 1.0f;
		float scaleAccumulate = 0.0f;
		for (int o = 0; o < octaves; o++)
		{
			int pitch = count >> o;
			int sample1 = (x / pitch) * pitch;
			int sample2 = (sample1 + pitch) % count;
		
			float blend = (float)(x - sample1) / (float)pitch;
			float sample = (1.0f - blend) * seed[sample1] + blend * seed[sample2];
			scaleAccumulate += scale;
			noise += sample * scale;
			scale = scale / 2.0f;
		}

		if (x <= outputSize && x != 0)
		{
			output[x] = noise / scaleAccumulate;
		}
	}
}

void PerlinNoiseGenerator::Update()
{
	perlinNoise1D = new float[outputSize];
	GenerateNoise1D(outputSize, noiseSeed1D, 8, perlinNoise1D);
	
	for (int i = 0; i < outputSize; i++)
	{
		int y = -(perlinNoise1D[i] * 256 / 2.0f) + 256 / 2.0f;
		std::cout << "Y =  " << perlinNoise1D[i] << std::endl;

		for (int f = 0; f < 256 / 2; f++)
		{
			// std::cout << f << " - " << y << std::endl;
		}
	}
}