#include "Familiar.h"

using namespace hexpatriates;

void Familiar::OnCreate()
{
    Parryable::OnCreate();

    m_framesBehind = GetFloat("FramesBehind", GetModelName());
    SetSpeed(orxVECTOR_0);

    orxCHAR gunTypeText[512] = "O-FamiliarGun";
    m_gun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, m_typeName)));
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
    if (m_bIsFired && orxString_SearchString(_zColliderPartName, "Wall") != orxNULL)
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
                float normalDirection = orxMath_ATan(_rvNormal.fY, _rvNormal.fX);
                m_attachedMovementDirection = normalDirection - orxMATH_KF_PI_BY_2;
                m_bIsAttached = true;
                SetRotation(normalDirection + orxMATH_KF_PI_BY_2);
                SetSpeed({ orxMath_Cos(m_attachedMovementDirection) * m_speed, orxMath_Sin(m_attachedMovementDirection) * m_speed });
                orxSpawner_SetWaveSize(m_gun->m_spawner, 1);
                orxSpawner_SetWaveDelay(m_gun->m_spawner, 0.5f);
                orxVECTOR laserSpeed = { orxMath_Cos(normalDirection), orxMath_Sin(normalDirection) };
                orxSpawner_SetObjectSpeed(m_gun->m_spawner, &laserSpeed);
                SetLifeTime(5.0f);
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
    orxCHAR explosionText[512] = "O-Explosion";
    CreateObject(strcat(explosionText, m_typeName), {}, {}, { { "Position", &GetPosition() } });

    Destroy();
}
