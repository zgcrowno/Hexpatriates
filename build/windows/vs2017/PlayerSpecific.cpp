#include "PlayerSpecific.h"

using namespace hexpatriates;

void PlayerSpecific::OnCreate()
{
    int typeLength = strlen("P1");
    ScrollMod::Substring(GetModelName(), m_genericName, 0, strlen(GetModelName()) - typeLength);
    ScrollMod::Substring(GetModelName(), m_typeName, strlen(GetModelName()) - typeLength, typeLength);
    m_bIsP1 = orxString_Compare(m_typeName, "P1") == 0;
    ScrollMod::Substring(m_bIsP1 ? "P2" : "P1", m_otherTypeName, 0, typeLength);
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
