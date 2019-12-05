#include "Ember.h"

using namespace hexpatriates;

void Ember::OnCreate()
{
    Projectile::OnCreate();

    m_fallSpeed = GetFloat("FallSpeed", GetModelName());
    m_swaySpeed = GetFloat("SwaySpeed", GetModelName());
    m_maxSwayTime = GetFloat("MaxSwayTime", GetModelName());
    m_movementDirection = { m_possibleSwayDirections[orxMath_GetRandomU32(0, 1)] * m_swaySpeed, m_fallSpeed };
    SetSpeed(m_movementDirection);
}

void Ember::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Ember::OnCollide(
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

void Ember::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    m_swayTime += _rstInfo.fDT;
    if (m_swayTime >= m_maxSwayTime)
    {
        m_swayTime = 0;
        m_movementDirection = { -m_movementDirection.fX, m_movementDirection.fY };
        SetSpeed(m_movementDirection);
    }
}
