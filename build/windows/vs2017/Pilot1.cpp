#include "Pilot1.h"

using namespace hexpatriates;

void Pilot1::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot1::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot1::OnCollide(
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

void Pilot1::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot1::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_ship->m_neutralGun->SpawnAtSelf(m_enemyDirection);
    }
}

void Pilot1::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_ship->m_upwardGun->SpawnAtSelf(-orxMATH_KF_PI_BY_2 + (copysignf(1, cosf(m_enemyDirection)) * orxMATH_KF_PI_BY_4));
    }
}

void Pilot1::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_ship->m_downwardGun->SpawnAtSelf(orxMath_GetRandomFloat(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_4 / 2.0, orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_4 / 2.0));
    }
}

void Pilot1::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        if (m_wavesIndexSuper % 2 == 0)
        {
            m_ship->m_superGun->SpawnAtSelf((m_enemyDirection + orxMATH_KF_PI_BY_4) * i);
        }
        else
        {
            m_ship->m_superGun->SpawnAtSelf((m_enemyDirection + orxMATH_KF_PI_BY_4) * i + (m_enemyDirection + orxMATH_KF_PI_BY_4) / 2);
        }
    }
}
