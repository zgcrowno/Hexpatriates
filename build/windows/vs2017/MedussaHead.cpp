#include "MedussaHead.h"

using namespace hexpatriates;

void MedussaHead::OnCreate()
{
    Projectile::OnCreate();

    m_gun = static_cast<Spawner*>(GetChildByName("O-MedussaHeadGun" + m_typeName));
}

void MedussaHead::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL MedussaHead::OnCollide(
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

void MedussaHead::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Ensure that MedussaHead is moving in whichever direction it's facing. The rotation which makes this matter is handled via ORX FX.
    float rotation = GetRotation();
    orxVECTOR normalizedSpeed = { orxMath_Cos(rotation), orxMath_Sin(rotation) };
    SetSpeed({ normalizedSpeed.fX * m_speed, normalizedSpeed.fY * m_speed });
}
