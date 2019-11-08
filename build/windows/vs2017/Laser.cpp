#include "Laser.h"

using namespace hexpatriates;

void Laser::OnCreate()
{
    Projectile::OnCreate();
}

void Laser::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Laser::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Projectile::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);
    
    Destroy();

    return orxTRUE;
}

void Laser::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
