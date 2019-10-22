#include "Pilot.h"
#include "Projectile.h"

using namespace hexpatriates;

void Pilot::OnCreate()
{
    // Get movement speed from config values.
    m_walkingSpeed = orxConfig_GetFloat("WalkingSpeed");
    m_flyingSpeed = orxConfig_GetFloat("FlyingSpeed");
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
    m_dashMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-DashMeter"));
    m_parryMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-ParryMeter"));
    m_livesMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-LivesMeter"));
    // Set the UI elements' default scales
    orxVECTOR variableScale = orxVECTOR_0;
    m_defaultScaleDash = m_dashMeter->GetScale(variableScale);
    m_defaultScaleParry = m_parryMeter->GetScale(variableScale);
    m_defaultScaleLives = m_livesMeter->GetScale(variableScale);
    // Set the Character's pilot and ship
    m_ship = static_cast<Ship*>(GetChildByName("O-Ship"));
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
    if (orxString_Compare(_zPartName, "BP-Pilot") == 0
        && orxString_Compare(_zColliderPartName, "BP-Partition") == 0)
    {
        DestroyShip();
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

            if (orxInput_IsActive("Up"))
            {
                movement.fY -= speed * _rstInfo.fDT;
            }
            if (orxInput_IsActive("Down"))
            {
                movement.fY += speed * _rstInfo.fDT;
            }
        }
        if (orxInput_IsActive("Left"))
        {
            movement.fX -= speed * _rstInfo.fDT;
        }
        if (orxInput_IsActive("Right"))
        {
            movement.fX += speed * _rstInfo.fDT;
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

void Pilot::Dash()
{
    if (orxInput_HasBeenActivated("Dash"))
    {
        // Only execute dash input if the Character isn't currently dashing or waiting out a dash cooldown.
        if (m_dashTime <= 0 && m_cooldownDash <= 0)
        {
            m_dashDirection = { orxInput_GetValue("Right") - orxInput_GetValue("Left"), orxInput_GetValue("Down") - orxInput_GetValue("Up"), 0 };
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
    if (orxInput_HasBeenActivated("Parry"))
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
    if (orxInput_HasBeenActivated("Neutral"))
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
    // Set BP-Ship to non-solid so the pilot will won't be kept a certain distance from other solid objects.
    SetBodyPartSolid("BP-Ship", orxFALSE);
}
