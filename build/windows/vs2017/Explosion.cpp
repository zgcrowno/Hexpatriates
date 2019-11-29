#include "Explosion.h"

using namespace hexpatriates;

void Explosion::OnCreate()
{
    Projectile::OnCreate();

    m_growthSpeed = GetFloat("GrowthSpeed", GetModelName());
}

void Explosion::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Explosion::OnCollide(
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

void Explosion::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Increase the size of the explosion
    float growthAmount = m_growthSpeed * _rstInfo.fDT;
    orxVECTOR curScale = GetScale();
    SetScale({ curScale.fX + growthAmount, curScale.fY + growthAmount, curScale.fZ });
}
