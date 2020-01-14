#include "BeamPlacer.h"

using namespace hexpatriates;

void BeamPlacer::OnCreate()
{
    Projectile::OnCreate();

    m_gun = ScrollCast<Spawner*>(GetChildByName("O-BeamPlacerGun" + m_typeName));

    m_gun->SpawnAtRaycast(GetRotation() - orxMATH_KF_PI_BY_2);
}

void BeamPlacer::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL BeamPlacer::OnCollide(
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

void BeamPlacer::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
