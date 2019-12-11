#include "LaserHeatseeking.h"
#include <iostream>

using namespace hexpatriates;

void LaserHeatseeking::OnCreate()
{
    Laser::OnCreate();

    m_target = static_cast<Pilot*>(Hexpatriates::GetInstance().GetPilotByPlayerType(m_otherTypeName));

    orxVECTOR pos = GetPosition(true);
    orxVECTOR targetPos = m_target->GetPosition(true);
    m_bInitialXLessThanTarget = pos.fX < targetPos.fX;
    m_bInitialYLessThanTarget = pos.fY < targetPos.fY;
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

    return true;
}

void LaserHeatseeking::Update(const orxCLOCK_INFO &_rstInfo)
{
    Laser::Update(_rstInfo);

    if (!m_bIsOnTarget)
    {
        orxVECTOR pos = GetPosition(true);
        orxVECTOR targetPos = m_target->GetPosition(true);
        bool bRelationToTargetHasChanged =
            m_bInitialXLessThanTarget && pos.fX >= targetPos.fX
            || !m_bInitialXLessThanTarget && pos.fX < targetPos.fX
            || m_bInitialYLessThanTarget && pos.fY >= targetPos.fY
            || !m_bInitialYLessThanTarget && pos.fY < targetPos.fY;
        if (bRelationToTargetHasChanged)
        {
            m_bIsOnTarget = true;
            float angleBetweenSelfAndTarget = AngleBetween(pos, targetPos);
            orxVECTOR normalizedSpeed = RadiansToVector(angleBetweenSelfAndTarget);
            SetRotation(angleBetweenSelfAndTarget - orxMATH_KF_PI_BY_2); // Subtracting orxMATH_KF_PI_BY_2 because of laser's default orientation.
            SetSpeed({ normalizedSpeed.fX * m_speed, normalizedSpeed.fY * m_speed });
        }
    }
}
