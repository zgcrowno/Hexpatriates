#include "LaserWall.h"
#include "Pilot.h"

using namespace hexpatriates;

void LaserWall::OnCreate()
{
    Projectile::OnCreate();
}

void LaserWall::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL LaserWall::OnCollide(
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

    /*if (dynamic_cast<Pilot*>(_poCollider) != orxNULL)
    {
        Destroy();
    }*/
    Destroy();

    return orxTRUE;
}

void LaserWall::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Increase the size of the wall
    orxVECTOR curScale = GetScale();
    SetScale({ curScale.fX, curScale.fY + _rstInfo.fDT, curScale.fZ });
}
