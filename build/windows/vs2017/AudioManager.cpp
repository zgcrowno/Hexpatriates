#include "AudioManager.h"

using namespace hexpatriates;

// Define static class members.
/* Null, because instance will be initialized on demand. */
AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
    m_menuMusic = orxSound_CreateFromConfig("SM-Menu");
    m_pilotMusicMap.insert({ "O-Pilot1", orxSound_CreateFromConfig("SM-Pilot1") });
    m_pilotMusicMap.insert({ "O-Pilot2", orxSound_CreateFromConfig("SM-Pilot2") });
    m_pilotMusicMap.insert({ "O-Pilot3", orxSound_CreateFromConfig("SM-Pilot3") });
    m_pilotMusicMap.insert({ "O-Pilot4", orxSound_CreateFromConfig("SM-Pilot4") });
    m_pilotMusicMap.insert({ "O-Pilot5", orxSound_CreateFromConfig("SM-Pilot5") });
    m_pilotMusicMap.insert({ "O-Pilot6", orxSound_CreateFromConfig("SM-Pilot6") });
    m_pilotMusicMap.insert({ "O-Pilot7", orxSound_CreateFromConfig("SM-Pilot7") });
    m_pilotMusicMap.insert({ "O-Pilot8", orxSound_CreateFromConfig("SM-Pilot8") });
}

AudioManager::~AudioManager()
{
    delete instance;
    instance = nullptr;
}

AudioManager* AudioManager::GetInstance()
{
    if (instance == 0)
    {
        instance = new AudioManager();
    }

    return instance;
}

void AudioManager::CrossFade(orxSOUND *_from, orxSOUND *_to, const float &_duration, const float &_fDT) {
    float step = _duration * _fDT;
    float fromVolume = orxSound_GetVolume(_from);
    float toVolume = orxSound_GetVolume(_to);
    fromVolume -= step;
    toVolume += step;
    float clampedFromVolume = orxCLAMP(fromVolume, 0, 1);
    float clampedToVolume = orxCLAMP(toVolume, 0, 1);
    orxSound_SetVolume(_from, clampedFromVolume);
    orxSound_SetVolume(_to, clampedToVolume);
}
