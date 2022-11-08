#include "PerlinNoiseGenerator.h"
#include "Game.h"

PerlinNoiseGenerator::PerlinNoiseGenerator()
{

}

PerlinNoiseGenerator::~PerlinNoiseGenerator()
{

}

void PerlinNoiseGenerator::Generate1DNoiseSeed()
{
	// Release the old array from memory before assigning a new one
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

void PerlinNoiseGenerator::GenerateNoise1D(int count, float* seed, int octaves, float bias, float* output)
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
			scale = scale / bias;
		}

		output[x] = noise / scaleAccumulate;
	}
}

void PerlinNoiseGenerator::Draw1DNoise()
{
	Generate1DNoiseSeed();

	if (perlinNoise1D != nullptr)
	{
		delete[] perlinNoise1D;
	}
	perlinNoise1D = new float[outputSize];

	GenerateNoise1D(outputSize, noiseSeed1D, 8, 2, perlinNoise1D);

	for (int i = 0; i < outputSize; i++)
	{
		float y = perlinNoise1D[i] * 256;
		std::cout << y << std::endl;
		GameObject* newObject = new GameObject("assets/Green_Pixel.png", i, y);
		objectArray1D[i] = newObject;
	}
}

void PerlinNoiseGenerator::Generate2DNoiseSeed()
{	
	std::cout << "Generating random noise seed..." << std::endl;

	// Release the old array from memory before assigning a new one
	if (noiseSeed2D != nullptr)
	{
		delete[] noiseSeed2D;
	}

	// Assign the new one
	noiseSeed2D = new float[outputWidth * outputHeight];

	// Give it random values
	for (int i = 0; i < outputWidth * outputHeight; i++)
	{
		noiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
	}
}

void PerlinNoiseGenerator::GenerateNoise2D(int width, int height, float* seed, int octaves, float bias, float* output)
{
	std::cout << "Generating 2D noise array..." << std::endl;

	// 2D Perlin Noise
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float noise = 0.0f;
			float scale = 1.0f;
			float scaleAccumulate = 0.0f;

			for (int o = 0; o < octaves; o++)
			{
				int pitch = width >> o;
				int sampleX1 = (x / pitch) * pitch;
				int sampleY1 = (y / pitch) * pitch;

				int sampleX2 = (sampleX1 + pitch) % width;
				int sampleY2 = (sampleY1 + pitch) % width;

				float blendX = (float)(x - sampleX1) / (float)pitch;
				float blendY = (float)(y - sampleY1) / (float)pitch;

				float sampleT = (1.0f - blendX) * seed[sampleY1 * width + sampleX1] + blendX * seed[sampleY1 * width + sampleX2];
				float sampleB = (1.0f - blendX) * seed[sampleY2 * width + sampleX1] + blendX * seed[sampleY2 * width + sampleX2];

				noise += (blendY * (sampleB - sampleT) + sampleT) * scale;
				scaleAccumulate += scale;
				scale = scale / bias;
			}

			output[y * width + x] = noise / scaleAccumulate;
			if (noise / scaleAccumulate > highest2DNoiseValue)
			{
				highest2DNoiseValue = noise / scaleAccumulate;
			}
		}
	}
}

void PerlinNoiseGenerator::Draw2DNoise()
{
	Generate2DNoiseSeed();

	if (perlinNoise2D != nullptr)
	{
		delete[] perlinNoise2D;
	}

	perlinNoise2D = new float[outputWidth * outputHeight];

	GenerateNoise2D(outputWidth, outputHeight, noiseSeed2D, 6, 2.4, perlinNoise2D);

	std::cout << "Drawing 2D noise..." << std::endl;
	int count = 0;

	for (int x = 0; x < outputWidth; x++)
	{
		for (int y = 0; y < outputHeight; y++)
		{
			if (perlinNoise2D[y * outputWidth + x] / highest2DNoiseValue < 0.33f)
			{
				GameObject* newObject = new GameObject("assets/Rock_Block.png", x * divider, y * divider);
				objectArray2D[count] = newObject;
				count++;
			}
			else if (perlinNoise2D[y * outputWidth + x] / highest2DNoiseValue < 0.44f)
			{
				GameObject* newObject = new GameObject("assets/Dirt_Block.png", x * divider, y * divider);
				objectArray2D[count] = newObject;
				count++;
			}
			else if (perlinNoise2D[y * outputWidth + x] / highest2DNoiseValue < 0.66f)
			{
				GameObject* newObject = new GameObject("assets/Sand_Block.png", x * divider, y * divider);
				objectArray2D[count] = newObject;
				count++;
			} else
			{
				GameObject* newObject = new GameObject("assets/Water_Block.png", x * divider, y * divider);
				objectArray2D[count] = newObject;
				count++;
			}
		}
	}
	std::cout << "Done drawing 2D noise..." << std::endl;
}