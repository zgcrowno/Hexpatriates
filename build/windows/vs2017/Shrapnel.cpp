#include "Shrapnel.h"

using namespace hexpatriates;

void Shrapnel::OnCreate()
{
    Projectile::OnCreate();
}

void Shrapnel::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Shrapnel::OnCollide(
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

    return orxTRUE;
}

void Shrapnel::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
