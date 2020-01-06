#include "LaserTeleportable.h"

using namespace hexpatriates;

void LaserTeleportable::OnCreate()
{
    Laser::OnCreate();

    m_gun = static_cast<Spawner*>(GetChildByName("O-LaserTeleportableGun" + m_typeName));

    m_gun->SpawnAtRaycast(GetRotation() - orxMATH_KF_PI_BY_2);
}

void LaserTeleportable::OnDelete()
{
    Laser::OnDelete();
}

orxBOOL LaserTeleportable::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Laser::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return orxTRUE;
}

orxBOOL LaserTeleportable::OnSeparate(ScrollObject *_poCollider)
{
    Laser::OnSeparate(_poCollider);

    return orxTRUE;
}

void LaserTeleportable::Update(const orxCLOCK_INFO &_rstInfo)
{
    Laser::Update(_rstInfo);
}
