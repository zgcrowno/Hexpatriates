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
        m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
    }
}

void Pilot1::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        int numWavesUpwardBy2 = m_numWavesUpward / 2;
        int shotDirectionMod =
            m_wavesIndexUpward <= numWavesUpwardBy2
            ? m_wavesIndexUpward + 1
            : (numWavesUpwardBy2 + 1) - (m_wavesIndexUpward - numWavesUpwardBy2);
        m_ship->m_upwardGun->SpawnAtSelf(GetPISD(shotDirectionMod * -orxMATH_KF_PI_BY_8));
    }
}

void Pilot1::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_ship->m_downwardGun->SpawnAtSelf(orxMath_GetRandomFloat(
            GetPISD(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_8),
            GetPISD(orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_8)));
    }
}

void Pilot1::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        if (m_wavesIndexSuper % 2 == 0)
        {
            m_ship->m_superGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_4) * i);
        }
        else
        {
            m_ship->m_superGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_4) * i + GetPISD(orxMATH_KF_PI_BY_8));
        }
    }
}
