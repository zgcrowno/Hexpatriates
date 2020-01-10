#include "Shuttlecock.h"
#include "ArenaBound.h"
#include <iostream>

using namespace hexpatriates;

void Shuttlecock::OnCreate()
{
    Parryable::OnCreate();
}

void Shuttlecock::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Shuttlecock::OnCollide(
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
    
    // Destroy the Shuttlecock if it hits the left or right wall of the arena.
    const orxCHAR *colliderModelName = _poCollider->GetModelName();
    if (orxString_Compare(colliderModelName, "O-WallLeftWall") == 0
        || orxString_Compare(colliderModelName, "O-WallRightWall") == 0)
    {
        Destroy();
    }

    return orxTRUE;
}

void Shuttlecock::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);
}
