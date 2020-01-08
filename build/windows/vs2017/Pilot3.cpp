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

void Pilot3::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        float shotDirection = GetPISD(-orxMATH_KF_PI);
        m_ship->m_neutralGun->SpawnAtSelf(shotDirection);
    }
}

void Pilot3::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        //m_ship->m_upwardGun->SpawnAtSelf(orxMath_GetRandomFloat(GetPISD(-orxMATH_KF_PI_BY_8), GetPISD(-orxMATH_KF_PI_BY_4 - orxMATH_KF_PI_BY_8)));
        m_ship->m_upwardGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_4));
    }
}

void Pilot3::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_ship->m_downwardGun->SpawnAtSelf(GetPISD(orxMATH_KF_PI_BY_2));
        static_cast<ArenaBounds*>(Hexpatriates::GetInstance().GetArenaBounds())->Electrify(m_bIsP1);
    }
}

void Pilot3::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        m_ship->m_superGun->SpawnAtSelf(GetPISD(-orxMATH_KF_PI_BY_8 + (i * (orxMATH_KF_PI_BY_16))));
    }
}
