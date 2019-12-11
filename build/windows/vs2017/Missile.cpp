#include "Missile.h"

using namespace hexpatriates;

void Missile::OnCreate()
{
    Parryable::OnCreate();

    m_firingDirection = GetVector("FiringDirection", GetModelName());

    SetSpeed({ m_firingDirection.fX * m_speed, m_firingDirection.fY * m_speed });
}

void Missile::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Missile::OnCollide(
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

    return orxTRUE;
}

void Missile::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);
}
