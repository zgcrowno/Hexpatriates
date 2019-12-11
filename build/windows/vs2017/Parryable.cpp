#include "Parryable.h"
#include "Pilot.h"

using namespace hexpatriates;

void Parryable::OnCreate()
{
    Projectile::OnCreate();
}

void Parryable::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Parryable::OnCollide(
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

    // Pilot collisions
    Pilot *pilot = dynamic_cast<Pilot*>(_poCollider);
    if (pilot != NULL && pilot->m_parryTime > 0)
    {
        ParriedBehavior();
    }

    return true;
}

void Parryable::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}

void Parryable::ParriedBehavior()
{
    ScrollMod *replacementScrollMod = static_cast<ScrollMod*>(CreateObject(strcat(m_genericName, m_otherTypeName)));
    orxVECTOR normalizedSpeed = NormalizeVector(GetSpeed());
    replacementScrollMod->SetPosition(GetPosition());
    replacementScrollMod->SetRotation(-GetRotation());
    replacementScrollMod->SetSpeed({ -normalizedSpeed.fX * m_speed, -normalizedSpeed.fY * m_speed });
    Destroy();
}
