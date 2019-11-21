#include "LaserPortalEntrance.h"

using namespace hexpatriates;

void LaserPortalEntrance::OnCreate()
{
    m_exitDirection = GetFloat("ExitDirection", GetModelName());

    orxVECTOR startingPos = GetPosition(true);
    // Using 10000 purely to have a huge number which results in the arena being traversed in full.
    orxVECTOR endingPos = { startingPos.fX + orxMath_Cos(m_exitDirection) * 10000.0f, startingPos.fY + orxMath_Sin(m_exitDirection) * 10000.0f };
    orxVECTOR hitPos;
    orxVECTOR hitNormal;
    orxObject_Raycast(&startingPos, &endingPos, 0xFFFF, orxPhysics_GetCollisionFlagValue("geometry"), true, &hitPos, &hitNormal);
    if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
    {
        m_exit = CreateObject("O-LaserPortalExitP1", {}, {}, { {"Position", &hitPos} });
    }
    else
    {
        m_exit = CreateObject("O-LaserPortalExitP2", {}, {}, { {"Position", &hitPos} });
    }
}

void LaserPortalEntrance::OnDelete()
{
    
}

orxBOOL LaserPortalEntrance::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return orxTRUE;
}

void LaserPortalEntrance::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
