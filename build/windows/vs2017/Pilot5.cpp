#include "Pilot5.h"
#include <iostream>

using namespace hexpatriates;

void Pilot5::OnCreate()
{
    Pilot::OnCreate();

    m_shipPoundSpeed = GetFloat("ShipPoundSpeed", GetModelName());
}

void Pilot5::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot5::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Pilot::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void Pilot5::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);

    // Handle ShipPoundShockwave behavior
    if (m_ship->m_bIsAgainstFloor && m_bIsShipPounding)
    {
        ShipPoundShockwave();
    }
}

void Pilot5::Move(const orxCLOCK_INFO &_rstInfo, const bool &_bAllowVerticalMovement)
{
    if (m_bIsShipPounding)
    {
        SetSpeed({ 0, m_shipPoundSpeed });
    }
    else
    {
        Pilot::Move(_rstInfo, m_stance != Grounded);
    }
}

void Pilot5::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        if (m_stance == Stance::Airborne)
        {
            m_ship->m_neutralGun->SpawnAtSelf(m_enemyDirection);
        }
        else // m_stance == Stance::Grounded
        {
            int typeLength = strlen("P1");
            orxCHAR crosshairsText[512] = "O-Crosshairs";
            orxCHAR crosshairsTypeText[512];
            ScrollMod::Substring(GetModelName(), crosshairsTypeText, strlen(GetModelName()) - typeLength, typeLength);

            orxVECTOR opposingPilotPosition = m_opposingPilot->GetPosition();
            orxVECTOR spawnPosition = { opposingPilotPosition.fX, opposingPilotPosition.fY, GetVector("Position", "O-Crosshairs").fZ };
            CreateObject(strcat(crosshairsText, crosshairsTypeText), {}, {}, { {"Position", &spawnPosition} });
        }
    }
}

void Pilot5::FireUpward()
{
    if (m_stance == Stance::Grounded)
    {
        SwitchStance();
        // Resetting this here so the base class doesn't keep iterating as if the upward gun was fired.
        m_wavesIndexUpward = 0;
    }
    else // m_stance == Stance::Airborne
    {
        for (int i = 0; i < m_waveSizeUpward; i++)
        {
            float shotDirection = orxMath_GetRandomFloat(-orxMATH_KF_PI_BY_8, -orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_8);
            m_ship->m_upwardGun->SpawnAtSelf(shotDirection);
        }
    }
}

void Pilot5::FireDownward()
{
    if (m_stance == Stance::Airborne)
    {
        SwitchStance();
        // Resetting this here so the base class doesn't keep iterating as if the downward gun was fired.
        m_wavesIndexDownward = 0;
    }
    else // m_stance == Stance::Grounded
    {
        for (int i = 0; i < m_waveSizeDownward; i++)
        {
            m_ship->m_downwardGun->SpawnAtSelf(orxMATH_KF_PI_BY_8 - (m_wavesIndexDownward * (orxMATH_KF_PI_BY_8 / m_numWavesDownward)));
        }
    }
}

void Pilot5::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        int typeLength = strlen("P1");
        orxCHAR missileShieldText[512] = "O-MissileShield";
        orxCHAR missileShieldTypeText[512];
        ScrollMod::Substring(GetModelName(), missileShieldTypeText, strlen(GetModelName()) - typeLength, typeLength);

        orxVECTOR opposingPilotPosition = m_opposingPilot->GetPosition();
        orxVECTOR spawnPosition = { opposingPilotPosition.fX, opposingPilotPosition.fY, GetVector("Position", "O-MissileShield").fZ };
        CreateObject(strcat(missileShieldText, missileShieldTypeText), {}, {}, { {"Position", &spawnPosition} });
    }
}

void Pilot5::SwitchStance()
{
    if (m_stance == Stance::Airborne)
    {
        m_stance = Stance::Grounded;
        m_bIsShipPounding = true;
        SetCustomGravity(GetWorldGravity());
    }
    else // m_stance == Stance::Grounded
    {
        m_stance = Stance::Airborne;
        SetCustomGravity(GetVector("CustomGravity", GetModelName()));
    }
}

void Pilot5::ShipPoundShockwave()
{
    m_bIsShipPounding = false;

    ScrollMod *shockwaveLeft = CreateObject("O-ShockwaveP1");
    ScrollMod *shockwaveRight = CreateObject("O-ShockwaveP1");
    shockwaveLeft->SetPosition({ GetPosition().fX, GetPosition().fY + GetScaledSize().fY / 2 });
    shockwaveRight->SetPosition({ GetPosition().fX, GetPosition().fY + GetScaledSize().fY / 2 });
    shockwaveLeft->SetSpeed({ -GetFloat("Speed", shockwaveLeft->GetModelName()), 0 });
    shockwaveRight->SetSpeed({ GetFloat("Speed", shockwaveLeft->GetModelName()), 0 });
}
