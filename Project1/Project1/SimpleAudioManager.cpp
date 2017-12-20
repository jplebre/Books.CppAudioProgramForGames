#include "SimpleAudioManager.h"

SimpleAudioManager::SimpleAudioManager()
{
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);

}

SimpleAudioManager::~SimpleAudioManager()
{
	//release every sound object
	//clear the sound map
	SoundMap::iterator iter;
	for (iter = sounds.begin(); iter != sounds.end(); iter++)
	{
		iter->second->release();
	}
	sounds.clear();

	//release the system object (main engine)
	system->release();
	system = 0;

}

void SimpleAudioManager::Update(float elapsed)
{
	system->update();
}

void SimpleAudioManager::LoadOrStream(const std::string& path, bool stream)
{
	//Is sound already loaded?
	if (sounds.find(path) != sounds.end())
		return;

	//load sound or stream file to a sound object
	FMOD::Sound* sound;
	if (stream)
		system->createStream(path.c_str(), FMOD_DEFAULT, 0, &sound);
	else
		system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);

	//Store sound object in the map
	//use path as "key"
	sounds.insert(std::make_pair(path, sound));
}

void SimpleAudioManager::Load(const std::string& path)
{
	LoadOrStream(path, false);
}

void SimpleAudioManager::Stream(const std::string& path)
{
	LoadOrStream(path, true);
}

void SimpleAudioManager::Play(const std::string& path)
{
	//search for matching sound in the map
	SoundMap::iterator sound = sounds.find(path);

	if (sound == sounds.end())
		return;

	system->playSound(FMOD_CHANNEL_FREE, sound->second, false, 0);
}