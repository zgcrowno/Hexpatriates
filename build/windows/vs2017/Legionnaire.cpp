#include "Legionnaire.h"
#include "ArenaBound.h"

using namespace hexpatriates;

void Legionnaire::OnCreate()
{
    Parryable::OnCreate();

    m_bDecelerate = GetBool("Decelerate", GetModelName());
    m_minFSpeed = GetFloat("MinFSpeed", GetModelName());
    m_fSpeedDecrement = GetFloat("FSpeedDecrement", GetModelName());
}

void Legionnaire::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Legionnaire::OnCollide(
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

void Legionnaire::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);

    if (m_bDecelerate)
    {
        if (m_speed > m_minFSpeed)
        {
            m_speed -= m_fSpeedDecrement;
            orxCLAMP(m_speed, m_minFSpeed, m_speed);
            orxVECTOR normalizedSpeed = NormalizeVector(GetSpeed());
            SetSpeed(*orxVector_Mulf(&normalizedSpeed, &normalizedSpeed, m_speed));
        }
        else
        {
            m_bDecelerate = false;
        }
    }
}

void Legionnaire::ParriedBehavior()
{
    ScrollMod *replacementScrollMod = ScrollCast<ScrollMod*>(CreateObject(m_genericName + m_otherTypeName, { { "Decelerate", false } }));
    orxVECTOR normalizedSpeed = NormalizeVector(GetSpeed());
    replacementScrollMod->SetPosition(GetPosition());
    replacementScrollMod->SetRotation(-GetRotation());
    replacementScrollMod->SetSpeed({
        -normalizedSpeed.fX * (m_speed * m_parrySpeedModifier),
        -normalizedSpeed.fY * (m_speed * m_parrySpeedModifier) });
    Destroy();
}
