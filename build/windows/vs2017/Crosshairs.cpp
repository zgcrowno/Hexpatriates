#include "Crosshairs.h"
#include "ArenaBounds.h"

using namespace hexpatriates;

void Crosshairs::OnCreate()
{
    PlayerSpecific::OnCreate();

    m_speed = GetFloat("FSpeed", GetModelName());
    m_decelerationDistance = GetFloat("DecelerationDistance", GetModelName());
    m_maxMissileSpawnInterval = GetFloat("MaxMissileSpawnInterval", GetModelName());
    m_target = ScrollCast<ScrollMod*>(Hexpatriates::GetInstance().GetPilotByPlayerType(m_otherTypeName));
    m_gun = ScrollCast<Spawner*>(GetChildByName("O-CrosshairsGun" + m_typeName));
    SetPosition(m_target->GetPosition());
    // We're setting the owner here so that, should the opposing pilot die while the crosshairs are extant, the latter won't cause a null pointer exception by attempting to move to a non-existant pilot (since it will die when the pilot diese).
    SetOwner(m_target);
}

void Crosshairs::OnDelete()
{

}

orxBOOL Crosshairs::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return orxTRUE;
}

void Crosshairs::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Handle positioning
    MoveTo(m_target->GetPosition(), m_speed, m_decelerationDistance);

    // Handle missile spawning
    if (m_missileSpawnTime <= 0)
    {
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
            spawnPosition = {
                orxMath_GetRandomFloat(partitionPosition.fX, arenaBounds->m_rightBound->GetPosition().fX),
                orxMath_GetRandomFloat(arenaBounds->m_topBound->GetPosition().fY, arenaBounds->m_bottomBound->GetPosition().fY) };
        }

        m_gun->SpawnAtPosition(AngleBetweenPoints(spawnPosition, GetPosition()), spawnPosition);
        m_missileSpawnTime = m_maxMissileSpawnInterval;
    }
    else
    {
        m_missileSpawnTime -= _rstInfo.fDT;
    }
}
