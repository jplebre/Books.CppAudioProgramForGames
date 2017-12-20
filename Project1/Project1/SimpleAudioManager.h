#include <string>
#include <map>
#include <fmod.hpp>

typedef std::map<std::string, FMOD::Sound* > SoundMap;

class SimpleAudioManager
{
public:
	SimpleAudioManager();
	~SimpleAudioManager();

	void Update(float elapsed);
	
	void Load(const std::string& path);
	void Stream(const std::string& path);
	void Play(const std::string& path);

private:
	void LoadOrStream(const std::string& path, bool stream);
	FMOD::System* system;
	SoundMap sounds;
};