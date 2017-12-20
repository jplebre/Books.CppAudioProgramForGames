#include <string>
#include <map>
#include <fmod.hpp>
#include "HelperFunctions_AudioProcessing.h"

typedef std::map<std::string, FMOD::Sound* > SoundMap;

class SimpleAudioManager
{
public:
	SimpleAudioManager();
	~SimpleAudioManager();

	void Update(float elapsed);
	
	void LoadSFX(const std::string& path);
	void LoadSong(const std::string& path);

	void PlaySFX(const std::string& path, float minVolume, float maxVolume, float minPitch, float maxPitch);
	void PlaySong(const std::string& path);

	void StopSFX();
	void StopSong();

	void SetMasterVolume(float volume);
	void SetSFXVolume(float volume);
	void SetSongVolume(float volume);


private:
	enum Category {CATEGORY_SFX, CATEGORY_SONG, CATEGORY_COUNT};

	void Load(Category type, const std::string& path);

	FMOD::System* system;

	FMOD::ChannelGroup* master;
	FMOD::ChannelGroup* groups[CATEGORY_COUNT];

	SoundMap sounds[CATEGORY_COUNT];
	FMOD_MODE modes[CATEGORY_COUNT];
	
	FMOD::Channel* currentSong;
	std::string currentSongPath;
	std::string nextSongPath;

	enum FadeState{FADE_NONE, FADE_IN, FADE_OUT};
	FadeState fade;
};