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

void Spawner::Spawn(const float _rotation, const bool &_bSpawnAtPosition)
{
    orxVECTOR initialSpeed = { orxMath_Cos(_rotation), orxMath_Sin(_rotation) };

    orxSpawner_SetObjectSpeed(m_spawner, &initialSpeed);

    if (_bSpawnAtPosition)
    {
        orxSpawner_SetRotation(m_spawner, _rotation);
        orxSpawner_Spawn(m_spawner, 1);
    }
    // The Spawner is spawning the object outside of itself, so we'll spawn it using raycasts, and make sure that the object is untethered.
    else
    {
        const orxCHAR *spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
        bool initialTetheredValue = GetBool("Tethered", spawnObjectModelName);

        std::vector<orxVECTOR> raycastData = Raycast(
            GetPosition(),
            _rotation,
            orxPhysics_GetCollisionFlagValue("geometry"));

        // TODO: Keep an eye on this, as I'll likely not want to add 90 degrees to every object spawned this way.
        CreateObject(spawnObjectModelName, { { "Tethered", false } }, { { "Rotation", orxMATH_KF_RAD_TO_DEG * ScrollMod::VectorToRadians(raycastData.at(1)) + 90.0f } }, { { "Position", &raycastData.at(0) } });
    }
}
