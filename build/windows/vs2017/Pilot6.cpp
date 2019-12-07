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

void Pilot6::Move(const orxCLOCK_INFO &_rstInfo, const bool &_bAllowVerticalMovement)
{
    Pilot::Move(_rstInfo, _bAllowVerticalMovement);

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

void Pilot6::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_ship->m_neutralGun->SpawnAtSelf(m_enemyDirection);
        for (Familiar *familiar : m_familiars)
        {
            familiar->m_gun->SpawnAtSelf(m_enemyDirection);
        }
    }
}

void Pilot6::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        FireFamiliar(-orxMATH_KF_PI_BY_4, Familiar::Type::Turret);
    }
}

void Pilot6::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        FireFamiliar(orxMATH_KF_PI_BY_4, Familiar::Type::Turret);
    }
}

void Pilot6::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        bool bSuperInPlay = false;
        Familiar *extantSuper;

        int typeLength = strlen("P1");
        orxCHAR familiarTypeText[512];
        ScrollMod::Substring(GetModelName(), familiarTypeText, strlen(GetModelName()) - typeLength, typeLength);
        std::vector<ScrollObject*> extantFamiliars = Hexpatriates::GetInstance().GetFamiliarsByPlayerType(familiarTypeText);

        for (int i = 0; i < extantFamiliars.size(); i++)
        {
            extantSuper = static_cast<Familiar*>(extantFamiliars.at(i));

            if (extantSuper != NULL && extantSuper->m_bIsFired && extantSuper->m_type == Familiar::Type::RemoteDetonation)
            {
                bSuperInPlay = true;
                break;
            }
        }

        if (bSuperInPlay)
        {
            extantSuper->Detonate();
        }
        else
        {
            FireFamiliar(m_enemyDirection, Familiar::Type::RemoteDetonation);
        }
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
        int typeLength = strlen("P1");
        orxCHAR familiarText[512] = "O-Familiar";
        orxCHAR pilotTypeText[512];
        ScrollMod::Substring(GetModelName(), pilotTypeText, strlen(GetModelName()) - typeLength, typeLength);
        orxVECTOR spawnPosition = { GetPosition().fX, GetPosition().fY, GetVector("Position", "O-Familiar").fZ };

        m_familiars.push_back(static_cast<Familiar*>(CreateObject(strcat(familiarText, pilotTypeText), {}, {}, { { "Position", &spawnPosition } })));
        m_familiars.at(m_familiars.size() - 1)->m_framesBehind *= m_familiars.size();
    }
}
