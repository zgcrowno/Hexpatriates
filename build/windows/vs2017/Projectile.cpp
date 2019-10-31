#include "Projectile.h"
#include "Pilot.h"

using namespace hexpatriates;

void Projectile::OnCreate()
{
    orxVECTOR speedRef = orxVECTOR_0;
    GetSpeed(speedRef, orxFALSE);
    SetSpeed({ speedRef.fX * m_speed, speedRef.fY * m_speed});
}

void Projectile::OnDelete()
{

}

orxBOOL Projectile::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    
    return orxTRUE;
}

void Projectile::Update(const orxCLOCK_INFO &_rstInfo)
{

}
