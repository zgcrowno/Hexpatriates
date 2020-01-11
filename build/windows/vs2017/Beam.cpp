#include "Beam.h"

using namespace hexpatriates;

void Beam::OnCreate()
{
    Projectile::OnCreate();

    m_expansionTime = GetFloat("ExpansionTime", GetModelName());
    m_damageDealingTime = GetFloat("DamageDealingTime", GetModelName());
    m_contractionTime = GetFloat("ContractionTime", GetModelName());
}

void Beam::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Beam::OnCollide(
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

void Beam::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    float age = GetActiveTime();
    if (age >= m_expansionTime + m_damageDealingTime)
    {
        RemoveBodyPartByName("BP-Beam" + m_typeName);
        AddUniqueFX("FX-ContractBeam");
    }
    else if (age >= m_expansionTime && !m_bBodyAdded)
    {
        m_bBodyAdded = true;
        AddBodyPartByName("BP-Beam" + m_typeName);
        // TODO: I'm calling SetPosition(GetPosition()) here becausefor some reason, in the event that a beam is untethered, and a pilot is touching it when its body part is added, the collision doesn't register until a movement/position event occurs.
        SetPosition(GetPosition());
    }
}
