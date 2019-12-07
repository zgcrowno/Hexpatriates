#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "Ship.h"
#include "Zone.h"

namespace hexpatriates
{
    class Pilot : public ScrollMod
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
        //! Called on object separation
        virtual orxBOOL OnSeparate(ScrollObject *_poCollider);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
        //! Sets the Pilot's heads up text
        void SetHeadsUpText();
        //! Moves the Player based on user input and the passed speed
        virtual void Move(const orxCLOCK_INFO &_rstInfo, const bool &_bAllowVerticalMovement);
    public:
        //! Flag representing whether or not the Pilot is in their own zone.
        bool m_bIsInOwnZone;
        //! Flag representing whether or not the Pilot is on the ground or a platform.
        bool m_bIsGrounded;
        //! Flag representing whether or not the Pilot is against the left wall.
        bool m_bIsAgainstLeftWall;
        //! Flag representing whether or not the Pilot is against the right wall.
        bool m_bIsAgainstRightWall;
        //! Flag representing whether or not the Pilot would kill it's enemy when executing a melee attack
        bool m_bIsInMeleeRange;
        //! The amount of time, in seconds, remaining until the Pilot's ship reconstructs.
        float m_constructionTimer;
        //! The amount of time, in seconds, remaining until the Pilot dies of contamination.
        float m_contaminationTimer;
        //! Speed of movement
        float m_walkingSpeed;
        float m_flyingSpeed;
        float m_jumpingSpeed;
        float m_dashSpeed;
        //! The amount of time, in seconds, the Pilot's jump may last
        float m_jumpDuration;
        //! The amount of time, in seconds, the Pilot has to spend jumping
        float m_jumpTime;
        //! The amount of time, in seconds, the Pilot has to spend wall jumping
        float m_wallJumpTime;
        //! The amount of time, in seconds, the Pilot's dash lasts.
        float m_dashDuration;
        //! The amount of time, in seconds, the Pilot ought to dash.
        float m_dashTime;
        //! The amount of time, in seconds, the Pilot's melee attack lasts.
        float m_meleeDuration;
        //! The amount of time, in seconds, the Pilot has to spend melee attacking.
        float m_meleeTime;
        //! The maximum number of lives possibly held by the Pilot
        int m_maxLives;
        //! The number of lives held by the Pilot
        int m_lives;
        //! Maximum consecutive actions
        int m_maxDashes;
        //! Times actions have been used prior to cooldown
        int m_usedDashes;
        //! Maximum cooldowns
        float m_maxCooldownDash;
        float m_maxCooldownParry;
        float m_maxCooldownMelee;
        //! Cooldowns
        float m_cooldownDash;
        float m_cooldownParry;
        float m_cooldownMelee;
        //! The amount of time, in seconds, the Pilot's parry lasts
        float m_parryDuration;
        //! The amount of time, in seconds, the Pilot ought to parry
        float m_parryTime;
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
        float m_enemyDirection;
        //! The input strings
        const orxCHAR *m_upInput;
        const orxCHAR *m_leftInput;
        const orxCHAR *m_downInput;
        const orxCHAR *m_rightInput;
        const orxCHAR *m_leftRightInput;
        const orxCHAR *m_upDownInput;
        const orxCHAR *m_dashInput;
        const orxCHAR *m_parryInput;
        const orxCHAR *m_meleeInput;
        const orxCHAR *m_jumpInput;
        orxSTRING m_neutralInput;
        orxSTRING m_upwardInput;
        orxSTRING m_downwardInput;
        orxSTRING m_superInput;
        orxBOOL m_defaultFlipX;
        orxBOOL m_defaultFlipY;
        //! The Pilot's spawning position
        orxVECTOR m_defaultPosition;
        //! The direction in which the Pilot's jumping
        orxVECTOR m_jumpDirection;
        //! The direction in which the Pilot's dashing
        orxVECTOR m_dashDirection;
        //! The Pilot's construction/contamination text
        ScrollMod *m_headsUpText;
        // TODO: Get rid of these once I've got final animations in order
        ScrollMod *m_parryObject;
        ScrollMod *m_meleeObject;
        //! The Pilot's zone
        Zone *m_zone;
        //! The Pilot's ship
        Ship *m_ship;
        //! The opposing pilot
        Pilot *m_opposingPilot;

        // This modified version of ScrollObject's SetScale method is necessary for Pilot, so we can reverse unintended solidification of the Pilot's ship body part.
        // void SetScale(const orxVECTOR &_rvScale, orxBOOL _bShipSolid, orxBOOL _bWorld = 0U);
        // This modified version of ScrollObject's SetFlip method is necessary for Pilot, so we can apply selectively recursive flipping.
        void SetFlip(orxBOOL _bFlipX, orxBOOL _vFlipY);
        /// <summary>Executes the Pilot's jump maneuver.</summary>
        void Jump(const orxCLOCK_INFO &_rstInfo);
        /// <summary>Executes the Pilot's dash maneuver.</summary>
        void Dash();
        /// <summary>Executes the Pilot's parry maneuver.</summary>
        void Parry();
        /// <summary>Executes the Pilot's melee attack.</summary>
        void Melee();
        /// <summary>Destroy's the Pilot's ship.</summary>
        void DestroyShip();
        /// <summary>Reconstructs the Pilot's ship.</summary>
        void ConstructShip();
        /// <summary>Kills the Pilot.</summary>
        void Die();
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
