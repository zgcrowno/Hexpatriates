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
        //! Moves the Player based on user input and the passed speed
        void Move(const orxCLOCK_INFO &_rstInfo);
    public:
        //! Flag representing whether or not the Pilot is in their own zone.
        bool m_bIsInOwnZone;
        //! Flag representing whether or not the Pilot is on the ground or a platform.
        bool m_bIsGrounded;
        //! Flag representing whether or not the Pilot is against the left wall.
        bool m_bIsAgainstLeftWall;
        //! Flag representing whether or not the Pilot is against the right wall.
        bool m_bIsAgainstRightWall;
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
        //! The Pilot's spawning position
        orxVECTOR m_defaultPosition;
        //! The direction in which the Pilot's jumping
        orxVECTOR m_jumpDirection;
        //! The direction in which the Pilot's dashing
        orxVECTOR m_dashDirection;
        //! The Pilot's zone
        Zone *m_zone;
        //! The Pilot's ship
        Ship *m_ship;

        // This modified version of ScrollObject's SetScale method is necessary for Pilot, so we can reverse unintended solidification of the Pilot's ship body part.
        void SetScale(const orxVECTOR &_rvScale, orxBOOL _bShipSolid, orxBOOL _bWorld = 0U);
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
    };
}
