#include "Beam.h"

using namespace hexpatriates;

void Beam::OnCreate()
{
    TetheredProjectile::OnCreate();
}

void Beam::OnDelete()
{
    TetheredProjectile::OnDelete();
}

orxBOOL Beam::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    TetheredProjectile::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return orxTRUE;
}

void Beam::Update(const orxCLOCK_INFO &_rstInfo)
{
    TetheredProjectile::Update(_rstInfo);
}
