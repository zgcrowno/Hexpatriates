#include "Ship3.h"

using namespace hexpatriates;

void Ship3::OnCreate()
{
    Ship::OnCreate();
}

void Ship3::OnDelete()
{
    Ship::OnDelete();
}

orxBOOL Ship3::OnCollide(
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

void Ship3::Update(const orxCLOCK_INFO &_rstInfo)
{
    Ship::Update(_rstInfo);
}

void Ship3::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        float shotDirection = m_enemyDirection - orxMATH_KF_PI;
        m_neutralGun->Spawn(shotDirection);

        ScrollMod *laserPortalEntrance;
        orxVECTOR startingPos = m_neutralGun->GetPosition(true);
        // Using 10000 purely to have a huge number which results in the arena being traversed in full.
        orxVECTOR endingPos = { startingPos.fX + orxMath_Cos(shotDirection) * 10000.0f, startingPos.fY + orxMath_Sin(shotDirection) * 10000.0f };
        orxVECTOR hitPos;
        orxVECTOR hitNormal;
        orxObject_Raycast(&startingPos, &endingPos, 0xFFFF, orxPhysics_GetCollisionFlagValue("geometry"), true, &hitPos, &hitNormal);
        float normalDirection = orxMath_ATan(hitNormal.fY, hitNormal.fX);
        if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
        {
            laserPortalEntrance = CreateObject("O-LaserPortalEntranceP1", {}, { {"ExitDirection", normalDirection} }, { {"Position", &hitPos} });
        }
        else
        {
            laserPortalEntrance = CreateObject("O-LaserPortalEntranceP2", {}, { {"ExitDirection", normalDirection} }, { {"Position", &hitPos} });
        }
    }
}

void Ship3::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_upwardGun->Spawn(orxMath_GetRandomFloat(-orxMATH_KF_PI_BY_4 / 2.0, -orxMATH_KF_PI_BY_4 - orxMATH_KF_PI_BY_4 / 2.0));
    }
}

void Ship3::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_downwardGun->Spawn(orxMATH_KF_PI_BY_2);
    }
}

void Ship3::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        /*if (m_wavesIndexSuper % 2 == 0)
        {*/
        m_superGun->Spawn(m_enemyDirection - orxMATH_KF_PI_BY_4 / 2 + (i * (orxMATH_KF_PI_BY_4 / 4)));
        /*}
        else
        {
            m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i + (m_enemyDirection + orxMATH_KF_PI_BY_4) / 2);
        }*/
    }
}
