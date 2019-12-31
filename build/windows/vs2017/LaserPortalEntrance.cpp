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

    m_exit = CreateObject("O-LaserPortalExit" + m_typeName, {}, {}, { { "Position", &raycastData.at(0) } });

    ScrollObject *arena = Hexpatriates::GetInstance().GetArena();
    SetOwner(arena);
    m_exit->SetOwner(arena);
}

void LaserPortalEntrance::OnDelete()
{
    
}

// TODO: Probably destroy the LaserPortalEntrance on collision, so they don't hang around for too long.
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
