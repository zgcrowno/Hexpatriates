#include "LaserPortalEntrance.h"

using namespace hexpatriates;

void LaserPortalEntrance::OnCreate()
{
    PlayerSpecific::OnCreate();

    m_exitDirection = GetFloat("ExitDirection", GetModelName());

    std::vector<orxVECTOR> raycastData = ScrollMod::Raycast(
        GetPosition(),
        m_exitDirection,
        orxPhysics_GetCollisionFlagValue("geometry"));

    if (m_bIsP1)
    {
        m_exit = CreateObject("O-LaserPortalExitP1", {}, {}, { {"Position", &raycastData.at(0)} });
    }
    else
    {
        m_exit = CreateObject("O-LaserPortalExitP2", {}, {}, { {"Position", &raycastData.at(0)} });
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
