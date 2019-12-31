#include "Ship.h"

using namespace hexpatriates;

void Ship::OnCreate()
{
    PlayerSpecific::OnCreate();

    int typeLength = strlen("1P1");
    std::string modelName(GetModelName());
    std::string shipTypeText = modelName.substr(modelName.size() - typeLength, typeLength);
    m_neutralGun = static_cast<Spawner*>(GetChildByName("O-NeutralGun" + shipTypeText));
    m_upwardGun = static_cast<Spawner*>(GetChildByName("O-UpwardGun" + shipTypeText));
    m_downwardGun = static_cast<Spawner*>(GetChildByName("O-DownwardGun" + shipTypeText));
    m_superGun = static_cast<Spawner*>(GetChildByName("O-SuperGun" + shipTypeText));
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
