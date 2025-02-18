#include "Pilot6.h"
#include "Laser.h"
#include "Orb.h"

using namespace hexpatriates;

void Pilot6::OnCreate()
{
    Pilot::OnCreate();

    m_maxFamiliars = GetFloat("MaxFamiliars", GetModelName());
}

void Pilot6::OnDelete()
{
    Pilot::OnDelete();
}

orxBOOL Pilot6::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Pilot::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    // Check for collisions with pilot body--not ship body
    if (orxString_Compare(_zPartName, "BP-PilotP1") == 0
        || orxString_Compare(_zPartName, "BP-PilotP2") == 0)
    {
        // Laser collisions
        if (dynamic_cast<Laser*>(_poCollider) != orxNULL)
        {
            if (m_parryTime > 0 && m_ship->IsEnabled())
            {
                SpawnFamiliar();
            }
        }
        // Orb collisions
        if (dynamic_cast<Orb*>(_poCollider) != orxNULL)
        {
            if (m_parryTime > 0 && m_ship->IsEnabled())
            {
                SpawnFamiliar();
            }
        }
    }

    return true;
}

void Pilot6::Update(const orxCLOCK_INFO &_rstInfo)
{
    Pilot::Update(_rstInfo);
}

void Pilot6::ExecuteMovement()
{
    Pilot::ExecuteMovement();

    orxVECTOR speedVector = GetSpeed();
    if (speedVector.fX != orxVECTOR_0.fX || speedVector.fY != orxVECTOR_0.fY)
    {
        for (Familiar *familiar : m_familiars)
        {
            if (familiar->m_upcomingPositions.size() == familiar->m_framesBehind - 1)
            {
                familiar->Move();
            }
            familiar->m_upcomingPositions.push(GetPosition());
        }
    }
}

void Pilot6::DestroyShip()
{
    Pilot::DestroyShip();

    for (Familiar *familiar : m_familiars)
    {
        familiar->Destroy();
    }
    m_familiars.clear();
}

void Pilot6::FireNeutral(int &_indexInWave)
{
    m_ship->m_neutralGun->SpawnAtSelf(m_enemyDirection);
    for (Familiar *familiar : m_familiars)
    {
        familiar->m_gun->SpawnAtSelf(GetPISD(0));
    }
}

void Pilot6::FireUpward(int &_indexInWave)
{
    FireFamiliar(GetPISD(-orxMATH_KF_PI_BY_4), Familiar::Type::Turret);
}

void Pilot6::FireDownward(int &_indexInWave)
{
    FireFamiliar(GetPISD(orxMATH_KF_PI_BY_4), Familiar::Type::Turret);
}

void Pilot6::FireSuper(int &_indexInWave)
{
    Familiar *superInPlay = SuperInPlay();
    if (superInPlay != nullptr)
    {
        superInPlay->Detonate();
    }
    else
    {
        FireFamiliar(GetPISD(0), Familiar::Type::RemoteDetonation);
    }
}

void Pilot6::FireFamiliar(const float _direction, const Familiar::Type _type)
{
    if (m_familiars.size() > 0)
    {
        m_familiars.at(m_familiars.size() - 1)->FireSelf(_direction, _type);
        m_familiars.pop_back();
    }
}

void Pilot6::SpawnFamiliar()
{
    if (m_familiars.size() < m_maxFamiliars)
    {
        orxVECTOR spawnPosition = { GetPosition().fX, GetPosition().fY, GetVector("Position", "O-Familiar").fZ };
        Familiar *familiar = ScrollCast<Familiar*>(CreateObject("O-Familiar" + m_typeName, {}, {}, { { "Position", &spawnPosition } }));
        m_familiars.push_back(familiar);
        familiar->SetOwner(this);
        familiar->m_framesBehind *= m_familiars.size();
    }
}

Familiar *Pilot6::SuperInPlay()
{
    bool bSuperInPlay = false;
    Familiar *extantSuper;
    std::vector<ScrollObject*> extantFamiliars = Hexpatriates::GetInstance().GetFamiliarsByPlayerType(m_typeName);

    for (int i = 0; i < extantFamiliars.size(); i++)
    {
        extantSuper = ScrollCast<Familiar*>(extantFamiliars.at(i));

        if (extantSuper != nullptr && extantSuper->m_bIsFired && extantSuper->m_type == Familiar::Type::RemoteDetonation)
        {
            return extantSuper;
        }
    }

    return nullptr;
}

void Pilot6::HandleSuperCooldown(const float &_fDT)
{
    if (m_familiars.size() > 0 || SuperInPlay() != nullptr)
    {
        m_cooldownSuper = 0;
    }
    else
    {
        // Using m_maxCooldownSuper minus a very small amount, because if it's set to m_maxCooldownSuper outright, the meter doesn't appear onscreen.
        m_cooldownSuper = m_maxCooldownSuper - 0.1f;
    }
}
