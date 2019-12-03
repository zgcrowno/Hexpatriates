#include "Spacer.h"

using namespace hexpatriates;

void Spacer::OnCreate()
{
    Projectile::OnCreate();
}

void Spacer::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Spacer::OnCollide(
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

void Spacer::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
