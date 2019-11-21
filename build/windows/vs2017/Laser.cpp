#include "Laser.h"
#include "LaserPortalEntrance.h"

using namespace hexpatriates;

void Laser::OnCreate()
{
    Projectile::OnCreate();
}

void Laser::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Laser::OnCollide(
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

    // LaserPortalEntrance Collisions
    LaserPortalEntrance *laserPortalEntrance = dynamic_cast<LaserPortalEntrance*>(_poCollider);
    if (laserPortalEntrance != orxNULL)
    {
        m_bIsTouchingPortal = true;
        SetPosition(laserPortalEntrance->m_exit->GetPosition(true), true);
    }
    else if (!m_bIsTouchingPortal)
    {
        Destroy();
    }

    return orxTRUE;
}

orxBOOL Laser::OnSeparate(ScrollObject *_poCollider)
{
    if (orxString_SearchString(_poCollider->GetModelName(), "LaserPortalExit") != orxNULL)
    {
        m_bIsTouchingPortal = false;
    }

    return orxTRUE;
}

void Laser::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
