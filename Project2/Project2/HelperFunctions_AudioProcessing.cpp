#include "HelperFunctions_AudioProcessing.h"

float ChangeSemitone(float frequency, float variation)
{
	static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
	return frequency * pow(semitone_ratio, variation);
}

float RandomBetween(float min, float max)
{
	if (min == max) return min;
	float n = (float)rand() / (float)RAND_MAX;
	return min + n*(max - min);
}

