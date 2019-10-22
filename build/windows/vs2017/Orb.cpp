#include "Orb.h"

using namespace hexpatriates;

void Orb::OnCreate()
{
    m_speed = orxConfig_GetFloat("SpeedOrb");

    Projectile::OnCreate();
}

void Orb::OnDelete()
{

}

orxBOOL Orb::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void Orb::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
