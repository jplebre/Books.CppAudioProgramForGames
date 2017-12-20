#include <iostream>
#include <fmod_errors.h>
#include "CheckErrors.h"

void ExitOnError(FMOD_Result result)
{
	if (result != FMOD_OK)
	{
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}