#include "SimpleAudioManager.h"

SimpleAudioManager::SimpleAudioManager()
{
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);

	//create groups for each category
	system->getMasterChannelGroup(&master);
	for (int i = 0; i < CATEGORY_COUNT; ++i)
	{
		system->createChannelGroup(0, &groups[i]);
		master->addGroup(groups[i]);
	}

	//set up modes for each category:
	modes[CATEGORY_SFX] = FMOD_DEFAULT;
	modes[CATEGORY_SONG] = FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL;

	//random number generator to trigger SFX
	srand(time(0));
}

SimpleAudioManager::~SimpleAudioManager()
{
	//release every sound object
	//clear the sound map
	SoundMap::iterator iter;
	for (int i=0; i < CATEGORY_COUNT; ++i)
	{
		for (iter = sounds[i].begin(); iter != sounds[i].end(); ++iter)
		{
			iter->second->release();
		}
		sounds[i].clear();
	}

	//release the system object (main engine)
	system->release();
}

void SimpleAudioManager::Update(float elapsed)
{
	const float fadeTime = 1.0f; //changes fade time, in seconds
	
	if (currentSong != 0 && fade == FADE_IN)
	{
		float volume;
		currentSong->getVolume(&volume);
		float nextVolume = volume + elapsed / fadeTime;
		if (nextVolume >= 1.0f)
		{
			currentSong->setVolume(1.0f);
			fade = FADE_NONE;
		}
		else
		{
			currentSong->setVolume(nextVolume);
		}
	}
	else if (currentSong != 0 && fade == FADE_OUT)
	{
		float volume;
		currentSong->getVolume(&volume);
		float nextVolume = volume - elapsed / fadeTime;

		if (nextVolume <= 0.0f)
		{
			currentSong->stop();
			currentSong = 0;
			currentSongPath.clear();
			fade = FADE_NONE;
		}
		else
		{
			currentSong->setVolume(nextVolume);
		}
	}
	else if (currentSong == 0 && !nextSongPath.empty())
	{
		PlaySong(nextSongPath);
		nextSongPath.clear();
	}

	system->update();
}

void SimpleAudioManager::LoadSFX(const std::string& path)
{
	Load(CATEGORY_SFX, path);
}

void SimpleAudioManager::LoadSong(const std::string& path)
{
	Load(CATEGORY_SONG, path);
}

void SimpleAudioManager::Load(Category type, const std::string& path)
{
	if (sounds[type].find(path) != sounds[type].end()) return;

	FMOD::Sound* sound;
	system->createSound(path.c_str(), modes[type], 0, &sound);
	sounds[type].insert(std::make_pair(path, sound));
}

void SimpleAudioManager::PlaySFX(const std::string& path, float minVolume, float maxVolume, float minPitch, float maxPitch)
{
	//return if SFX not found
	SoundMap::iterator sound = sounds[CATEGORY_SFX].find(path);
	if (sound == sounds[CATEGORY_SFX].end()) return;

	//calculate a random volume and pitch for selected input range
	float volume = RandomBetween(minVolume, maxVolume);
	float pitch = RandomBetween(minPitch, maxPitch);

	//play sound effect with initial values:
	FMOD::Channel * channel;
	system->playSound(FMOD_CHANNEL_FREE, sound->second, true, &channel);

	channel->setChannelGroup(groups[CATEGORY_SFX]);
	channel->setVolume(volume);
	float frequency;
	channel->getFrequency(&frequency);
	channel->setFrequency(ChangeSemitone(frequency, pitch));
	channel->setPaused(false);
}

void SimpleAudioManager::StopSFX()
{
	groups[CATEGORY_SFX]->stop();
}

void SimpleAudioManager::PlaySong(const std::string& path)
{
	//ignore if song is already playing
	if (currentSongPath == path) return;

	//if a song is playing stop them and set this as the next song
	if (currentSong != 0)
	{
		StopSong();
		nextSongPath = path;
		return;
	}

	//find the song in the corresponding sound map
	SoundMap::iterator sound = sounds[CATEGORY_SONG].find(path);

	if (sound == sounds[CATEGORY_SONG].end())
		return;

	//start playing song with volume set to 0 and fade in
	currentSongPath = path;
	system->playSound(FMOD_CHANNEL_FREE, sound->second, true, &currentSong);

	currentSong->setChannelGroup(groups[ CATEGORY_SONG ]);
	currentSong->setVolume(0.0f);
	currentSong->setPaused(false);
	fade = FADE_IN;
}

void SimpleAudioManager::StopSong()
{
	if (currentSong != 0)
		fade = FADE_OUT;

	nextSongPath.clear();
}


//setting group volumes
void SimpleAudioManager::SetMasterVolume(float volume)
{
	master->setVolume(volume);
}

void SimpleAudioManager::SetSFXVolume(float volume)
{
	groups[CATEGORY_SFX]->setVolume(volume);
}

void SimpleAudioManager::SetSongVolume(float volume)
{
	groups[CATEGORY_SONG]->setVolume(volume);
}

