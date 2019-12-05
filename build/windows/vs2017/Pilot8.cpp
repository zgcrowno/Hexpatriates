#include "Pilot8.h"
#include "ArenaBounds.h"

using namespace hexpatriates;

void Pilot8::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot8::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot8::OnCollide(
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

void Pilot8::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot8::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_ship->m_neutralGun->SpawnAtSelf(m_enemyDirection);
    }
}

void Pilot8::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_ship->m_upwardGun->SpawnAtSelf(-orxMATH_KF_PI_BY_2);
        static_cast<ArenaBounds*>(Hexpatriates::GetInstance().GetArenaBounds())->RainEmbers(orxString_SearchString(GetModelName(), "P1") != NULL);
    }
}

void Pilot8::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_ship->m_downwardGun->SpawnAtSelf(orxMATH_KF_PI_BY_2);
    }
}

void Pilot8::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        m_ship->m_superGun->SpawnAtSelf(m_enemyDirection + orxMATH_KF_PI_BY_16 - (i * copysignf(1, cosf(m_enemyDirection)) * orxMATH_KF_PI_BY_16));
    }
}
