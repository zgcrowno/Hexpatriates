#include "Familiar.h"

using namespace hexpatriates;

void Familiar::OnCreate()
{
    Projectile::OnCreate();
}

void Familiar::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Familiar::OnCollide(
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

void Familiar::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
