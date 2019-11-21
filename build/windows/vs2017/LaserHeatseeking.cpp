#include "LaserHeatseeking.h"
#include <iostream>

using namespace hexpatriates;

void LaserHeatseeking::OnCreate()
{
    Laser::OnCreate();

    if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
    {
        m_target = static_cast<Pilot*>(Hexpatriates::GetInstance().GetPilotByPlayerType("P2"));
    }
    else
    {
        m_target = static_cast<Pilot*>(Hexpatriates::GetInstance().GetPilotByPlayerType("P1"));
    }
}

void LaserHeatseeking::OnDelete()
{
    Laser::OnDelete();
}

orxBOOL LaserHeatseeking::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Laser::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return orxTRUE;
}

void LaserHeatseeking::Update(const orxCLOCK_INFO &_rstInfo)
{
    Laser::Update(_rstInfo);

    orxVECTOR pos = GetPosition(orxTRUE);
    orxVECTOR targetPos = m_target->GetPosition(orxTRUE);
    if (!m_bIsOnTarget && orxMath_Abs(pos.fY - targetPos.fY) <= 5.0f)
    {
        m_bIsOnTarget = true;
        SetRotation(orxMATH_KF_PI_BY_2);
        SetSpeed({ m_speed, 0.0f });
    }
}
