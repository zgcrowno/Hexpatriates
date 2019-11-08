#include "LaserWall.h"

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

    Destroy();

    return orxTRUE;
}

void LaserWall::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Increase the size of the wall
    orxVECTOR curScale = orxVECTOR_0;
    GetScale(curScale);
    SetScale({ curScale.fX, curScale.fY + _rstInfo.fDT, curScale.fZ });
}
