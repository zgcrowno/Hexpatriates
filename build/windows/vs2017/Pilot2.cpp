#include "Pilot2.h"

using namespace hexpatriates;

void Pilot2::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot2::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot2::OnCollide(
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

void Pilot2::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot2::FireNeutral(int &_indexInWave)
{
    m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
}

void Pilot2::FireUpward(int &_indexInWave)
{
    m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_4));
}

void Pilot2::FireDownward(int &_indexInWave)
{
    float shotDirection = orxMath_GetRandomFloat(GetPISD(orxMATH_KF_PI_BY_8), GetPISD(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_8));
    m_ship->m_downwardGun->SpawnAtSelf(shotDirection);
}

void Pilot2::FireSuper(int &_indexInWave)
{
    if (m_wavesIndexSuper % 2 == 0)
    {
        m_ship->m_superGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 + (_indexInWave * orxMATH_KF_PI_BY_16)));
    }
    else
    {
        // This conditional results in the attack appearing more symmetrical, but having fewer projectiles.
        // In effect, each subsequent wave is a different size than the one before it (5, 4, 5, for instance).
        if (_indexInWave < m_waveSizeSuper - 1)
        {
            m_ship->m_superGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 + orxMATH_KF_PI_BY_32 + (_indexInWave * orxMATH_KF_PI_BY_16)));
        }
    }
}
