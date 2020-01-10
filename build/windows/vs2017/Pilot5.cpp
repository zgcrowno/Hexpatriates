#include "Pilot5.h"

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

    // Check for collisions with ship body
    if (orxString_SearchString(_zPartName, "BP-Ship") != nullptr)
    {
        // Floor collisions
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0 && m_bIsShipPounding)
        {
            ShipPoundShockwave(_rvPosition);
        }
    }

    return true;
}

void Pilot5::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot5::Move(const bool &_bAllowVerticalMovement)
{
    if (m_bIsShipPounding)
    {
        SetSpeed({ 0, m_shipPoundSpeed });
    }
    else
    {
        Pilot::Move(m_stance != Grounded);
    }
}

void Pilot5::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        if (m_stance == Stance::Airborne)
        {
            m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
        }
        else // m_stance == Stance::Grounded
        {
            orxVECTOR opposingPilotPosition = m_opposingPilot->GetPosition();
            orxVECTOR spawnPosition = { opposingPilotPosition.fX, opposingPilotPosition.fY, GetVector("Position", "O-Crosshairs").fZ };
            CreateObject("O-Crosshairs" + m_typeName, {}, {}, { {"Position", &spawnPosition} });
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
            float shotDirection = orxMath_GetRandomFloat(GetPISD(-orxMATH_KF_PI_BY_8), GetPISD(-orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_8));
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
            m_ship->m_downwardGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_8 - (m_wavesIndexDownward * (orxMATH_KF_PI_BY_8 / m_numWavesDownward))));
        }
    }
}

void Pilot5::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        orxVECTOR zoneBottomRight = GetVector("BottomRight", "BP-Zone");
        float zoneWidth = zoneBottomRight.fX;
        float zoneHeight = zoneBottomRight.fY;
        orxVECTOR opposingZonePosition = m_opposingPilot->m_zone->GetPosition();
        orxVECTOR spawnPosition = { opposingZonePosition.fX + zoneWidth / 2.0f, opposingZonePosition.fY + zoneHeight / 2.0f, GetVector("Position", "O-MissileShield" + m_typeName).fZ };
        m_ship->m_superGun->SpawnAtPosition(0, spawnPosition);
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

void Pilot5::ShipPoundShockwave(const orxVECTOR &_shockwavePosition)
{
    m_bIsShipPounding = false;

    ScrollMod *shockwaveLeft = CreateObject("O-ShockwaveP1");
    ScrollMod *shockwaveRight = CreateObject("O-ShockwaveP1");
    shockwaveLeft->SetPosition(_shockwavePosition);
    shockwaveRight->SetPosition(_shockwavePosition);
    shockwaveLeft->SetSpeed({ -GetFloat("FSpeed", shockwaveLeft->GetModelName()), 0 });
    shockwaveRight->SetSpeed({ GetFloat("FSpeed", shockwaveLeft->GetModelName()), 0 });
}
