#include "Orb.h"

using namespace hexpatriates;

void Orb::OnCreate()
{
    Projectile::OnCreate();
}

void Orb::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Orb::OnCollide(
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

void Orb::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
