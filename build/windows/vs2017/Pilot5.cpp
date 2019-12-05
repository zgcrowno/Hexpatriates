#include "Pilot5.h"

using namespace hexpatriates;

void Pilot5::OnCreate()
{
    Pilot::OnCreate();
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
}

void Pilot5::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        //m_neutralGun->Spawn(m_enemyDirection);
    }
}

void Pilot5::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        if (m_stance == Stance::CloseRange)
        {
            m_stance == Stance::LongRange;
        }
        else
        {
            //m_upwardGun->Spawn(-orxMATH_KF_PI_BY_2 + (copysignf(1, cosf(m_enemyDirection)) * orxMATH_KF_PI_BY_4));
        }
    }
}

void Pilot5::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        if (m_stance == Stance::LongRange)
        {
            m_stance == Stance::CloseRange;
        }
        else
        {
            //m_downwardGun->Spawn(orxMath_GetRandomFloat(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_4 / 2.0, orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_4 / 2.0));
        }
    }
}

void Pilot5::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        if (m_wavesIndexSuper % 2 == 0)
        {
            //m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i);
        }
        else
        {
            //m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i + (m_enemyDirection + orxMATH_KF_PI_BY_4) / 2);
        }
    }
}
