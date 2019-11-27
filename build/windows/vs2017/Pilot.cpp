#include "Pilot.h"
#include "Laser.h"
#include "LaserWall.h"
#include "Orb.h"
#include "Ship6.h"
#include <string>

using namespace hexpatriates;

void Pilot::OnCreate()
{
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
    // Get inputs.
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
    // Check for collisions with pilot body--not ship body
    if (orxString_Compare(_zPartName, "BP-PilotP1") == 0
        || orxString_Compare(_zPartName, "BP-PilotP2") == 0)
    {
        // Zone collisions
        if (dynamic_cast<Zone*>(_poCollider) != orxNULL)
        {
            if (orxString_Compare(_poCollider->GetModelName(), m_zone->GetModelName()) == 0)
            {
                m_bIsInOwnZone = orxTRUE;
            }
            else
            {
                m_bIsInOwnZone = orxFALSE;
                DestroyShip();
            }
        }
        // Laser collisions
        if (dynamic_cast<Laser*>(_poCollider) != orxNULL)
        {
            if (m_parryTime <= 0)
            {
                if (m_ship->IsEnabled())
                {
                    DestroyShip();
                }
                else
                {
                    Die();
                }
            }
            else if (m_ship->IsEnabled())
            {
                SpawnFamiliar();
            }
        }
        // Orb collisions
        Orb *collidedOrb = dynamic_cast<Orb*>(_poCollider);
        if (collidedOrb != orxNULL)
        {
            if (m_parryTime > 0)
            {
                SpawnFamiliar();

                // Deflect the orb (we're basically replacing the orb with another one of the Pilot's type)
                // TODO: This should probably be done more efficiently
                orxCHAR *deflectedOrbModelName;
                if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
                {
                    deflectedOrbModelName = "O-OrbP1";
                }
                else
                {
                    deflectedOrbModelName = "O-OrbP2";
                }
                Orb *deflectedOrb = static_cast<Orb*>(CreateObject(deflectedOrbModelName));
                deflectedOrb->SetPosition(collidedOrb->GetPosition());
                deflectedOrb->SetSpeed({ -deflectedOrb->m_speed * _rvNormal.fX, -deflectedOrb->m_speed * _rvNormal.fY });
            }
            else
            {
                if (m_ship->IsEnabled())
                {
                    DestroyShip();
                }
                else
                {
                    Die();
                }
            }
            collidedOrb->Destroy();
        }
        // Laser wall collisions
        LaserWall *collidedLaserWall = dynamic_cast<LaserWall*>(_poCollider);
        if (collidedLaserWall != orxNULL)
        {
            if (m_ship->IsEnabled())
            {
                DestroyShip();
            }
            else
            {
                Die();
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
        if (orxString_Compare(_poCollider->GetModelName(), m_zone->GetModelName()) == 0)
        {
            m_bIsInOwnZone = orxFALSE;
            DestroyShip();
        }
        else
        {
            m_bIsInOwnZone = orxTRUE;
        }
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
            if (m_bIsAgainstLeftWall || m_bIsAgainstRightWall)
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
                movement.fY = m_jumpDirection.fY * (GetWorldGravity().fY + m_jumpingSpeed) * (m_jumpTime / m_jumpDuration) * _rstInfo.fDT;
            }
            if (m_wallJumpTime > 0)
            {
                movement.fX = m_jumpDirection.fX * m_jumpingSpeed * (m_wallJumpTime / m_jumpDuration) * _rstInfo.fDT;
                movement.fY = m_jumpDirection.fY * (GetWorldGravity().fY + m_jumpingSpeed) * (m_wallJumpTime / m_jumpDuration) * _rstInfo.fDT;
            }
        }
        if (orxInput_IsActive(m_leftRightInput))
        {
            float leftRightValue = orxInput_GetValue(m_leftRightInput);

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
            if (orxInput_IsActive(m_leftInput))
            {
                if (!m_ship->IsEnabled())
                {
                    SetTargetAnim("A-PilotRun");
                    //SetFlip(orxTRUE, orxFALSE, orxFALSE);
                }

                movement.fX -= speed * _rstInfo.fDT;
            }
            else if (orxInput_IsActive(m_rightInput))
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
    // If the Pilot is associated with a Ship that has familiars, ensure those familiars are correctly positioned upon movement
    Ship6 *familiarShip = dynamic_cast<Ship6*>(m_ship);
    if ((movement.fX != orxVECTOR_0.fX || movement.fY != orxVECTOR_0.fY) && familiarShip != NULL)
    {
        for (Familiar *familiar : familiarShip->m_familiars)
        {
            if (familiar->m_upcomingPositions.size() == familiar->m_framesBehind - 1)
            {
                familiar->Move();
            }
            familiar->m_upcomingPositions.push(GetPosition());
        }
    }
}

void Pilot::Jump(const orxCLOCK_INFO &_rstInfo)
{
    if (orxInput_HasBeenActivated(m_jumpInput))
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
    if (orxInput_HasBeenActivated(m_meleeInput))
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

void Pilot::SpawnFamiliar()
{
    Ship6 *familiarShip = dynamic_cast<Ship6*>(m_ship);
    if (familiarShip != NULL && familiarShip->m_familiars.size() < familiarShip->m_maxFamiliars - 1)
    {
        int typeLength = strlen("P1");
        orxCHAR familiarText[512] = "O-Familiar";
        orxCHAR pilotTypeText[512];
        ScrollMod::Substring(GetModelName(), pilotTypeText, strlen(GetModelName()) - typeLength, typeLength);
        orxVECTOR spawnPosition = {GetPosition().fX, GetPosition().fY, GetVector("Position", "O-Familiar").fZ};

        familiarShip->m_familiars.push_back(static_cast<Familiar*>(CreateObject(strcat(familiarText, pilotTypeText), {}, {}, { { "Position", &spawnPosition } })));
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
