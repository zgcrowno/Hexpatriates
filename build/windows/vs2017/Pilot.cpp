#include "Pilot.h"
#include "Laser.h"
#include "LaserWall.h"
#include "Missile.h"
#include "MissileShield.h"
#include "Orb.h"
#include <string>

using namespace hexpatriates;

void Pilot::OnCreate()
{
    PlayerSpecific::OnCreate();

    // Set The iFrames.
    m_maxIFrames = GetFloat("MaxIFrames", GetModelName());
    // Set the construction timer to its default value.
    m_constructionTimer = 10;
    // Set the contamination timer to its default value.
    m_contaminationTimer = 10;
    // Get movement speed from config values.
    m_walkingSpeed = GetFloat("WalkingSpeed", GetModelName());
    m_flyingSpeed = GetFloat("FlyingSpeed", GetModelName());
    m_jumpingSpeed = GetFloat("JumpingSpeed", GetModelName());
    // Get jump duration from config values.
    m_jumpDuration = GetFloat("JumpDuration", GetModelName());
    // Get dash speed from config values.
    m_dashSpeed = GetFloat("DashSpeed", GetModelName());
    // Get dash duration from config values.
    m_dashDuration = GetFloat("DashDuration", GetModelName());
    // Get parry duration from config values.
    m_parryDuration = GetFloat("ParryDuration", GetModelName());
    // Get melee duration from config values.
    m_meleeDuration = GetFloat("MeleeDuration", GetModelName());
    // Get maximum number of lives.
    m_maxLives = GetFloat("MaxLives", GetModelName());
    m_lives = m_maxLives;
    // Get maximum consecutive actions from config values
    m_maxDashes = GetFloat("MaxDashes", GetModelName());
    // Get maximum cooldowns from config values
    m_maxCooldownDash = GetFloat("MaxCooldownDash", GetModelName());
    m_maxCooldownParry = GetFloat("MaxCooldownParry", GetModelName());
    m_maxCooldownMelee = GetFloat("MaxCooldownMelee", GetModelName());
    m_clipSizeNeutral = GetFloat("ClipSizeNeutral", GetModelName());
    m_clipSizeUpward = GetFloat("ClipSizeUpward", GetModelName());
    m_clipSizeDownward = GetFloat("ClipSizeDownward", GetModelName());
    m_waveSizeNeutral = GetFloat("WaveSizeNeutral", GetModelName());
    m_waveSizeUpward = GetFloat("WaveSizeUpward", GetModelName());
    m_waveSizeDownward = GetFloat("WaveSizeDownward", GetModelName());
    m_waveSizeSuper = GetFloat("WaveSizeSuper", GetModelName());
    m_numWavesNeutral = GetFloat("NumWavesNeutral", GetModelName());
    m_numWavesUpward = GetFloat("NumWavesUpward", GetModelName());
    m_numWavesDownward = GetFloat("NumWavesDownward", GetModelName());
    m_numWavesSuper = GetFloat("NumWavesSuper", GetModelName());
    m_maxCooldownNeutral = GetFloat("MaxCooldownNeutral", GetModelName());
    m_maxCooldownUpward = GetFloat("MaxCooldownUpward", GetModelName());
    m_maxCooldownDownward = GetFloat("MaxCooldownDownward", GetModelName());
    m_maxCooldownSuper = GetFloat("MaxCooldownSuper", GetModelName());
    m_maxWaveDelayNeutral = GetFloat("MaxWaveDelayNeutral", GetModelName());
    m_maxWaveDelayUpward = GetFloat("MaxWaveDelayUpward", GetModelName());
    m_maxWaveDelayDownward = GetFloat("MaxWaveDelayDownward", GetModelName());
    m_maxWaveDelaySuper = GetFloat("MaxWaveDelaySuper", GetModelName());
    m_cooldownSuper = m_maxCooldownSuper;
    // Get inputs.
    m_pauseInput = GetString("PauseInput", GetModelName());
    m_upInput = GetString("UpInput", GetModelName());
    m_leftInput = GetString("LeftInput", GetModelName());
    m_downInput = GetString("DownInput", GetModelName());
    m_rightInput = GetString("RightInput", GetModelName());
    m_leftRightInput = GetString("LeftRightInput", GetModelName());
    m_upDownInput = GetString("UpDownInput", GetModelName());
    m_dashInput = GetString("DashInput", GetModelName());
    m_parryInput = GetString("ParryInput", GetModelName());
    m_meleeInput = GetString("MeleeInput", GetModelName());
    m_jumpInput = GetString("JumpInput", GetModelName());
    if (m_bIsP1)
    {
        m_zone = (Zone*)CreateObject("O-ZoneP1");
        m_neutralInput = "NeutralP1";
        m_upwardInput = "UpwardP1";
        m_downwardInput = "DownwardP1";
        m_superInput = "SuperP1";
        m_enemyDirection = 0;
    }
    else
    {
        m_zone = (Zone*)CreateObject("O-ZoneP2");
        m_neutralInput = "NeutralP2";
        m_upwardInput = "UpwardP2";
        m_downwardInput = "DownwardP2";
        m_superInput = "SuperP2";
        m_enemyDirection = orxMATH_KF_PI;
    }
    // Set the Pilot's spawning position and flip
    m_defaultPosition = GetPosition();
    GetFlip(m_defaultFlipX, m_defaultFlipY);
    // Set the Pilot's construction/contamination text
    m_headsUpText = static_cast<ScrollMod*>(GetChildByName("O-HeadsUpText"));
    m_headsUpText->Enable(orxFALSE);
    // TODO: Get rid of these once I've got final animations in order
    m_parryObject = static_cast<ScrollMod*>(GetChildByName("O-Parry"));
    m_meleeObject = static_cast<ScrollMod*>(GetChildByName("O-Melee"));
    m_parryObject->Enable(orxFALSE);
    m_meleeObject->Enable(orxFALSE);
    // Set the Pilot's ship.
    m_ship = static_cast<Ship*>(GetChildByName({
        "O-Ship1P1",
        "O-Ship1P2",
        "O-Ship2P1",
        "O-Ship2P2",
        "O-Ship3P1",
        "O-Ship3P2",
        "O-Ship4P1",
        "O-Ship4P2",
        "O-Ship5P1",
        "O-Ship5P2",
        "O-Ship6P1",
        "O-Ship6P2",
        "O-Ship7P1",
        "O-Ship7P2",
        "O-Ship8P1",
        "O-Ship8P2", }));
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
    // Check for collisions with pilot body
    if (orxString_Compare(_zPartName, "BP-PilotP1") == 0
        || orxString_Compare(_zPartName, "BP-PilotP2") == 0)
    {
        // Projectile collisions
        if (dynamic_cast<Projectile*>(_poCollider) != NULL)
        {
            // Non-Parried collisions
            Parryable *parryable = dynamic_cast<Parryable*>(_poCollider);
            if (m_parryTime <= 0 || parryable == NULL)
            {
                // MissileShield collisions
                if (dynamic_cast<MissileShield*>(_poCollider) != NULL)
                {
                    m_bIsTouchingMissileShield = true;
                }
                else
                {
                    // Only deal damage if the Pilot isn't currently invincible.
                    if (m_iFrames <= 0)
                    {
                        // Only deal damage if the Pilot isn't both touching a missile shield and colliding with a missile.
                        if (dynamic_cast<Missile*>(_poCollider) == NULL || !m_bIsTouchingMissileShield)
                        {
                            TakeDamage();
                        }
                    }
                }
            }
        }
        // Zone collisions
        if (dynamic_cast<Zone*>(_poCollider) != orxNULL)
        {
            if (orxString_Compare(_poCollider->GetModelName(), m_zone->GetModelName().c_str()) == 0)
            {
                m_bIsInOwnZone = orxTRUE;
            }
            else
            {
                m_bIsInOwnZone = orxFALSE;
                if (m_ship->IsEnabled())
                {
                    TakeDamage();
                }
            }
        }
        // Floor collisions
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0)
        {
            m_bIsGrounded = true;
            m_jumpTime = 0;
            m_wallJumpTime = 0;
        }
        // Left wall collisions
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallLeftWall") == 0)
        {
            m_bIsAgainstLeftWall = true;
        }
        // Right wall collisions
        else if (orxString_Compare(_poCollider->GetModelName(), "O-WallRightWall") == 0)
        {
            m_bIsAgainstRightWall = true;
        }
    }
    // Check for collisions with melee body
    else if (orxString_SearchString(_zPartName, "Melee") != orxNULL)
    {
        // Pilot collisions
        Pilot *collidingPilot = dynamic_cast<Pilot*>(_poCollider);
        if (collidingPilot != orxNULL)
        {
            m_bIsInMeleeRange = orxTRUE;
            if (m_meleeTime > 0)
            {
                collidingPilot->Die();
            }
        }
    }

    return orxTRUE;
}

orxBOOL Pilot::OnSeparate(ScrollObject *_poCollider)
{
    if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0)
    {
        m_bIsGrounded = false;
    }
    if (orxString_Compare(_poCollider->GetModelName(), "O-WallLeftWall") == 0)
    {
        m_bIsAgainstLeftWall = false;
    }
    else if (orxString_Compare(_poCollider->GetModelName(), "O-WallRightWall") == 0)
    {
        m_bIsAgainstRightWall = false;
    }
    // Zone separations
    if (dynamic_cast<Zone*>(_poCollider) != orxNULL)
    {
        if (orxString_Compare(_poCollider->GetModelName(), m_zone->GetModelName().c_str()) == 0)
        {
            m_bIsInOwnZone = orxFALSE;
            DestroyShip();
        }
        else
        {
            m_bIsInOwnZone = orxTRUE;
        }
    }
    // MissileShield separations
    if (dynamic_cast<MissileShield*>(_poCollider) != NULL)
    {
        m_bIsTouchingMissileShield = false;
    }
    // TODO: I'll probably have to go about this another way, since the melee body part will likely be different from the pilot's body part.
    if (orxString_SearchString(_poCollider->GetModelName(), "Pilot") != orxNULL)
    {
        m_bIsInMeleeRange = orxFALSE;
    }

    return orxTRUE;
}

void Pilot::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Movement inputs.
    Dash();
    Move(_rstInfo, true);
    // Action inputs.
    Parry();
    if (m_ship->IsEnabled())
    {
        Neutral();
        Upward();
        Downward();
        Super();
    }
    else
    {
        Melee();
        Jump(_rstInfo);

        // Handle construction and contamination decrement and response
        if (m_bIsInOwnZone)
        {
            m_constructionTimer -= _rstInfo.fDT;

            if (m_constructionTimer <= 0 && IsEnabled())
            {
                ConstructShip();
            }
        }
        else
        {
            m_contaminationTimer -= _rstInfo.fDT;

            if (m_contaminationTimer <= 0)
            {
                Die();
            }
        }
        SetHeadsUpText();
    }
    // Handle iFrames decrement
    if (m_iFrames > 0)
    {
        m_iFrames -= _rstInfo.fDT;

        if (m_iFrames <= 0)
        {
            RemoveTrack("TT-IFramesFlash");
        }
    }
    else
    {
        m_iFrames = 0;
        
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
    // Handle wall jump time decrement
    if (m_wallJumpTime > 0)
    {
        m_wallJumpTime -= _rstInfo.fDT;
    }
    else
    {
        m_wallJumpTime = 0;
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
        m_parryObject->Enable(orxFALSE);
        m_parryTime = 0;
    }
    // Handle melee time decrement
    if (m_meleeTime > 0)
    {
        m_meleeTime -= _rstInfo.fDT;
    }
    else
    {
        m_meleeObject->Enable(orxFALSE);
        m_meleeTime = 0;
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
    if (m_cooldownNeutral > 0)
    {
        m_cooldownNeutral -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownNeutral = 0;
    }
    if (m_cooldownUpward > 0)
    {
        m_cooldownUpward -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownUpward = 0;
    }
    if (m_cooldownDownward > 0)
    {
        m_cooldownDownward -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownDownward = 0;
    }
    if (m_cooldownSuper > 0)
    {
        m_cooldownSuper -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownSuper = 0;
    }
    // Handle Waves
    if (m_wavesIndexNeutral != 0 && m_wavesIndexNeutral < m_numWavesNeutral)
    {
        if (m_waveDelayNeutral > 0)
        {
            m_waveDelayNeutral -= _rstInfo.fDT;
        }
        else
        {
            FireNeutral();
            m_wavesIndexNeutral++;
            m_waveDelayNeutral = m_maxWaveDelayNeutral;
        }
    }
    else
    {
        m_wavesIndexNeutral = 0;
        m_waveDelayNeutral = 0;
    }
    if (m_wavesIndexUpward != 0 && m_wavesIndexUpward < m_numWavesUpward)
    {
        if (m_waveDelayUpward > 0)
        {
            m_waveDelayUpward -= _rstInfo.fDT;
        }
        else
        {
            FireUpward();
            m_wavesIndexUpward++;
            m_waveDelayUpward = m_maxWaveDelayUpward;
        }
    }
    else
    {
        m_wavesIndexUpward = 0;
        m_waveDelayUpward = 0;
    }
    if (m_wavesIndexDownward != 0 && m_wavesIndexDownward < m_numWavesDownward)
    {
        if (m_waveDelayDownward > 0)
        {
            m_waveDelayDownward -= _rstInfo.fDT;
        }
        else
        {
            FireDownward();
            m_wavesIndexDownward++;
            m_waveDelayDownward = m_maxWaveDelayDownward;
        }
    }
    else
    {
        m_wavesIndexDownward = 0;
        m_waveDelayDownward = 0;
    }
    if (m_wavesIndexSuper != 0 && m_wavesIndexSuper < m_numWavesSuper)
    {
        if (m_waveDelaySuper > 0)
        {
            m_waveDelaySuper -= _rstInfo.fDT;
        }
        else
        {
            FireSuper();
            m_wavesIndexSuper++;
            m_waveDelaySuper = m_maxWaveDelaySuper;
        }
    }
    else
    {
        m_wavesIndexSuper = 0;
        m_waveDelaySuper = 0;
    }
}

const float Pilot::GetPISD(const float &_angle) const
{
    return m_bIsP1 ? _angle : orxMATH_KF_PI - _angle;
}

void Pilot::SetFlip(orxBOOL _bFlipX, orxBOOL _bFlipY)
{
    ScrollObject::SetFlip(_bFlipX, _bFlipY, orxFALSE);
    m_headsUpText->SetFlip(orxFALSE, orxFALSE, orxFALSE);
}

void Pilot::SetHeadsUpText()
{
    orxCHAR formattedHeadsUpText[3];
    orxCOLOR color;

    if (m_bIsInOwnZone)
    {
        orxString_Print(formattedHeadsUpText, "%1.0f", m_constructionTimer);
        color.vRGB = {0, 0.5, 1.0};
    }
    else
    {
        orxString_Print(formattedHeadsUpText, "%1.0f", m_contaminationTimer);
        color.vRGB = { 1.0, 0.5, 0 };
    }

    color.fAlpha = 1.0;
    orxObject_SetTextString(m_headsUpText->GetOrxObject(), formattedHeadsUpText);
    orxObject_SetColor(m_headsUpText->GetOrxObject(), &color);
}

void Pilot::Move(const orxCLOCK_INFO &_rstInfo, const bool &_bAllowVerticalMovement)
{
    orxVECTOR movement = orxVECTOR_0;

    // Only execute regular movement inputs if the Character isn't dashing.
    if (m_dashTime <= 0)
    {
        float speed = m_walkingSpeed;

        if (m_ship->IsEnabled())
        {
            speed = m_flyingSpeed;

            if (orxInput_IsActive(m_upDownInput.c_str()) && _bAllowVerticalMovement)
            {
                movement.fY += speed * orxInput_GetValue(m_upDownInput.c_str()) * _rstInfo.fDT;
            }
            else if (_bAllowVerticalMovement)
            {
                if (orxInput_IsActive(m_upInput.c_str()))
                {
                    movement.fY -= speed * _rstInfo.fDT;
                }
                if (orxInput_IsActive(m_downInput.c_str()))
                {
                    movement.fY += speed * _rstInfo.fDT;
                }
            }
        }
        else
        {
            if (m_bIsAgainstLeftWall || m_bIsAgainstRightWall)
            {
                if (orxInput_IsActive(m_upDownInput.c_str()))
                {
                    m_jumpTime = 0;
                    movement.fY += speed * orxInput_GetValue(m_upDownInput.c_str()) * _rstInfo.fDT;
                }
                else
                {
                    if (orxInput_IsActive(m_upInput.c_str()))
                    {
                        m_jumpTime = 0;
                        movement.fY -= (GetWorldGravity().fY + speed) * _rstInfo.fDT;
                    }
                    if (orxInput_IsActive(m_downInput.c_str()))
                    {
                        m_jumpTime = 0;
                        movement.fY += speed * _rstInfo.fDT;
                    }
                }
            }

            if (m_jumpTime > 0)
            {
                movement.fY = m_jumpDirection.fY * (GetWorldGravity().fY + m_jumpingSpeed) * (m_jumpTime / m_jumpDuration) * _rstInfo.fDT;
            }
            if (m_wallJumpTime > 0)
            {
                movement.fX = m_jumpDirection.fX * m_jumpingSpeed * (m_wallJumpTime / m_jumpDuration) * _rstInfo.fDT;
                movement.fY = m_jumpDirection.fY * (GetWorldGravity().fY + m_jumpingSpeed) * (m_wallJumpTime / m_jumpDuration) * _rstInfo.fDT;
            }
        }
        if (orxInput_IsActive(m_leftRightInput.c_str()))
        {
            float leftRightValue = orxInput_GetValue(m_leftRightInput.c_str());

            if (!m_ship->IsEnabled())
            {
                if (leftRightValue > 0)
                {
                    SetTargetAnim("A-PilotRun");
                    //SetFlip(orxFALSE, orxFALSE, orxFALSE);
                }
                else if (leftRightValue < 0)
                {
                    SetTargetAnim("A-PilotRun");
                    //SetFlip(orxTRUE, orxFALSE, orxFALSE);
                }
            }

            movement.fX += speed * leftRightValue * _rstInfo.fDT;
        }
        else
        {
            if (orxInput_IsActive(m_leftInput.c_str()))
            {
                if (!m_ship->IsEnabled())
                {
                    SetTargetAnim("A-PilotRun");
                    //SetFlip(orxTRUE, orxFALSE, orxFALSE);
                }

                movement.fX -= speed * _rstInfo.fDT;
            }
            else if (orxInput_IsActive(m_rightInput.c_str()))
            {
                if (!m_ship->IsEnabled())
                {
                    SetTargetAnim("A-PilotRun");
                    //SetFlip(orxFALSE, orxFALSE, orxFALSE);
                }
                
                movement.fX += speed * _rstInfo.fDT;
            }
            else
            {
                SetTargetAnim("A-PilotIdle");
            }
        }
    }
    // Otherwise, execute dash movement
    else
    {
        movement.fX = m_dashDirection.fX * m_dashSpeed * _rstInfo.fDT;
        movement.fY = m_dashDirection.fY * m_dashSpeed * _rstInfo.fDT;
    }
    SetSpeed(movement);
}

void Pilot::TakeDamage()
{
    if (m_ship->IsEnabled())
    {
        DestroyShip();
    }
    else
    {
        Die();
    }
    m_iFrames = m_maxIFrames;
    AddTrack("TT-IFramesFlash");
}

void Pilot::Jump(const orxCLOCK_INFO &_rstInfo)
{
    if (orxInput_HasBeenActivated(m_jumpInput.c_str()))
    {
        if (m_bIsGrounded)
        {
            m_jumpDirection = { 0, -1, 0 };
            m_jumpTime = m_jumpDuration;
        }
        else if (m_bIsAgainstLeftWall)
        {
            m_jumpDirection = { 1.6, -0.8, 0 };
            m_wallJumpTime = m_jumpDuration;
        }
        else if (m_bIsAgainstRightWall)
        {
            m_jumpDirection = { -1.6, -0.8, 0 };
            m_wallJumpTime = m_jumpDuration;
        }
    }
    else if (orxInput_HasBeenDeactivated(m_jumpInput.c_str()))
    {
        m_jumpTime = 0;
    }
}

void Pilot::Dash()
{
    if (orxInput_HasBeenActivated(m_dashInput.c_str()))
    {
        // Only execute dash input if the Character isn't currently dashing or waiting out a dash cooldown.
        if (m_dashTime <= 0 && m_cooldownDash <= 0)
        {
            if (orxInput_GetValue(m_leftRightInput.c_str()) != 0 || orxInput_GetValue(m_upDownInput.c_str()) != 0)
            {
                m_dashDirection = { orxInput_GetValue(m_leftRightInput.c_str()), orxInput_GetValue(m_upDownInput.c_str()) };
            }
            else
            {
                m_dashDirection = { orxInput_GetValue(m_rightInput.c_str()) - orxInput_GetValue(m_leftInput.c_str()), orxInput_GetValue(m_downInput.c_str()) - orxInput_GetValue(m_upInput.c_str()), 0 };
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
    if (orxInput_HasBeenActivated(m_parryInput.c_str()))
    {
        if (m_cooldownParry <= 0 && m_meleeTime <= 0)
        {
            m_parryObject->Enable(orxTRUE);
            m_parryTime = m_parryDuration;
            m_cooldownParry = m_maxCooldownParry;
        }
    }
}

void Pilot::Melee()
{
    if (orxInput_HasBeenActivated(m_meleeInput.c_str()))
    {
        if (m_cooldownMelee <= 0 && m_parryTime <= 0)
        {
            m_meleeObject->Enable(orxTRUE);
            m_meleeTime = m_meleeDuration;
            m_cooldownMelee = m_maxCooldownMelee;
            if (m_bIsInMeleeRange)
            {
                m_opposingPilot->Die();
            }
        }
    }
}

void Pilot::DestroyShip()
{
    // Disable the ship
    m_ship->Enable(orxFALSE);
    // Set custom gravity to world's gravity
    SetCustomGravity(GetWorldGravity());
    // Enable and set construction/contamination text
    m_headsUpText->Enable(orxTRUE);
    SetHeadsUpText();
}

void Pilot::ConstructShip()
{
    SetPosition(m_defaultPosition);
    //SetScale(m_defaultScale, orxTRUE);
    SetFlip(m_defaultFlipX, m_defaultFlipY);
    m_ship->Enable(orxTRUE);
    orxVECTOR customGravity = { 0, 0, 0 };
    SetCustomGravity(customGravity);
    m_constructionTimer = 10;
    m_contaminationTimer = 10;
    m_headsUpText->Enable(orxFALSE);
}

void Pilot::Die()
{
    if (m_ship->IsEnabled())
    {
        DestroyShip();
    }
    m_lives--;
    Enable(orxFALSE);
}

void Pilot::Neutral()
{
    if (orxInput_HasBeenActivated(m_neutralInput.c_str()))
    {
        if (m_cooldownNeutral <= 0 && m_wavesIndexNeutral == 0)
        {
            m_waveDelayNeutral = m_maxWaveDelayNeutral;

            m_clipIndexNeutral++;
            m_wavesIndexNeutral++;

            FireNeutral();

            if (m_clipIndexNeutral == m_clipSizeNeutral)
            {
                m_clipIndexNeutral = 0;
                m_cooldownNeutral = m_maxCooldownNeutral;
            }
        }
    }
}

void Pilot::Upward()
{
    if (orxInput_HasBeenActivated(m_upwardInput.c_str()))
    {
        if (m_cooldownUpward <= 0 && m_wavesIndexUpward == 0)
        {
            m_waveDelayUpward = m_maxWaveDelayUpward;

            m_clipIndexUpward++;
            m_wavesIndexUpward++;

            FireUpward();

            if (m_clipIndexUpward == m_clipSizeUpward)
            {
                m_clipIndexUpward = 0;
                m_cooldownUpward = m_maxCooldownUpward;
            }
        }
    }
}

void Pilot::Downward()
{
    if (orxInput_HasBeenActivated(m_downwardInput.c_str()))
    {
        if (m_cooldownDownward <= 0 && m_wavesIndexDownward == 0)
        {
            m_waveDelayDownward = m_maxWaveDelayDownward;

            m_clipIndexDownward++;
            m_wavesIndexDownward++;

            FireDownward();

            if (m_clipIndexDownward == m_clipSizeDownward)
            {
                m_clipIndexDownward = 0;
                m_cooldownDownward = m_maxCooldownDownward;
            }
        }
    }
}

void Pilot::Super()
{
    if (orxInput_HasBeenActivated(m_superInput.c_str()))
    {
        if (m_cooldownSuper <= 0 && m_wavesIndexSuper == 0)
        {
            m_wavesIndexSuper++;

            m_waveDelaySuper = m_maxWaveDelaySuper;

            m_cooldownSuper = m_maxCooldownSuper;

            FireSuper();

            m_cooldownSuper = m_maxCooldownSuper;
        }
    }
}
