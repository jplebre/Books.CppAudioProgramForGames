#include <fmod.hpp>
#include "CheckErrors.h"



	//creating and instantiating sound engine
	FMOD::System *system;
	FMOD_RESULT result = FMOD::System_Create(&system);
	//ExitOnError(System_Create(&system));

	//loading defaults - initialising sound engine
	system->init(100, FMOD_INIT_NORMAL);
	system->update();
	system->release();

	//loading sound objects into memory, or streaming them from disk
	FMOD::Sound* sound;
	system->createSound("sfx.wav", FMOD_DEFAULT, 0, &sound);

	FMOD::Sound* stream;
	system->createStream("song.ogg", FMOD_DEFAULT, 0, &stream);

	//Play created "sound" objects
	FMOD::Channel* channel;
	system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);

	sound->release();
	stream->release();
