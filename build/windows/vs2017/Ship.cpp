#include "Ship.h"

using namespace hexpatriates;

void Ship::OnCreate()
{
    PlayerSpecific::OnCreate();

    int typeLength = strlen("1P1");
    orxCHAR gunTypeText[512] = "O-NeutralGun";
    orxCHAR shipTypeText[512];
    ScrollMod::Substring(GetModelName(), shipTypeText, strlen(GetModelName()) - typeLength, typeLength);
    m_neutralGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
    strcpy(gunTypeText, "O-UpwardGun");
    m_upwardGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
    strcpy(gunTypeText, "O-DownwardGun");
    m_downwardGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
    strcpy(gunTypeText, "O-SuperGun");
    m_superGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
}

void Ship::OnDelete()
{

}

orxBOOL Ship::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    // Check for collisions with the Ship's body
    if (orxString_Compare(_zPartName, "BP-Ship") == 0)
    {
        // Floor collisions
        if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0)
        {
            m_bIsAgainstFloor = true;
        }
    }

    return true;
}

orxBOOL Ship::OnSeparate(ScrollObject *_poCollider)
{
    if (orxString_Compare(_poCollider->GetModelName(), "O-WallFloor") == 0)
    {
        m_bIsAgainstFloor = false;
    }

    return true;
}

void Ship::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
