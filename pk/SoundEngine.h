#pragma once

#include <fmod/fmod.hpp>

#include <map>
#include <string>

class SoundEngine
{
public:
	typedef std::map<std::string, FMOD::Sound*> SoundsMap;
	typedef std::pair<std::string, FMOD::Sound*> SoundPair;
	typedef std::map<int, FMOD::Channel*> ChannelsMap;
	typedef std::pair<int, FMOD::Channel*> ChannelPair;

	static SoundEngine& Get()
	{
		static SoundEngine Instance;
		return Instance;
	}

	void Load(const std::string& SoundPath);
	int Play(const std::string& SoundPath, const float Volume);
	int Play(const std::string& SoundPath, const float Volume, bool bMuted, bool bLoop);
	void Mute(int ChannelId, bool bMute);
	void Stop(int ChannelId);
	void SetChannelVolume(const int ChannelId, const float NewVolume);
	void SetChannelPitch(const int ChannelId, const float Pitch);
	bool IsPlaying(const int ChannelId) const;

	bool IsLoaded(const std::string& SoundName) const;

	FMOD_RESULT GetLastResult() const;

	void Update(const float Delta);

	SoundEngine(const SoundEngine&) = delete;
	void operator=(const SoundEngine&) = delete;

	~SoundEngine();

private:
	bool IsActive(const int ChannelId) const;
	SoundEngine();
	void Initialize();

	FMOD::System* System;
	FMOD_RESULT LastResult;

	SoundsMap LoadedSounds;
	ChannelsMap ActiveChannels;
	int NextChannelId;
};