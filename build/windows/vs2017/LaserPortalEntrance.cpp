#include "LaserPortalEntrance.h"
#include "Laser.h"

using namespace hexpatriates;

void LaserPortalEntrance::OnCreate()
{
    PlayerSpecific::OnCreate();

    m_gun = ScrollCast<Spawner*>(GetChildByName("O-LaserPortalEntranceGun" + m_typeName));
    
    m_gun->SpawnAtRaycast(GetRotation() - orxMATH_KF_PI_BY_2);
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
    if (dynamic_cast<Laser*>(_poCollider) != nullptr)
    {
        SetLifeTime(0.3f);
    }

    return orxTRUE;
}

void LaserPortalEntrance::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
