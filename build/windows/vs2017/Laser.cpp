#include "Laser.h"

using namespace hexpatriates;

void Laser::OnCreate()
{
    m_speed = orxConfig_GetFloat("SpeedLaser");

    Projectile::OnCreate();
}

void Laser::OnDelete()
{

}

orxBOOL Laser::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Destroy();

    return orxTRUE;
}

void Laser::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
