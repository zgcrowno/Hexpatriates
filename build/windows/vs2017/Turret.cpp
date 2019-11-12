#include "Turret.h"

using namespace hexpatriates;

void Turret::OnCreate()
{
    Projectile::OnCreate();
}

void Turret::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Turret::OnCollide(
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

    // Wall collisions
    if (orxString_SearchString(_zColliderPartName, "Wall") != orxNULL)
    {
        if (m_bIsAttached)
        {
            m_movementDirection = { -m_movementDirection.fX, -m_movementDirection.fY };
        }
        else
        {
            float rotRef;
            m_bIsAttached = true;
            // TODO: Set rotation/position
        }
    }

    return orxTRUE;
}

void Turret::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
