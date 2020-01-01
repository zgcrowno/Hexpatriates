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
    // Have to handle OnDestruction behavior here, becuase OnDelete is called AFTER the Spawner has actually been deleted--not directly prior as previously thought.
    if (!CleanOnDelete() && GetLifeTime() <= 0)
    {
        // If the spawner isn't set to clean on delete, we have to transfer ownership to the Arena so we're not left with living projectiles when we exit to a menu.
        orxOBJECT *arena = Hexpatriates::GetInstance().GetArena()->GetOrxObject();
        for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
        {
            orxObject_SetOwner(child->GetOrxObject(), arena);
        }
    }
}

// TODO: I don't think I'm ever using an instance of this with _tethered set to true, so maybe I should just get rid of that parameter and its associated behavior?
void Spawner::SpawnAtSelf(const float _rotation, const bool _tethered)
{
    // We add the m_defaultSpawnerRotation value here so we can make spawned item rotation independent of parent rotation.
    orxSpawner_SetRotation(m_spawner, _rotation + m_defaultSpawnerRotation);
    
    if (_tethered)
    {
        if (GetOwnedChildrenCount() < GetActiveObjectLimit())
        {
            const std::string spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
            ScrollMod *projectile = CreateObject(spawnObjectModelName, { { "Tethered", _tethered } });
            projectile->SetOwner(this);
        }
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
    int activeObjectLimit = GetActiveObjectLimit();
    if (activeObjectLimit == 0 || GetOwnedChildrenCount() < activeObjectLimit)
    {
        const std::string spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
        orxVECTOR initialSpeed = { orxMath_Cos(_rotation), orxMath_Sin(_rotation) };

        ScrollMod *projectile = CreateObject(
            spawnObjectModelName,
            { {"Tethered", false} },
            { { "Rotation", _rotation * orxMATH_KF_RAD_TO_DEG } },
            { { "Position", &_position }, { "Speed", &initialSpeed } });
        projectile->SetOwner(this);
    }
}

void Spawner::SpawnAtRaycast(const float _direction)
{
    int activeObjectLimit = GetActiveObjectLimit();
    if (activeObjectLimit == 0 || GetOwnedChildrenCount() < activeObjectLimit)
    {
        const std::string spawnObjectModelName = GetString("Object", GetString("Spawner", GetModelName()));
        std::vector<orxVECTOR> raycastData = Raycast(
            GetPosition(true),
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
        projectile->SetOwner(this);
    }
}

// TODO: Probably just make this a ScrollMod method at some point.
int Spawner::GetOwnedChildrenCount()
{
    int result = 0;
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        result++;
    }
    return result;
}

int Spawner::GetActiveObjectCount()
{
    return orxSpawner_GetActiveObjectCount(m_spawner);
}

int Spawner::GetActiveObjectLimit()
{
    return orxSpawner_GetActiveObjectLimit(m_spawner);
}

bool Spawner::CleanOnDelete()
{
    return GetBool("CleanOnDelete", GetString("Spawner", GetModelName()));
}
