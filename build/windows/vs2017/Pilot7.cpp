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

void Pilot7::FireNeutral(int &_indexInWave)
{
    m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
}

void Pilot7::FireUpward(int &_indexInWave)
{
    m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 - (_indexInWave * orxMATH_KF_PI_BY_16)));
}

void Pilot7::FireDownward(int &_indexInWave)
{
    m_ship->m_downwardGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_4));
}

void Pilot7::FireSuper(int &_indexInWave)
{
    float shotDirection = GetPISD(orxMath_GetRandomFloat(-orxMATH_KF_PI_BY_4, orxMATH_KF_PI_BY_4));
    m_ship->m_superGun->SpawnAtSelf(shotDirection);
}
