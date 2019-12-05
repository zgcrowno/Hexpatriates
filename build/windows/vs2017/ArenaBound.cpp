#include "ArenaBound.h"

using namespace hexpatriates;

void ArenaBound::OnCreate()
{
    m_electricityIconP1 = GetChildByName("O-ElectricityIconP1");
    m_electricityIconP2 = GetChildByName("O-ElectricityIconP2");
    m_electricityIconP1->Enable(false);
    m_electricityIconP2->Enable(false);
}

void ArenaBound::OnDelete()
{

}

orxBOOL ArenaBound::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void ArenaBound::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
