#include "Pilot2.h"

using namespace hexpatriates;

void Pilot2::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot2::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot2::OnCollide(
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

void Pilot2::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot2::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
    }
}

void Pilot2::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_4));
    }
}

void Pilot2::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        float shotDirection = orxMath_GetRandomFloat(GetPISD(orxMATH_KF_PI_BY_8), GetPISD(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_8));
        m_ship->m_downwardGun->SpawnAtSelf(shotDirection);

        std::vector<orxVECTOR> raycastData = ScrollMod::Raycast(
            m_ship->m_downwardGun->GetPosition(true),
            shotDirection,
            orxPhysics_GetCollisionFlagValue("geometry"));
        float normalDirection = ScrollMod::VectorToRadians(raycastData.at(1));

        ScrollMod *laserPortalEntrance;
        if (m_bIsP1)
        {
            laserPortalEntrance = CreateObject("O-LaserPortalEntranceP1", {}, { {"ExitDirection", normalDirection} }, { {"Position", &raycastData.at(0)} });
        }
        else
        {
            laserPortalEntrance = CreateObject("O-LaserPortalEntranceP2", {}, { {"ExitDirection", normalDirection} }, { {"Position", &raycastData.at(0)} });
        }
    }
}

void Pilot2::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        m_ship->m_superGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 + (i * orxMATH_KF_PI_BY_16)));
    }
}
