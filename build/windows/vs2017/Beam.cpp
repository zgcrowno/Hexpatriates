#include "Beam.h"

using namespace hexpatriates;

void Beam::OnCreate()
{
    Projectile::OnCreate();
}

void Beam::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Beam::OnCollide(
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

void Beam::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
