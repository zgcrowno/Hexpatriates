#include "Ship7.h"

using namespace hexpatriates;

void Ship7::OnCreate()
{
    Ship::OnCreate();
}

void Ship7::OnDelete()
{
    Ship::OnDelete();
}

orxBOOL Ship7::OnCollide(
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

void Ship7::Update(const orxCLOCK_INFO &_rstInfo)
{
    Ship::Update(_rstInfo);
}

void Ship7::FireNeutral()
{
    /*for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_neutralGun->Spawn(m_enemyDirection);
    }*/
}

void Ship7::FireUpward()
{
    /*for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_upwardGun->Spawn(-orxMATH_KF_PI_BY_2 + (copysignf(1, cosf(m_enemyDirection)) * orxMATH_KF_PI_BY_4));
    }*/
}

void Ship7::FireDownward()
{
    /*for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_downwardGun->Spawn(orxMath_GetRandomFloat(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_4 / 2.0, orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_4 / 2.0));
    }*/
}

void Ship7::FireSuper()
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
