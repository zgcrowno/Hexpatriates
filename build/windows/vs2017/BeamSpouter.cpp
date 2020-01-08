#include "BeamSpouter.h"

using namespace hexpatriates;

void BeamSpouter::OnCreate()
{
    Projectile::OnCreate();

    m_spawnTime = GetFloat("SpawnTime", GetModelName());
    m_gun = static_cast<Spawner*>(GetChildByName("O-BeamSpouterGun" + m_typeName));
}

void BeamSpouter::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL BeamSpouter::OnCollide(
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

void BeamSpouter::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    float age = orxObject_GetActiveTime(GetOrxObject());
    if (!m_bHasSpawnedBeam && age >= m_spawnTime)
    {
        m_bHasSpawnedBeam = true;
        m_gun->SpawnAtSelf(GetRotation());
    }
}
