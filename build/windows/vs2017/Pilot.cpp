#include "Pilot.h"
#include "Projectile.h"
#include <iostream>

using namespace hexpatriates;

void Pilot::OnCreate()
{
    // Get movement speed from config values.
    m_walkingSpeed = orxConfig_GetFloat("WalkingSpeed");
    m_flyingSpeed = orxConfig_GetFloat("FlyingSpeed");
    m_jumpingSpeed = orxConfig_GetFloat("JumpingSpeed");
    // Get jump duration from config values.
    m_jumpDuration = orxConfig_GetFloat("JumpDuration");
    // Get dash speed from config values.
    m_dashSpeed = orxConfig_GetFloat("DashSpeed");
    // Get dash duration from config values.
    m_dashDuration = orxConfig_GetFloat("DashDuration");
    // Get parry duration from config values.
    m_parryDuration = orxConfig_GetFloat("ParryDuration");
    // Get maximum number of lives.
    m_maxLives = orxConfig_GetFloat("MaxLives");
    m_lives = m_maxLives;
    // Get maximum consecutive actions from config values
    m_maxDashes = orxConfig_GetFloat("MaxDashes");
    // Get maximum cooldowns from config values
    m_maxCooldownDash = orxConfig_GetFloat("MaxCooldownDash");
    m_maxCooldownParry = orxConfig_GetFloat("MaxCooldownParry");
    m_maxCooldownMelee = orxConfig_GetFloat("MaxCooldownMelee");
    // Create and assign the Pilot's associated UI elements.
    m_dashMeter = static_cast<ScrollMod*>(GetChildByName({ "O-DashMeterP1", "O-DashMeterP2" }));
    m_parryMeter = static_cast<ScrollMod*>(GetChildByName({ "O-ParryMeterP1", "O-ParryMeterP2" }));
    m_livesMeter = static_cast<ScrollMod*>(GetChildByName({ "O-LivesMeterP1", "O-LivesMeterP2" }));
    // Set the UI elements' default scales
    orxVECTOR variableScale = orxVECTOR_0;
    m_defaultScaleDash = m_dashMeter->GetScale(variableScale);
    m_defaultScaleParry = m_parryMeter->GetScale(variableScale);
    m_defaultScaleLives = m_livesMeter->GetScale(variableScale);
    // Set the Character's pilot and ship
    m_ship = static_cast<Ship*>(GetChildByName({ "O-ShipP1", "O-ShipP2" }));

    if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
    {
        m_upInput = "UpP1";
        m_leftInput = "LeftP1";
        m_downInput = "DownP1";
        m_rightInput = "RightP1";
        m_leftRightInput = "LeftRightP1";
        m_upDownInput = "UpDownP1";
        m_dashInput = "DashP1";
        m_parryInput = "ParryP1";
        m_meleeInput = "NeutralP1";
        m_jumpInput = "DownwardP1";
    }
    else
    {
        m_upInput = "UpP2";
        m_leftInput = "LeftP2";
        m_downInput = "DownP2";
        m_rightInput = "RightP2";
        m_leftRightInput = "LeftRightP2";
        m_upDownInput = "UpDownP2";
        m_dashInput = "DashP2";
        m_parryInput = "ParryP2";
        m_meleeInput = "NeutralP2";
        m_jumpInput = "DownwardP2";
    }
}

void Pilot::OnDelete()
{
    
}

orxBOOL Pilot::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    // TODO: I'll probably make some sort of zone check instead of this collision, as dashing seems to lessen the accuracy of this.
    if (orxString_Compare(_zPartName, "BP-PilotP1") == 0
        || orxString_Compare(_zPartName, "BP-PilotP2") == 0)
    {
        if (orxString_Compare(_zColliderPartName, "BP-Partition") == 0)
        {
            DestroyShip();
        }
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0)
        {
            m_bIsGrounded = true;
        }
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallLeftWall") == 0
            || orxString_Compare(_poCollider->GetModelName(), "O-WallRightWall") == 0)
        {
            m_bIsAgainstWall = true;
        }
    }

    return orxTRUE;
}

orxBOOL Pilot::OnSeparate(ScrollObject *_poCollider)
{
    if (orxString_Compare(_poCollider->GetModelName(), "O-WallLeftWall") == 0
        || orxString_Compare(_poCollider->GetModelName(), "O-WallRightWall") == 0)
    {
        m_bIsAgainstWall = false;
    }

    return orxTRUE;
}

void Pilot::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Movement inputs.
    Dash();
    Move(_rstInfo);
    // Action inputs.
    Parry();
    if (m_ship->IsEnabled())
    {
        m_ship->Neutral();
        m_ship->Upward();
        m_ship->Downward();
        m_ship->Super();
    }
    else
    {
        Melee();
        Jump(_rstInfo);
    }
    // Handle jump time decrement
    if (m_jumpTime > 0)
    {
        m_jumpTime -= _rstInfo.fDT;
    }
    else
    {
        m_jumpTime = 0;
    }
    // Handle dash time decrement
    if (m_dashTime > 0)
    {
        m_dashTime -= _rstInfo.fDT;
    }
    else
    {
        m_dashTime = 0;
    }
    // Handle parry time decrement
    if (m_parryTime > 0)
    {
        m_parryTime -= _rstInfo.fDT;
    }
    else
    {
        m_parryTime = 0;
    }
    // Handle cooldowns
    if (m_cooldownDash > 0)
    {
        m_cooldownDash -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownDash = 0;
    }
    if (m_cooldownParry > 0)
    {
        m_cooldownParry -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownParry = 0;
    }
    if (m_cooldownMelee > 0)
    {
        m_cooldownMelee -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownMelee = 0;
    }
    // Handle UI appearance
    if (m_cooldownDash > 0)
    {
        m_dashMeter->SetScale({ m_defaultScaleDash.fX - (m_defaultScaleDash.fX * (m_cooldownDash / m_maxCooldownDash)), m_defaultScaleDash.fY, m_defaultScaleDash.fZ });
    }
    else
    {
        m_dashMeter->SetScale({ m_defaultScaleDash.fX - (m_defaultScaleDash.fX * ((float)m_usedDashes / (float)m_maxDashes)), m_defaultScaleDash.fY, m_defaultScaleDash.fZ });
    }
    m_parryMeter->SetScale({ m_defaultScaleParry.fX - (m_defaultScaleParry.fX * (m_cooldownParry / m_maxCooldownParry)), m_defaultScaleParry.fY, m_defaultScaleParry.fZ });
    m_livesMeter->SetScale({ m_defaultScaleLives.fX * ((float)m_lives / (float)m_maxLives), m_defaultScaleLives.fY, m_defaultScaleLives.fZ });
}

void Pilot::Move(const orxCLOCK_INFO &_rstInfo)
{
    orxVECTOR movement = orxVECTOR_0;

    // Only execute regular movement inputs if the Character isn't dashing.
    if (m_dashTime <= 0)
    {
        float speed = m_walkingSpeed;

        if (m_ship->IsEnabled())
        {
            speed = m_flyingSpeed;

            if (orxInput_IsActive(m_upDownInput))
            {
                movement.fY += speed * orxInput_GetValue(m_upDownInput) * _rstInfo.fDT;
            }
            else
            {
                if (orxInput_IsActive(m_upInput))
                {
                    movement.fY -= speed * _rstInfo.fDT;
                }
                if (orxInput_IsActive(m_downInput))
                {
                    movement.fY += speed * _rstInfo.fDT;
                }
            }
        }
        else
        {
            if (m_bIsAgainstWall)
            {
                if (orxInput_IsActive(m_upDownInput))
                {
                    m_jumpTime = 0;
                    movement.fY += speed * orxInput_GetValue(m_upDownInput) * _rstInfo.fDT;
                }
                else
                {
                    if (orxInput_IsActive(m_upInput))
                    {
                        m_jumpTime = 0;
                        movement.fY -= (GetWorldGravity().fY + speed) * _rstInfo.fDT;
                    }
                    if (orxInput_IsActive(m_downInput))
                    {
                        m_jumpTime = 0;
                        movement.fY += speed * _rstInfo.fDT;
                    }
                }
            }

            if (m_jumpTime > 0)
            {
                // Multiplying m_jumpingSpeed by its product to make for a more believable "dropping off" of the vertical velocity.
                movement.fY = (-(GetWorldGravity().fY + m_jumpingSpeed) * (m_jumpTime / m_jumpDuration)) * _rstInfo.fDT;
            }
        }
        if (orxInput_IsActive(m_leftRightInput))
        {
            movement.fX += speed * orxInput_GetValue(m_leftRightInput) * _rstInfo.fDT;
        }
        else
        {
            if (orxInput_IsActive(m_leftInput))
            {
                movement.fX -= speed * _rstInfo.fDT;
            }
            if (orxInput_IsActive(m_rightInput))
            {
                movement.fX += speed * _rstInfo.fDT;
            }
        }
    }
    // Otherwise, execute dash movement
    else
    {
        movement.fX = m_dashDirection.fX * m_dashSpeed * _rstInfo.fDT;
        movement.fY = m_dashDirection.fY * m_dashSpeed * _rstInfo.fDT;
    }
    SetSpeed(movement, orxFALSE);
}

void Pilot::Jump(const orxCLOCK_INFO &_rstInfo)
{
    if (m_bIsGrounded && orxInput_HasBeenActivated(m_jumpInput))
    {
        m_jumpTime = m_jumpDuration;
        m_bIsGrounded = orxFALSE;
    }
    else if (orxInput_HasBeenDeactivated(m_jumpInput))
    {
        m_jumpTime = 0;
    }
}

void Pilot::Dash()
{
    if (orxInput_HasBeenActivated(m_dashInput))
    {
        // Only execute dash input if the Character isn't currently dashing or waiting out a dash cooldown.
        if (m_dashTime <= 0 && m_cooldownDash <= 0)
        {
            if (orxInput_GetValue(m_leftRightInput) != 0 || orxInput_GetValue(m_upDownInput) != 0)
            {
                m_dashDirection = { orxInput_GetValue(m_leftRightInput), orxInput_GetValue(m_upDownInput) };
            }
            else
            {
                m_dashDirection = { orxInput_GetValue(m_rightInput) - orxInput_GetValue(m_leftInput), orxInput_GetValue(m_downInput) - orxInput_GetValue(m_upInput), 0 };
            }

            m_jumpTime = 0;
            m_dashTime = m_dashDuration;
            m_usedDashes++;

            if (m_usedDashes == m_maxDashes)
            {
                m_usedDashes = 0;
                m_cooldownDash = m_maxCooldownDash;
            }
        }
    }
}

void Pilot::Parry()
{
    if (orxInput_HasBeenActivated(m_parryInput))
    {
        if (m_cooldownParry <= 0)
        {
            m_parryTime = m_parryDuration;
            m_cooldownParry = m_maxCooldownParry;
        }
    }
}

void Pilot::Melee()
{
    if (orxInput_HasBeenActivated(m_meleeInput))
    {
        if (m_cooldownMelee <= 0)
        {
            m_cooldownMelee = m_maxCooldownMelee;
        }
    }
}

void Pilot::DestroyShip()
{
    // Disable the ship
    m_ship->Enable(orxFALSE);
    // Set custom gravity to world's gravity
    SetCustomGravity(GetWorldGravity());
    // Set BP-Ship to non-solid so the pilot won't be kept a certain distance from other solid objects.
    SetBodyPartSolid("BP-Ship", orxFALSE);
}
