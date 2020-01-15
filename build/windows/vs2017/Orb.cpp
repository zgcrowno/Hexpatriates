#include "Orb.h"
#include "ArenaBound.h"

using namespace hexpatriates;

void Orb::OnCreate()
{
    Parryable::OnCreate();
}

void Orb::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Orb::OnCollide(
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

    // Destroy the Orb if it hits the left or right wall of the arena.
    const orxCHAR *colliderModelName = _poCollider->GetModelName();
    if (orxString_Compare(colliderModelName, "O-WallLeftWall") == 0
        || orxString_Compare(colliderModelName, "O-WallRightWall") == 0)
    {
        Destroy();
    }

    return orxTRUE;
}

void Orb::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);
}
