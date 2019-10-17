#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "Ship.h"

namespace hexpatriates
{
    class Pilot : public ScrollMod
    {
    private:
        //! Associated UI elements' default scales
        // TODO: At least for these default scales, I should probably put together a UI manager to handle data like this. OR, make fully fleshed out classes for these UI elements.
        orxVECTOR m_defaultScaleDash;
        orxVECTOR m_defaultScaleParry;
        orxVECTOR m_defaultScaleLives;
        //! Associated UI elements
        ScrollMod *m_dashMeter;
        ScrollMod *m_parryMeter;
        ScrollMod *m_livesMeter;
        Pilot *m_pilot;
        Ship *m_ship;

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
        //! Moves the Player based on user input and the passed speed
        void Move(const orxCLOCK_INFO &_rstInfo);
    public:
        //! Speed of movement
        float m_walkingSpeed;
        float m_flyingSpeed;
        //! Dash speed
        float m_dashSpeed;
        //! The amount of time, in seconds, the Pilot's dash lasts.
        float m_dashDuration;
        //! The amount of time, in seconds, the Pilot ought to dash.
        float m_dashTime;
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
        //! The amount of time, in seconds, the Pilot's parry lasts.
        float m_parryDuration;
        //! The amount of time, in seconds, the Pilot ought to parry.
        float m_parryTime;
        //! The direction in which the Pilot's dashing
        orxVECTOR m_dashDirection;

        /// <summary>Executes the Pilot's dash maneuver.</summary>
        void Dash();
        /// <summary>Executes the Pilot's parry maneuver.</summary>
        void Parry();
        /// <summary>Executes the Pilot's melee attack.</summary>
        void Melee();
        /// <summary>Destroy's the Pilot's ship.</summary>
        void DestroyShip();
    };
}
