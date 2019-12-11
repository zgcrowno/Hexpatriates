#include "Spawner.h"

using namespace hexpatriates;

void Spawner::OnCreate()
{
    m_spawner = (orxSPAWNER*)GetStructure(orxSTRUCTURE_ID_SPAWNER);

    m_defaultSpawnerRotation = GetFloat("Rotation", orxSpawner_GetName(m_spawner)) * orxMATH_KF_DEG_TO_RAD;
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

// TODO: I don't think I'm ever using an instance of this with _tethered set to true, so maybe I should just get rid of that parameter and its associated behavior?
void Spawner::SpawnAtSelf(const float _rotation, const bool _tethered)
{
    // We add the m_defaultSpawnerRotation value here so we can make spawned item rotation independent of parent rotation.
    orxSpawner_SetRotation(m_spawner, _rotation + m_defaultSpawnerRotation);
    
    if (_tethered)
    {
        const orxCHAR *spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
        CreateObject(spawnObjectModelName, { { "Tethered", _tethered } });
    }
    else
    {
        orxVECTOR initialSpeed = { orxMath_Cos(_rotation), orxMath_Sin(_rotation) };

        orxSpawner_SetObjectSpeed(m_spawner, &initialSpeed);
        orxSpawner_Spawn(m_spawner, 1);
    }
}

void Spawner::SpawnAtPosition(const float _rotation, const orxVECTOR _position)
{
    const orxCHAR *spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
    orxVECTOR initialSpeed = { orxMath_Cos(_rotation), orxMath_Sin(_rotation) };

    orxSpawner_SetObjectSpeed(m_spawner, &initialSpeed);
    ScrollMod *projectile = CreateObject(
        spawnObjectModelName,
        { {"Tethered", false} },
        { { "Rotation", _rotation * orxMATH_KF_RAD_TO_DEG } },
        { { "Position", &_position }, { "Speed", &initialSpeed } });
}

void Spawner::SpawnAtRaycast(const float _direction)
{
    const orxCHAR *spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
    std::vector<orxVECTOR> raycastData = Raycast(
        GetPosition(),
        _direction,
        orxPhysics_GetCollisionFlagValue("geometry"));
    // TODO: Keep an eye on this, as I'll likely not want to add 90 degrees to every object spawned this way.
    float initialRotation = ScrollMod::VectorToRadians(raycastData.at(1)) + orxMATH_KF_PI_BY_2;
    orxVECTOR initialSpeed = { orxMath_Cos(initialRotation), orxMath_Sin(initialRotation) };

    ScrollMod *projectile = CreateObject(
        spawnObjectModelName,
        { {"Tethered", false} },
        { { "Rotation", initialRotation * orxMATH_KF_RAD_TO_DEG } },
        { { "Position", &raycastData.at(0) }, { "Speed", &initialSpeed } });
}
