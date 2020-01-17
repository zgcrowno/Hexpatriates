#pragma once

#include "Hexpatriates.h"
#include <map>
#include <vector>

namespace hexpatriates
{
    class AudioManager
    {
    private:
        /* Here will be the instance stored. */
        static AudioManager* instance;

        /* Private constructor to prevent instancing. */
        AudioManager();

    public:
        orxSOUND *m_menuMusic;
        std::map<std::string, orxSOUND*> m_pilotMusicMap;

        static AudioManager* GetInstance();
        /// <summary>Crossfades the sound being played by <paramref name="_from"/> to the sound being played by <paramref name="_to"/>.</summary>
        /// <param name="_from">The sound being faded out.</param>
        /// <param name="_to">The sound being faded in.</param>
        /// <param name="_duration">The length of the crossfade, in seconds.</param>
        /// <param name="_fDT">The delta time.</param>
        static void CrossFade(orxSOUND *_from, orxSOUND *_to, const float &_duration, const float &_fDT);
    };
}
