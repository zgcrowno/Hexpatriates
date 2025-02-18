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

void Pilot1::FireNeutral(int &_indexInWave)
{
    m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
}

void Pilot1::FireUpward(int &_indexInWave)
{
    int numWavesUpwardBy2 = m_numWavesUpward / 2;
    int shotDirectionMod =
        m_wavesIndexUpward <= numWavesUpwardBy2
        ? m_wavesIndexUpward
        : numWavesUpwardBy2 - (m_wavesIndexUpward - numWavesUpwardBy2);
    m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 - (shotDirectionMod * orxMATH_KF_PI_BY_64)));
}

void Pilot1::FireDownward(int &_indexInWave)
{
    m_ship->m_downwardGun->SpawnAtSelf(orxMath_GetRandomFloat(
        GetPISD(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_8),
        GetPISD(orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_8)));
}

void Pilot1::FireSuper(int &_indexInWave)
{
    if (m_wavesIndexSuper % 2 == 0)
    {
        m_ship->m_superGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_4) * _indexInWave);
    }
    else
    {
        m_ship->m_superGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_4) * _indexInWave + GetPISD(orxMATH_KF_PI_BY_8));
    }
}
