#include "Ship.h"
#include <iostream>

using namespace hexpatriates;

void Ship::OnCreate()
{
    m_maxNeutral = orxConfig_GetFloat("MaxNeutral");
    m_maxUpward = orxConfig_GetFloat("MaxUpward");
    m_maxDownward = orxConfig_GetFloat("MaxDownward");
    m_maxCooldownNeutral = orxConfig_GetFloat("MaxCooldownNeutral");
    m_maxCooldownUpward = orxConfig_GetFloat("MaxCooldownUpward");
    m_maxCooldownDownward = orxConfig_GetFloat("MaxCooldownDownward");
    m_maxCooldownSuper = orxConfig_GetFloat("MaxCooldownSuper");
    m_cooldownSuper = m_maxCooldownSuper;
    m_neutralMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-NeutralMeter"));
    m_upwardMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-UpwardMeter"));
    m_downwardMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-DownwardMeter"));
    m_superMeter = static_cast<ScrollMod*>(Hexpatriates::GetInstance().CreateObject("O-SuperMeter"));
    orxVECTOR variableScale = orxVECTOR_0;
    m_defaultScaleNeutral = m_neutralMeter->GetScale(variableScale);
    m_defaultScaleUpward = m_upwardMeter->GetScale(variableScale);
    m_defaultScaleDownward = m_downwardMeter->GetScale(variableScale);
    m_defaultScaleSuper = m_superMeter->GetScale(variableScale);

    m_neutralGun = static_cast<ScrollMod*>(GetChildByName("O-NeutralGun"));
    m_neutralGun->Enable(orxFALSE);
    m_upwardGun = static_cast<ScrollMod*>(GetChildByName("O-UpwardGun"));
    m_upwardGun->Enable(orxFALSE);
    m_downwardGun = static_cast<ScrollMod*>(GetChildByName("O-DownwardGun"));
    m_downwardGun->Enable(orxFALSE);
    m_superGun = static_cast<ScrollMod*>(GetChildByName("O-SuperGun"));
    m_superGun->Enable(orxFALSE);
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
    // Handle Cooldowns
    if (m_cooldownNeutral > 0)
    {
        m_cooldownNeutral -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownNeutral = 0;
    }
    if (m_cooldownUpward > 0)
    {
        m_cooldownUpward -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownUpward = 0;
    }
    if (m_cooldownDownward > 0)
    {
        m_cooldownDownward -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownDownward = 0;
    }
    if (m_cooldownSuper > 0)
    {
        m_cooldownSuper -= _rstInfo.fDT;
    }
    else
    {
        m_cooldownSuper = 0;
    }
    // Handle UI appearance
    if (m_cooldownNeutral > 0)
    {
        m_neutralMeter->SetScale({ m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * (m_cooldownNeutral / m_maxCooldownNeutral)), m_defaultScaleNeutral.fY, m_defaultScaleNeutral.fZ });
    }
    else
    {
        m_neutralMeter->SetScale({ m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * ((float)m_usedNeutral / (float)m_maxNeutral)), m_defaultScaleNeutral.fY, m_defaultScaleNeutral.fZ });
    }
    if (m_cooldownUpward > 0)
    {
        m_upwardMeter->SetScale({ m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * (m_cooldownUpward / m_maxCooldownUpward)), m_defaultScaleUpward.fY, m_defaultScaleUpward.fZ });
    }
    else
    {
        m_upwardMeter->SetScale({ m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * ((float)m_usedUpward / (float)m_maxUpward)), m_defaultScaleUpward.fY, m_defaultScaleUpward.fZ });
    }
    if (m_cooldownDownward > 0)
    {
        m_downwardMeter->SetScale({ m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * (m_cooldownDownward / m_maxCooldownDownward)), m_defaultScaleDownward.fY, m_defaultScaleDownward.fZ });
    }
    else
    {
        m_downwardMeter->SetScale({ m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * ((float)m_usedDownward / (float)m_maxDownward)), m_defaultScaleDownward.fY, m_defaultScaleDownward.fZ });
    }
    m_superMeter->SetScale({ m_defaultScaleSuper.fX - (m_defaultScaleSuper.fX * (m_cooldownSuper / m_maxCooldownSuper)), m_defaultScaleSuper.fY, m_defaultScaleSuper.fZ });
}

void Ship::Neutral()
{
    if (orxInput_HasBeenActivated("Neutral"))
    {
        if (m_cooldownNeutral <= 0)
        {
            m_usedNeutral++;

            m_neutralGun->Enable(orxTRUE);

            if (m_usedNeutral == m_maxNeutral)
            {
                m_usedNeutral = 0;
                m_cooldownNeutral = m_maxCooldownNeutral;
            }
        }
    }
    else if (orxInput_HasBeenDeactivated("Neutral"))
    {
        m_neutralGun->Enable(orxFALSE);
    }
}

void Ship::Upward()
{
    if (orxInput_HasBeenActivated("Upward"))
    {
        if (m_cooldownUpward <= 0)
        {
            m_usedUpward++;

            m_upwardGun->Enable(orxTRUE);

            if (m_usedUpward == m_maxUpward)
            {
                m_usedUpward = 0;
                m_cooldownUpward = m_maxCooldownUpward;
            }
        }
    }
    else if (orxInput_HasBeenDeactivated("Upward"))
    {
        m_upwardGun->Enable(orxFALSE);
    }
}

void Ship::Downward()
{
    if (orxInput_HasBeenActivated("Downward"))
    {
        if (m_cooldownDownward <= 0)
        {
            m_usedDownward++;

            m_downwardGun->Enable(orxTRUE);

            if (m_usedDownward == m_maxDownward)
            {
                m_usedDownward = 0;
                m_cooldownDownward = m_maxCooldownDownward;
            }
        }
    }
    else if (orxInput_HasBeenDeactivated("Downward"))
    {
        m_downwardGun->Enable(orxFALSE);
    }
}

void Ship::Super()
{
    if (orxInput_HasBeenActivated("Super"))
    {
        if (m_cooldownSuper <= 0)
        {
            m_cooldownSuper = m_maxCooldownSuper;

            m_superGun->Enable(orxTRUE);

            m_cooldownSuper = m_maxCooldownSuper;
        }
    }
}
