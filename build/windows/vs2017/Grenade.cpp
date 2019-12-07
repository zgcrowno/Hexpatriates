#include "Grenade.h"

using namespace hexpatriates;

void Grenade::OnCreate()
{
    Projectile::OnCreate();

    m_numShrapnel = GetFloat("NumShrapnel", GetModelName());
    m_gun = static_cast<Spawner*>(GetChildByName({ "O-GrenadeGunP1", "O-GrenadeGunP2" }));
}

void Grenade::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Grenade::OnCollide(
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

    float normalInRadians = VectorToRadians(_rvNormal);
    for (int i = 0; i < m_numShrapnel; i++)
    {
        float shotDirection = orxMath_GetRandomFloat(normalInRadians - orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_8, normalInRadians + orxMATH_KF_PI_BY_2 - orxMATH_KF_PI_BY_8);
        m_gun->SpawnAtSelf(shotDirection);
    }

    Destroy();

    return orxTRUE;
}

void Grenade::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
