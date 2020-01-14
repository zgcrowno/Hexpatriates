#include "Familiar.h"

using namespace hexpatriates;

void Familiar::OnCreate()
{
    Parryable::OnCreate();

    m_framesBehind = GetFloat("FramesBehind", GetModelName());
    SetSpeed(orxVECTOR_0);

    m_gun = ScrollCast<Spawner*>(GetChildByName("O-FamiliarGun" + m_typeName));
}

void Familiar::OnDelete()
{
    Parryable::OnDelete();
}

orxBOOL Familiar::OnCollide(
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
    if (m_bIsFired && arenaBound != orxNULL)
    {
        if (m_bIsAttached)
        {
            m_attachedMovementDirection += orxMATH_KF_PI;
            SetSpeed({ orxMath_Cos(m_attachedMovementDirection) * m_speed, orxMath_Sin(m_attachedMovementDirection) * m_speed });
        }
        else
        {
            if (m_type == Turret)
            {
                AttachToBound(arenaBound, _rvPosition, _rvNormal);
            }
            else // m_type == ERemoteDetonation
            {
                Detonate();
            }
        }
    }

    return orxTRUE;
}

void Familiar::Update(const orxCLOCK_INFO &_rstInfo)
{
    Parryable::Update(_rstInfo);
}

void Familiar::AttachToBound(const ArenaBound *_arenaBound, const orxVECTOR &_attachPosition, const orxVECTOR &_attachNormal)
{
    Projectile::AttachToBound(_arenaBound, _attachPosition, _attachNormal);

    m_bIsAttached = true;
    float normalDirection = orxMath_ATan(_attachNormal.fY, _attachNormal.fX);
    m_attachedMovementDirection = normalDirection - orxMATH_KF_PI_BY_2;
    SetRotation(normalDirection + orxMATH_KF_PI_BY_2);
    SetSpeed({ orxMath_Cos(m_attachedMovementDirection) * m_speed, orxMath_Sin(m_attachedMovementDirection) * m_speed });
    orxSpawner_SetWaveSize(m_gun->m_spawner, 1);
    orxSpawner_SetWaveDelay(m_gun->m_spawner, 0.5f);
    orxVECTOR laserSpeed = { orxMath_Cos(normalDirection), orxMath_Sin(normalDirection) };
    orxSpawner_SetObjectSpeed(m_gun->m_spawner, &laserSpeed);
    SetLifeTime(5.0f);
}

void Familiar::ParriedBehavior()
{
    if (!m_bIsAttached)
    {
        Parryable::ParriedBehavior();
    }
}

void Familiar::Move()
{
    orxVECTOR nextPosition = m_upcomingPositions.front();
    SetPosition({ nextPosition.fX, nextPosition.fY, GetPosition().fZ });
    m_upcomingPositions.pop();
}

void Familiar::FireSelf(const float _direction, const Type _type)
{
    orxVECTOR initialSpeed = { orxMath_Cos(_direction), orxMath_Sin(_direction) };
    SetRotation(_direction);
    SetSpeed({ initialSpeed.fX * m_speed, initialSpeed.fY * m_speed });
    m_bIsFired = true;
    m_type = _type;
}

void Familiar::Detonate()
{
    CreateObject("O-Explosion" + m_typeName, {}, {}, { { "Position", &GetPosition() } });

    Destroy();
}
