#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "Spawner.h"

namespace hexpatriates
{
    /// <summary>Represents a vessel which is operated by a Pilot.</summary>
    class Ship : public ScrollMod
    {
    protected:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete();
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        int m_clipSizeNeutral;
        int m_clipIndexNeutral;
        int m_waveSizeNeutral;
        int m_numWavesNeutral;
        int m_wavesIndexNeutral;
        float m_maxCooldownNeutral;
        float m_cooldownNeutral;
        float m_maxWaveDelayNeutral;
        float m_waveDelayNeutral;
        int m_clipSizeUpward;
        int m_clipIndexUpward;
        int m_waveSizeUpward;
        int m_numWavesUpward;
        int m_wavesIndexUpward;
        float m_maxCooldownUpward;
        float m_cooldownUpward;
        float m_maxWaveDelayUpward;
        float m_waveDelayUpward;
        int m_clipSizeDownward;
        int m_clipIndexDownward;
        int m_waveSizeDownward;
        int m_numWavesDownward;
        int m_wavesIndexDownward;
        float m_maxCooldownDownward;
        float m_cooldownDownward;
        float m_maxWaveDelayDownward;
        float m_waveDelayDownward;
        int m_waveSizeSuper;
        int m_numWavesSuper;
        int m_wavesIndexSuper;
        float m_maxCooldownSuper;
        float m_cooldownSuper;
        float m_maxWaveDelaySuper;
        float m_waveDelaySuper;
        //! The direction in which the Ship's enemy's zone is, measured in radians.
        float m_enemyDirection;
        orxSTRING m_neutralInput;
        orxSTRING m_upwardInput;
        orxSTRING m_downwardInput;
        orxSTRING m_superInput;
        Spawner *m_neutralGun;
        Spawner *m_upwardGun;
        Spawner *m_downwardGun;
        Spawner *m_superGun;

        /// <summary>Executes the Ship's neutral attack.</summary>
        void Neutral();
        /// <summary>Executes the Ship's upward attack.</summary>
        void Upward();
        /// <summary>Executes the Ship's downward attack.</summary>
        void Downward();
        /// <summary>Executes the Ship's super attack.</summary>
        void Super();
        /// <summary>Handles the actual spawning/firing of the Ship's neutral attack.</summary>
        virtual void FireNeutral() = 0;
        /// <summary>Handles the actual spawning/firing of the Ship's upward attack.</summary>
        virtual void FireUpward() = 0;
        /// <summary>Handles the actual spawning/firing of the Ship's downward attack.</summary>
        virtual void FireDownward() = 0;
        /// <summary>Handles the actual spawning/firing of the Ship's super attack.</summary>
        virtual void FireSuper() = 0;
    };
}
