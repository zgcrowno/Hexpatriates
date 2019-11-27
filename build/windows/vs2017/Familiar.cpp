#include "Familiar.h"

using namespace hexpatriates;

void Familiar::OnCreate()
{
    Projectile::OnCreate();

    m_framesBehind = GetFloat("FramesBehind", GetModelName());

    int typeLength = strlen("P1");
    orxCHAR gunTypeText[512] = "O-FamiliarGun";
    orxCHAR familiarTypeText[512];
    ScrollMod::Substring(GetModelName(), familiarTypeText, strlen(GetModelName()) - typeLength, typeLength);
    m_gun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, familiarTypeText)));
}

void Familiar::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Familiar::OnCollide(
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

    return orxTRUE;
}

void Familiar::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}

void Familiar::Move()
{
    orxVECTOR nextPosition = m_upcomingPositions.front();
    SetPosition({ nextPosition.fX, nextPosition.fY, GetPosition().fZ });
    m_upcomingPositions.pop();
}
