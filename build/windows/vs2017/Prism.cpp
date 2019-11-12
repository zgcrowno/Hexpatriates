#include "Prism.h"

using namespace hexpatriates;

void Prism::OnCreate()
{
    Projectile::OnCreate();
}

void Prism::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Prism::OnCollide(
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

void Prism::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
