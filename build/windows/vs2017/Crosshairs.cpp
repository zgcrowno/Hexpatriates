#include "Crosshairs.h"

using namespace hexpatriates;

void Crosshairs::OnCreate()
{
    m_speed = GetFloat("Speed", GetModelName());
    m_decelerationDistance = GetFloat("DecelerationDistance", GetModelName());
    if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
    {
        m_target = static_cast<ScrollMod*>(Hexpatriates::GetInstance().GetPilotByPlayerType("P2"));
    }
    else
    {
        m_target = static_cast<ScrollMod*>(Hexpatriates::GetInstance().GetPilotByPlayerType("P1"));
    }
    SetPosition(m_target->GetPosition());
}

void Crosshairs::OnDelete()
{

}

orxBOOL Crosshairs::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return orxTRUE;
}

void Crosshairs::Update(const orxCLOCK_INFO &_rstInfo)
{
    MoveTo(m_target->GetPosition(), m_speed, m_decelerationDistance);
}
