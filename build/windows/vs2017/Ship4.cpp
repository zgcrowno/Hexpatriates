#include "Ship4.h"

using namespace hexpatriates;

void Ship4::OnCreate()
{
    Ship::OnCreate();
}

void Ship4::OnDelete()
{
    Ship::OnDelete();
}

orxBOOL Ship4::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Ship::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void Ship4::Update(const orxCLOCK_INFO &_rstInfo)
{
    Ship::Update(_rstInfo);
}

void Ship4::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_neutralGun->SpawnAtSelf((m_enemyDirection - orxMATH_KF_PI_BY_8) + (i * orxMATH_KF_PI_BY_8));
    }
}

void Ship4::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        const orxCHAR *spawnObjectModelName = m_upwardGun->GetString("Object", m_upwardGun->GetString("Spawner", m_upwardGun->GetModelName()));
        ScrollMod *projectile = CreateObject(spawnObjectModelName);
        if (m_upwardOrigin.fY == orxVECTOR_0.fY)
        {
            m_upwardOrigin = Raycast(GetPosition(), -orxMATH_KF_PI_BY_2, orxPhysics_GetCollisionFlagValue("geometry")).at(0);
        }
        else
        {
            float projectileDistance = projectile->GetSize().fX * projectile->GetScale().fX;
            m_upwardOrigin.fX += projectileDistance;
        }
        projectile->SetPosition(m_upwardOrigin);
        if (m_wavesIndexUpward == m_numWavesUpward - 1)
        {
            m_upwardOrigin = orxVECTOR_0;
        }
    }
}

void Ship4::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        float shotDirection = (m_enemyDirection + orxMATH_KF_PI_BY_2 - orxMATH_KF_PI_BY_8) - (i * orxMATH_KF_PI_BY_8);
        m_downwardGun->SpawnAtRaycast(shotDirection);
    }
}

void Ship4::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        const orxCHAR *spawnObjectModelName = m_upwardGun->GetString("Object", m_upwardGun->GetString("Spawner", m_upwardGun->GetModelName()));
        float projectileDistance;
        if (i < m_waveSizeSuper / 2)
        {
            projectileDistance = 100.0f;
        }
        else
        {
            projectileDistance = 400.0f;
        }

        m_superGun->SpawnAtPosition(
            (m_enemyDirection + orxMATH_KF_PI_BY_2) + (i * orxMATH_KF_PI_BY_4),
            { GetPosition().fX + (orxMath_Cos(m_enemyDirection + (i * orxMATH_KF_PI_BY_4)) * projectileDistance),
            GetPosition().fY + (orxMath_Sin(m_enemyDirection + (i * orxMATH_KF_PI_BY_4)) * projectileDistance) });
    }
}
