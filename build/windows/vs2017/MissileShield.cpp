#include "MissileShield.h"
#include "ArenaBounds.h"
#include "Pilot.h"

using namespace hexpatriates;

void MissileShield::OnCreate()
{
    Projectile::OnCreate();

    m_maxMissileSpawnInterval = GetFloat("MaxMissileSpawnInterval", GetModelName());
    m_gun = ScrollCast<Spawner*>(GetChildByName("O-MissileShieldGun" + m_typeName));

    // Set speed from config-generated, random rotation
    orxVECTOR randomNormalizedVector = RadiansToVector(orxMath_GetRandomFloat(0, orxMATH_KF_2_PI));
    SetSpeed({ randomNormalizedVector.fX * m_speed, randomNormalizedVector.fY * m_speed });
}

void MissileShield::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL MissileShield::OnCollide(
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

    // Bounce off of partition
    if (orxString_Compare(_poCollider->GetModelName(), "O-Partition") == 0)
    {
        orxVECTOR reflectionVector = ReflectionVector(NormalizeVector(GetSpeed()), _rvNormal);
        SetSpeed({ reflectionVector.fX * m_speed, reflectionVector.fY * m_speed });
    }

    return orxTRUE;
}

void MissileShield::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Handle missle spawning
    if (m_missileSpawnTime <= 0)
    {
        float rotation = 0;
        orxVECTOR spawnPosition = orxVECTOR_0;
        orxVECTOR partitionPosition = GetVector("Position", "O-Partition");
        ArenaBounds *arenaBounds = ScrollCast<ArenaBounds*>(Hexpatriates::GetInstance().GetArenaBounds());

        if (m_bIsP1)
        {
            spawnPosition = {
                orxMath_GetRandomFloat(arenaBounds->m_leftBound->GetPosition().fX, partitionPosition.fX),
                orxMath_GetRandomFloat(arenaBounds->m_topBound->GetPosition().fY, arenaBounds->m_bottomBound->GetPosition().fY) };
        }
        else
        {
            rotation = orxMATH_KF_PI;
            spawnPosition = {
                orxMath_GetRandomFloat(partitionPosition.fX, arenaBounds->m_rightBound->GetPosition().fX),
                orxMath_GetRandomFloat(arenaBounds->m_topBound->GetPosition().fY, arenaBounds->m_bottomBound->GetPosition().fY) };
        }

        m_gun->SpawnAtPosition(rotation, spawnPosition);

        m_missileSpawnTime = m_maxMissileSpawnInterval;
    }
    else
    {
        m_missileSpawnTime -= _rstInfo.fDT;
    }
}
