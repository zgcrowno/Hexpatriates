#include "Pilot.h"
#include "Projectile.h"

using namespace hexpatriates;

void Pilot::OnCreate()
{
    // Get 2nd player flag from config values.
    m_bIsP2 = GetBool("IsP2", GetModelName());
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
    // Set the Pilot's ship.
    m_ship = static_cast<Ship*>(GetChildByName({ "O-ShipP1", "O-ShipP2" }));

    if (m_bIsP2)
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
    else
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
        if (orxString_SearchString(_zColliderPartName, "Pilot") != orxNULL)
        {
            Pilot *collidingPilot = (Pilot*)_poCollider;
            if (collidingPilot->m_meleeTime > 0)
            {
                Die();
            }
        }
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0)
        {
            m_bIsGrounded = true;
            m_jumpTime = 0;
            m_wallJumpTime = 0;
        }
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallLeftWall") == 0)
        {
            m_bIsAgainstLeftWall = true;
        }
        else if (orxString_Compare(_poCollider->GetModelName(), "O-WallRightWall") == 0)
        {
            m_bIsAgainstRightWall = true;
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
        RemoveFX("FX-Parry");
        m_parryTime = 0;
    }
    // Handle melee time decrement
    if (m_meleeTime > 0)
    {
        m_meleeTime -= _rstInfo.fDT;
    }
    else
    {
        RemoveFX("FX-Melee");
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

void Pilot::SetScale(const orxVECTOR &_rvScale, orxBOOL _bShipSolid, orxBOOL _bWorld)
{
    ScrollObject::SetScale(_rvScale, _bWorld);
    SetBodyPartSolid("BP-Ship", _bShipSolid);
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

            if (leftRightValue > 0)
            {
                SetTargetAnim("A-PilotRun");
                SetScale({ 1, 1, 1 }, m_ship->IsEnabled());
            }
            else if (leftRightValue < 0)
            {
                SetTargetAnim("A-PilotRun");
                SetScale({ -1, 1, 1 }, m_ship->IsEnabled());
            }
            else
            {
                SetTargetAnim("A-PilotIdle");
            }
            movement.fX += speed * leftRightValue * _rstInfo.fDT;
        }
        else
        {
            if (orxInput_IsActive(m_leftInput))
            {
                SetTargetAnim("A-PilotRun");
                SetScale({ -1, 1, 1 }, m_ship->IsEnabled());
                movement.fX -= speed * _rstInfo.fDT;
            }
            else if (orxInput_IsActive(m_rightInput))
            {
                SetTargetAnim("A-PilotRun");
                SetScale({ 1, 1, 1 }, m_ship->IsEnabled());
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
    SetSpeed(movement, orxFALSE);
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
            AddFX("FX-Parry");
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
            AddFX("FX-Melee");
            m_meleeTime = m_meleeDuration;
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

void Pilot::Die()
{
    if (m_ship->IsEnabled())
    {
        DestroyShip();
    }
    Enable(orxFALSE);
}
