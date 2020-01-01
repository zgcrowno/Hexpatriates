#include "Laser.h"
#include "LaserPortalEntrance.h"
#include "Prism.h"

using namespace hexpatriates;

void Laser::OnCreate()
{
    Parryable::OnCreate();
}

void Laser::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Laser::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Parryable::OnCollide(
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
        orxVECTOR newPos = ScrollMod::Raycast(
            laserPortalEntrance->GetPosition(),
            laserPortalEntrance->GetRotation() - orxMATH_KF_PI_BY_2,
            orxPhysics_GetCollisionFlagValue("geometry")).at(0);
        SetPosition(newPos, true);
    }
    // Only destroy the laser if it's not touching a portal, it's not a LaserGateLaser, it's not colliding with a partition, and it's colliding with something that's either not a projectile or is a prism.
    else if (!m_bIsTouchingPortal && orxString_SearchString(GetModelName().c_str(), "O-LaserGateLaser") == NULL && orxString_SearchString(_poCollider->GetModelName(), "O-Partition") == NULL && (dynamic_cast<Projectile*>(_poCollider) == NULL || dynamic_cast<Prism*>(_poCollider) != NULL))
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
    Parryable::Update(_rstInfo);
}

void Laser::ParriedBehavior()
{
    // Do nothing, as destruction is handled via collisions
}
