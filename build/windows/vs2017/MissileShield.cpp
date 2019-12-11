#include "MissileShield.h"
#include "ArenaBounds.h"
#include "Pilot.h"

using namespace hexpatriates;

void MissileShield::OnCreate()
{
    Projectile::OnCreate();

    m_maxMissileSpawnInterval = GetFloat("MaxMissileSpawnInterval", GetModelName());

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

    // Non-Pilot collisions
    if (dynamic_cast<Pilot*>(_poCollider) == NULL)
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
        orxVECTOR firingDirection = orxVECTOR_0;
        orxVECTOR spawnPosition = orxVECTOR_0;
        orxVECTOR partitionPosition = GetVector("Position", "O-Partition");
        ArenaBounds *arenaBounds = static_cast<ArenaBounds*>(Hexpatriates::GetInstance().GetArenaBounds());
        char *missileModelName;

        if (m_bIsP1)
        {
            firingDirection = { 1, 0 };
            spawnPosition = {
                orxMath_GetRandomFloat(arenaBounds->m_leftBound->GetPosition().fX, partitionPosition.fX),
                orxMath_GetRandomFloat(arenaBounds->m_topBound->GetPosition().fY, arenaBounds->m_bottomBound->GetPosition().fY) };
            missileModelName = "O-MissileP1";
        }
        else
        {
            firingDirection = { -1, 0 };
            spawnPosition = {
                orxMath_GetRandomFloat(partitionPosition.fX, arenaBounds->m_rightBound->GetPosition().fX),
                orxMath_GetRandomFloat(arenaBounds->m_topBound->GetPosition().fY, arenaBounds->m_bottomBound->GetPosition().fY) };
            missileModelName = "O-MissileP2";
        }

        CreateObject(missileModelName, {}, {}, { {"Position", &spawnPosition}, {"FiringDirection", &firingDirection} });
        m_missileSpawnTime = m_maxMissileSpawnInterval;
    }
    else
    {
        m_missileSpawnTime -= _rstInfo.fDT;
    }
}
