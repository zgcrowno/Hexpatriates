#include "Pilot7.h"

using namespace hexpatriates;

void Pilot7::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot7::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot7::OnCollide(
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

void Pilot7::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot7::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_ship->m_neutralGun->SpawnAtSelf(m_enemyDirection);
    }
}

void Pilot7::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_ship->m_upwardGun->SpawnAtSelf(-orxMATH_KF_PI_BY_8 - copysignf(1, cosf(m_enemyDirection)) * (i * orxMATH_KF_PI_BY_8));
    }
}

void Pilot7::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_ship->m_downwardGun->SpawnAtSelf(orxMATH_KF_PI_BY_4);
    }
}

void Pilot7::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        m_ship->m_superGun->SpawnAtSelf(m_enemyDirection);
    }
}
