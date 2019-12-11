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

    // ArenaBound Collisions
    if (dynamic_cast<ArenaBound*>(_poCollider) != NULL)
    {
        orxVECTOR reflectionVector = ReflectionVector(NormalizeVector(GetSpeed()), _rvNormal);
        SetSpeed({ reflectionVector.fX * m_speed, reflectionVector.fY * m_speed });
    }

    return orxTRUE;
}

void Orb::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);
}
