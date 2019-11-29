#include "Ship6.h"

using namespace hexpatriates;

void Ship6::OnCreate()
{
    Ship::OnCreate();

    m_maxFamiliars = GetFloat("MaxFamiliars", GetModelName());

    // TODO: Get rid of this once I've done sufficient testing.
    int typeLength = strlen("P1");
    orxCHAR familiarText[512] = "O-Familiar";
    orxCHAR shipTypeText[512];
    ScrollMod::Substring(GetModelName(), shipTypeText, strlen(GetModelName()) - typeLength, typeLength);
    orxVECTOR spawnPosition = { GetPosition().fX, GetPosition().fY, GetVector("Position", "O-Familiar").fZ };
    m_familiars.push_back(static_cast<Familiar*>(CreateObject(strcat(familiarText, shipTypeText), {}, {}, { { "Position", &spawnPosition } })));
}

void Ship6::OnDelete()
{
    Ship::OnDelete();
}

orxBOOL Ship6::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Ship::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void Ship6::Update(const orxCLOCK_INFO &_rstInfo)
{
    Ship::Update(_rstInfo);
}

void Ship6::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_neutralGun->SpawnAtSelf(m_enemyDirection);
        for (Familiar *familiar : m_familiars)
        {
            familiar->m_gun->SpawnAtSelf(m_enemyDirection);
        }
    }
}

void Ship6::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        FireFamiliar(-orxMATH_KF_PI_BY_4, ETurret);
    }
}

void Ship6::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        FireFamiliar(orxMATH_KF_PI_BY_4, ETurret);
    }
}

void Ship6::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        int typeLength = strlen("P1");
        orxCHAR familiarTypeText[512];
        ScrollMod::Substring(GetModelName(), familiarTypeText, strlen(GetModelName()) - typeLength, typeLength);
        Familiar *extantSuper = static_cast<Familiar*>(Hexpatriates::GetInstance().GetFamiliarByPlayerType(familiarTypeText));

        if (extantSuper != NULL && extantSuper->m_bIsFired && extantSuper->m_type == ERemoteDetonation)
        {
            extantSuper->Detonate();
        }
        else
        {
            FireFamiliar(m_enemyDirection, ERemoteDetonation);
        }
    }
}

void Ship6::FireFamiliar(const float _direction, const FamiliarType _type)
{
    if (m_familiars.size() > 0)
    {
        m_familiars.at(m_familiars.size() - 1)->FireSelf(_direction, _type);
        m_familiars.pop_back();
    }
}
