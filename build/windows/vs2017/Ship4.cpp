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
        m_neutralGun->Spawn((m_enemyDirection - orxMATH_KF_PI_BY_8) + (i * orxMATH_KF_PI_BY_8));
    }
}

void Ship4::FireUpward()
{
    /*for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_upwardGun->Spawn(-orxMATH_KF_PI_BY_2 + (copysignf(1, cosf(m_enemyDirection)) * orxMATH_KF_PI_BY_4));
    }*/
}

void Ship4::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        float shotDirection = (m_enemyDirection + orxMATH_KF_PI_BY_2 - orxMATH_KF_PI_BY_8) - (i * orxMATH_KF_PI_BY_8);
        m_downwardGun->Spawn(shotDirection, false);
    }
}

void Ship4::FireSuper()
{
    /*for (int i = 0; i < m_waveSizeSuper; i++)
    {
        if (m_wavesIndexSuper % 2 == 0)
        {
            m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i);
        }
        else
        {
            m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i + (m_enemyDirection + orxMATH_KF_PI_BY_4) / 2);
        }
    }*/
}
