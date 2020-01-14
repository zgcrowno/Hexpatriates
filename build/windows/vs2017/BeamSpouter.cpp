#include "BeamSpouter.h"

using namespace hexpatriates;

void BeamSpouter::OnCreate()
{
    Projectile::OnCreate();

    m_spawnTime = GetFloat("SpawnTime", GetModelName());
    m_gun = ScrollCast<Spawner*>(GetChildByName("O-BeamSpouterGun" + m_typeName));
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

    float age = GetActiveTime();
    if (!m_bHasSpawnedBeam && age >= m_spawnTime)
    {
        m_bHasSpawnedBeam = true;
        // TODO: I ought to create an entirely new, untethered projectile that the BeamSpouter uses (instead of just a standard, tethered beam), so as to avoid setting and resetting "Tethered" here.
        SetBool("Tethered", false, "O-Beam");
        // TODO: This SpawnAtSelf call will have to be changed once I've finalized sprites and their normal positions.
        m_gun->SpawnAtSelf(0);
        SetBool("Tethered", true, "O-Beam");
    }
}
