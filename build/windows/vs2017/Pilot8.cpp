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

void Pilot8::FireNeutral(int &_indexInWave)
{
    m_ship->m_neutralGun->SpawnAtSelf(GetPISD(0));
}

void Pilot8::FireUpward(int &_indexInWave)
{
    if (m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_2)) > 0)
    {
        ScrollCast<ArenaBounds*>(Hexpatriates::GetInstance().GetArenaBounds())->RainEmbers(m_bIsP1);
    }
}

void Pilot8::FireDownward(int &_indexInWave)
{
    m_ship->m_downwardGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_2));
}

void Pilot8::FireSuper(int &_indexInWave)
{
    m_ship->m_superGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_16 - (_indexInWave * orxMATH_KF_PI_BY_16)));
}
