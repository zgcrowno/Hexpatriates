#include "Spawner.h"

using namespace hexpatriates;

void Spawner::OnCreate()
{
    m_spawner = (orxSPAWNER*)GetStructure(orxSTRUCTURE_ID_SPAWNER);
}

void Spawner::OnDelete()
{

}

orxBOOL Spawner::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void Spawner::Update(const orxCLOCK_INFO &_rstInfo)
{

}

void Spawner::Spawn(const float _rotation)
{
    orxVECTOR initialSpeed = { orxMath_Cos(_rotation), orxMath_Sin(_rotation) };

    orxSpawner_SetObjectSpeed(m_spawner, &initialSpeed);
    orxSpawner_SetRotation(m_spawner, _rotation);
    orxSpawner_Spawn(m_spawner, 1);
}
