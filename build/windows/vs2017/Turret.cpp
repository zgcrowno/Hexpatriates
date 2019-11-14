#include "Turret.h"

using namespace hexpatriates;

void Turret::OnCreate()
{
    Projectile::OnCreate();

    m_turretGun = static_cast<Spawner*>(GetChildByName({
        "O-TurretGunP1",
        "O-TurretGunP2" }));
    orxSpawner_Enable(m_turretGun->m_spawner, false);
}

void Turret::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Turret::OnCollide(
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

    // Wall collisions
    if (orxString_SearchString(_zColliderPartName, "Wall") != orxNULL)
    {
        if (m_bIsAttached)
        {
            m_movementDirection += orxMATH_KF_PI;
            SetSpeed({ orxMath_Cos(m_movementDirection) * m_speed, orxMath_Sin(m_movementDirection) });
        }
        else
        {
            float normalDirection = orxMath_ATan(_rvNormal.fY, _rvNormal.fX);
            m_movementDirection += orxMATH_KF_2_PI;
            m_bIsAttached = true;
            SetRotation(normalDirection + orxMATH_KF_PI_BY_2);
            SetSpeed({ orxMath_Cos(m_movementDirection) * m_speed, orxMath_Sin(m_movementDirection) * m_speed });
            orxSpawner_Enable(m_turretGun->m_spawner, true);
            // TODO: The speed needs to be determined by O-Laser's Speed attribute, but since I don't have access to _rstInfo.fDT here, I'll need to figure out
            // how to do that without these lasers attaining unreasonably high speeds. Does Orx handle fDT multiplication in the background? Do I even need to
            // worry about fDT when calling SetSpeed?
            orxVECTOR turretLaserSpeed = { orxMath_Cos(normalDirection), orxMath_Sin(normalDirection) };
            orxSpawner_SetObjectSpeed(m_turretGun->m_spawner, &turretLaserSpeed);
        }
    }

    return orxTRUE;
}

void Turret::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}
