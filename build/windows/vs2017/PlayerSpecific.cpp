#include "PlayerSpecific.h"

using namespace hexpatriates;

void PlayerSpecific::OnCreate()
{
    int typeLength = strlen("P1");
    std::string modelName(GetModelName());
    m_genericName = modelName.substr(0, modelName.size() - typeLength);
    m_typeName = modelName.substr(modelName.size() - typeLength, typeLength);
    m_bIsP1 = orxString_Compare(m_typeName.c_str(), "P1") == 0;
    m_otherTypeName = m_bIsP1 ? "P2" : "P1";
}

void PlayerSpecific::OnDelete()
{

}

orxBOOL PlayerSpecific::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void PlayerSpecific::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
