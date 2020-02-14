#pragma once

#include "Hexpatriates.h"
#include "Agent.h"
#include "PlayerSpecific.h"
#include "Ship.h"
#include "Zone.h"
#include "ArenaBound.h"
#include "Projectile.h"

namespace hexpatriates
{
    class Pilot : public PlayerSpecific, public Agent
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
        virtual void SetActionMap();
        //! Sets the Pilot's heads up text
        void SetHeadsUpText();
        //! Manages Pilot movement
        virtual void ExecuteMovement();
        virtual void ExecuteJump();
        virtual void HandleMovementInput();
        virtual void HandleDashInput();
        virtual void HandleParryInput();
        virtual void HandleMeleeInput();
        virtual void HandleJumpInput();
        virtual void HandleNeutralInput();
        virtual void HandleUpwardInput();
        virtual void HandleDownwardInput();
        virtual void HandleSuperInput();
        //! Moves the Pilot based on the passed movement vector, direction and speed
        virtual void Move(orxVECTOR &_movementVec, const orxVECTOR &_direction, const float &_speed);
        //! Returns a bool which represents whether or not the Pilot can move vertically
        virtual bool CanMoveVertically();
    public:
        Action::ActionType m_movementType;
        //! The amount of time, in seconds, the Pilot is currently invulnerable.
        float m_iFrames;
        //! The maximum amount of time, in seconds, the Pilot is invulnerable after taking damage.
        float m_maxIFrames;
        //! Flag representing whether or not the Pilot is controlled by the computer.
        bool m_bIsAutomated;
        //! Flag representing whether or not the Pilot is currently downstabbing
        bool m_bIsDownstabbing;
        //! Flag representing whether or not the Pilot has just successfully parried.
        bool m_bJustParried;
        //! Flag representing whether or not the Pilot has canceled (reversed) their dash.
        bool m_bCanceledDash;
        //! Flag representing whether or not the Pilot is touching a MissileShield.
        bool m_bIsTouchingMissileShield;
        //! Flag representing whether or not the Pilot is on the ground or a platform.
        bool m_bIsGrounded;
        //! Flag representing whether or not the Pilot is against the ceiling.
        bool m_bIsAgainstCeiling;
        //! Flag representing whether or not the Pilot is against the left wall.
        bool m_bIsAgainstLeftWall;
        //! Flag representing whether or not the Pilot is against the right wall.
        bool m_bIsAgainstRightWall;
        //! Flag representing whether or not the Pilot would kill it's enemy when executing a melee attack
        bool m_bIsInMeleeRange;
        //! Flag representing whether or not the Pilot would kill its enemy when executing a melee attack
        bool m_bIsInDownstabRange;
        //! The amount of time, in seconds, remaining until the Pilot's ship reconstructs.
        float m_constructionTimer;
        //! The amount of time, in seconds, remaining until the Pilot dies of contamination.
        float m_contaminationTimer;
        //! Speed of movement
        float m_walkingSpeed;
        float m_flyingSpeed;
        float m_jumpingSpeed;
        float m_dashSpeed;
        float m_downstabSpeed;
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
        int m_waveSizeNeutral;
        int m_numWavesNeutral;
        int m_wavesIndexNeutral;
        float m_maxWaveDelayNeutral;
        float m_waveDelayNeutral;
        int m_waveSizeUpward;
        int m_numWavesUpward;
        int m_wavesIndexUpward;
        float m_maxWaveDelayUpward;
        float m_waveDelayUpward;
        int m_waveSizeDownward;
        int m_numWavesDownward;
        int m_wavesIndexDownward;
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
        std::string m_pauseInput;
        std::string m_upInput;
        std::string m_leftInput;
        std::string m_downInput;
        std::string m_rightInput;
        std::string m_leftRightInput;
        std::string m_upDownInput;
        std::string m_dashInput;
        std::string m_parryInput;
        std::string m_meleeInput;
        std::string m_jumpInput;
        std::string m_neutralInput;
        std::string m_upwardInput;
        std::string m_downwardInput;
        std::string m_superInput;
        orxBOOL m_defaultFlipX;
        orxBOOL m_defaultFlipY;
        //! The Pilot's movement vector
        orxVECTOR m_movement;
        //! The Pilot's aggressive movement vector
        orxVECTOR m_movementAggressive;
        //! The Pilot's defensive movement vector
        orxVECTOR m_movementDefensive;
        //! The Pilot's spawning position
        orxVECTOR m_defaultPosition;
        //! The direction in which the Pilot's jumping
        orxVECTOR m_jumpDirection;
        //! The direction in which the Pilot's dashing
        orxVECTOR m_dashDirection;
        //! The direction in which the Pilot's aggressively dashing.
        orxVECTOR m_dashDirectionAggressive;
        //! The direction in which the Pilot's defensively dashing.
        orxVECTOR m_dashDirectionDefensive;
        orxVECTOR m_noDashIconDefaultScale;
        orxVECTOR m_noParryIconDefaultScale;
        ScrollMod *m_noDashIcon;
        ScrollMod *m_noParryIcon;
        //! The Pilot's construction/contamination text
        ScrollMod *m_headsUpText;
        // TODO: Get rid of these once I've got final animations in order
        ScrollMod *m_parryObject;
        ScrollMod *m_meleeObject;
        ScrollMod *m_downstabObject;
        //! The Pilot's zone
        Zone *m_zone;
        //! The Pilot's ship
        Ship *m_ship;
        //! The opposing pilot
        Pilot *m_opposingPilot;
        //! Pilot contexts
        Context *m_contextInShip;
        Context *m_contextGrounded;
        Context *m_contextJumping;

        // Player independent shot direction, where _angle is in radians.
        const float GetPISD(const float &_angle) const;
        // This modified version of ScrollObject's SetFlip method is necessary for Pilot, so we can apply selectively recursive flipping.
        void SetFlip(orxBOOL _bFlipX, orxBOOL _vFlipY);
        virtual bool NeutralIsAvailable();
        virtual bool UpwardIsAvailable();
        virtual bool DownwardIsAvailable();
        virtual bool SuperIsAvailable();
        float GetMaxMatchTime();
        float GetRemainingMatchTime();
        ScrollMod *GetPartition();
        Projectile *GetMostPressingProjectile();
        void PositionIcons();
        /// <summary>Returns a bool representing whether or not the Pilot is in their own zone.</summary>
        /// <returns>A bool representing whether or not the Pilot is in their own zone.</returns>
        bool IsInOwnZone();
        /// <summary>Applies damage to Pilot.</summary>
        void TakeDamage();
        /// <summary>Spawns the appropriate dash icon behind the player.</summary>
        void SpawnDashIcon();
        /// <summary>Executes the Pilot's jump maneuver.</summary>
        void Jump();
        /// <summary>Stops the Pilot's jump maneuver.
        void Fall();
        /// <summary>Executes the Pilot's dash maneuver.</summary>
        void Dash(orxVECTOR &_dashVec, const orxVECTOR &_direction);
        /// <summary>Executes the Pilot's parry maneuver.</summary>
        void Parry();
        /// <summary>Executes the Pilot's melee attack.</summary>
        void Melee();
        /// <summary>Executes the Pilot's downstab attack.</summary>
        void Downstab(const bool _downstab);
        /// <summary>Destroy's the Pilot's ship.</summary>
        virtual void DestroyShip();
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
        virtual void FireNeutral(int &_indexInWave) = 0;
        /// <summary>Handles the actual spawning/firing of the Ship's upward attack.</summary>
        virtual void FireUpward(int &_indexInWave) = 0;
        /// <summary>Handles the actual spawning/firing of the Ship's downward attack.</summary>
        virtual void FireDownward(int &_indexInWave) = 0;
        /// <summary>Handles the actual spawning/firing of the Ship's super attack.</summary>
        virtual void FireSuper(int &_indexInWave) = 0;
        /// <summary>Handles the Pilot's super cooldown management, which may change marginally between Pilots.</summary>
        virtual void HandleSuperCooldown(const float &_fDT);
        /// <summary>Scores the action in terms of various factors.</summary>
        virtual int ScoreAction(Action *_action);
    };
}
