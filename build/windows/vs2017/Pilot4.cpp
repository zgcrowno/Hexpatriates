#include "Pilot4.h"

using namespace hexpatriates;

void Pilot4::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot4::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot4::OnCollide(
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

void Pilot4::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot4::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_ship->m_neutralGun->SpawnAtSelf(GetPISD((-orxMATH_KF_PI_BY_8) + (i * orxMATH_KF_PI_BY_8)));
    }
}

void Pilot4::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        const std::string spawnObjectModelName = m_ship->m_upwardGun->GetString("Object", m_ship->m_upwardGun->GetString("Spawner", m_ship->m_upwardGun->GetModelName()));
        ScrollMod *projectile = CreateObject(spawnObjectModelName);
        if (m_upwardOrigin.fY == orxVECTOR_0.fY)
        {
            m_upwardOrigin = Raycast(GetPosition(), GetPISD(-orxMATH_KF_PI_BY_2), orxPhysics_GetCollisionFlagValue("geometry")).at(0);
        }
        else
        {
            float projectileDistance = projectile->GetScaledSize().fX;
            m_upwardOrigin.fX += (copysignf(1, orxMath_Cos(m_enemyDirection)) * projectileDistance);
        }
        projectile->SetPosition(m_upwardOrigin);
        if (m_wavesIndexUpward == m_numWavesUpward - 1)
        {
            m_upwardOrigin = orxVECTOR_0;
        }
    }
}

void Pilot4::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        float shotDirection = GetPISD((orxMATH_KF_PI_BY_2 - orxMATH_KF_PI_BY_8) - (i * orxMATH_KF_PI_BY_8));
        //m_ship->m_downwardGun->SpawnAtRaycast(shotDirection);
        m_ship->m_downwardGun->SpawnAtSelf(shotDirection);
    }
}

void Pilot4::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        const std::string spawnObjectModelName = m_ship->m_upwardGun->GetString("Object", m_ship->m_upwardGun->GetString("Spawner", m_ship->m_upwardGun->GetModelName()));
        float projectileDistance;
        if (i < m_waveSizeSuper / 2)
        {
            projectileDistance = 100.0f;
        }
        else
        {
            projectileDistance = 400.0f;
        }

        m_ship->m_superGun->SpawnAtPosition(
            (orxMATH_KF_PI_BY_2) + (i * orxMATH_KF_PI_BY_4),
            { GetPosition().fX + (orxMath_Cos(i * orxMATH_KF_PI_BY_4) * projectileDistance),
            GetPosition().fY + (orxMath_Sin(i * orxMATH_KF_PI_BY_4) * projectileDistance) });
    }
}
