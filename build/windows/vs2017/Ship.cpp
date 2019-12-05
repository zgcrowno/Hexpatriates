#include "Ship.h"

using namespace hexpatriates;

void Ship::OnCreate()
{
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
    return true;
}

void Ship::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
