#include "Pilot3.h"
#include "ArenaBounds.h"

using namespace hexpatriates;

void Pilot3::OnCreate()
{
    Pilot::OnCreate();
}

void Pilot3::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot3::OnCollide(
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

void Pilot3::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot3::FireNeutral(int &_indexInWave)
{
    float shotDirection = GetPISD(-orxMATH_KF_PI);
    m_ship->m_neutralGun->SpawnAtSelf(shotDirection);
}

void Pilot3::FireUpward(int &_indexInWave)
{
    m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_4));
}

void Pilot3::FireDownward(int &_indexInWave)
{
    if (m_ship->m_downwardGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_2)) > 0)
    {
        ScrollCast<ArenaBounds*>(Hexpatriates::GetInstance().GetArenaBounds())->Electrify(m_bIsP1);
    }
}

void Pilot3::FireSuper(int &_indexInWave)
{
    m_ship->m_superGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 + (_indexInWave * (orxMATH_KF_PI_BY_16))));
}
