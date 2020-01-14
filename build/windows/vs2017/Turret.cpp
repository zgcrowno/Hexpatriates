#include "Turret.h"

using namespace hexpatriates;

void Turret::OnCreate()
{
    Parryable::OnCreate();

    std::string turretGunName = "O-TurretGun" + m_typeName;
    m_turretGun = ScrollCast<Spawner*>(GetChildByName(turretGunName));
    orxSpawner_Enable(m_turretGun->m_spawner, false);
}

void Turret::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Turret::OnCollide(
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

    // Wall collisions
    ArenaBound *arenaBound = dynamic_cast<ArenaBound*>(_poCollider);
    if (arenaBound != orxNULL)
    {
        if (m_bIsAttached)
        {
            m_movementDirection += orxMATH_KF_PI;
            SetSpeed({ orxMath_Cos(m_movementDirection) * m_speed, orxMath_Sin(m_movementDirection) * m_speed });
        }
        else
        {
            AttachToBound(arenaBound, _rvPosition, _rvNormal);
        }
    }

    return orxTRUE;
}

void Turret::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);
}

void Turret::AttachToBound(const ArenaBound *_arenaBound, const orxVECTOR &_attachPosition, const orxVECTOR &_attachNormal)
{
    Projectile::AttachToBound(_arenaBound, _attachPosition, _attachNormal);

    m_bIsAttached = true;
    float normalDirection = orxMath_ATan(_attachNormal.fY, _attachNormal.fX);
    m_movementDirection = normalDirection - orxMATH_KF_PI_BY_2;
    SetRotation(normalDirection + orxMATH_KF_PI_BY_2);
    SetSpeed({ orxMath_Cos(m_movementDirection) * m_speed, orxMath_Sin(m_movementDirection) * m_speed });
    orxSpawner_Enable(m_turretGun->m_spawner, true);
    orxVECTOR turretLaserSpeed = { orxMath_Cos(normalDirection), orxMath_Sin(normalDirection) };
    orxSpawner_SetObjectSpeed(m_turretGun->m_spawner, &turretLaserSpeed);
}

void Turret::ParriedBehavior()
{
    if (!m_bIsAttached)
    {
        Parryable::ParriedBehavior();
    }
}
