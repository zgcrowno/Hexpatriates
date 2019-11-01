#include "Arena.h"
#include "Zone.h"
#include <iostream>

using namespace hexpatriates;

void Arena::OnCreate()
{
    m_pilotP1 = (Pilot*)CreateObject("O-Pilot1P1");
    m_pilotP1->m_zone = (Zone*)CreateObject("O-ZoneP1");
    m_pilotP2 = (Pilot*)CreateObject("O-Pilot1P2");
    m_pilotP2->m_zone = (Zone*)CreateObject("O-ZoneP2");
    m_dashMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-DashMeterP1"));
    m_parryMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-ParryMeterP1"));
    m_livesMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-LivesMeterP1"));
    m_neutralMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-NeutralMeterP1"));
    m_upwardMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-UpwardMeterP1"));
    m_downwardMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-DownwardMeterP1"));
    m_superMeterP1 = static_cast<ScrollMod*>(GetChildByName("O-SuperMeterP1"));
    m_dashMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-DashMeterP2"));
    m_parryMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-ParryMeterP2"));
    m_livesMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-LivesMeterP2"));
    m_neutralMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-NeutralMeterP2"));
    m_upwardMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-UpwardMeterP2"));
    m_downwardMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-DownwardMeterP2"));
    m_superMeterP2 = static_cast<ScrollMod*>(GetChildByName("O-SuperMeterP2"));
    orxVECTOR variableScale = orxVECTOR_0;
    m_defaultScaleDash = m_dashMeterP1->GetScale(variableScale);
    m_defaultScaleParry = m_parryMeterP1->GetScale(variableScale);
    m_defaultScaleLives = m_livesMeterP1->GetScale(variableScale);
    m_defaultScaleNeutral = m_neutralMeterP1->GetScale(variableScale);
    m_defaultScaleUpward = m_upwardMeterP1->GetScale(variableScale);
    m_defaultScaleDownward = m_downwardMeterP1->GetScale(variableScale);
    m_defaultScaleSuper = m_superMeterP1->GetScale(variableScale);

    // Create and place the meter borders
    CreateMeterBorder("O-DashMeterP1", m_dashMeterP1, m_pilotP1->m_maxDashes);
    CreateMeterBorder("O-ParryMeterP1", m_parryMeterP1, 1);
    CreateMeterBorder("O-NeutralMeterP1", m_neutralMeterP1, m_pilotP1->m_ship->m_clipSizeNeutral);
    CreateMeterBorder("O-UpwardMeterP1", m_upwardMeterP1, m_pilotP1->m_ship->m_clipSizeUpward);
    CreateMeterBorder("O-DownwardMeterP1", m_downwardMeterP1, m_pilotP1->m_ship->m_clipSizeDownward);
    CreateMeterBorder("O-SuperMeterP1", m_superMeterP1, 1);
    CreateMeterBorder("O-DashMeterP2", m_dashMeterP2, m_pilotP2->m_maxDashes);
    CreateMeterBorder("O-ParryMeterP2", m_parryMeterP2, 1);
    CreateMeterBorder("O-NeutralMeterP2", m_neutralMeterP2, m_pilotP2->m_ship->m_clipSizeNeutral);
    CreateMeterBorder("O-UpwardMeterP2", m_upwardMeterP2, m_pilotP2->m_ship->m_clipSizeUpward);
    CreateMeterBorder("O-DownwardMeterP2", m_downwardMeterP2, m_pilotP2->m_ship->m_clipSizeDownward);
    CreateMeterBorder("O-SuperMeterP2", m_superMeterP2, 1);
}

void Arena::OnDelete()
{

}

orxBOOL Arena::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void Arena::Update(const orxCLOCK_INFO &_rstInfo)
{
    //TODO: I'll probably move this stuff to arrays at some point so as to lessen the possibility of error.
    // Handle UI appearance
    // Pilot-associated UI
    if (m_pilotP1->m_cooldownDash > 0)
    {
        m_dashMeterP1->SetScale({
            m_defaultScaleDash.fX - (m_defaultScaleDash.fX * (m_pilotP1->m_cooldownDash / m_pilotP1->m_maxCooldownDash)),
            m_defaultScaleDash.fY,
            m_defaultScaleDash.fZ });
    }
    else
    {
        m_dashMeterP1->SetScale({
            m_defaultScaleDash.fX - (m_defaultScaleDash.fX * ((float)m_pilotP1->m_usedDashes / (float)m_pilotP1->m_maxDashes)),
            m_defaultScaleDash.fY,
            m_defaultScaleDash.fZ });
    }
    m_parryMeterP1->SetScale({ m_defaultScaleParry.fX - (m_defaultScaleParry.fX * (m_pilotP1->m_cooldownParry / m_pilotP1->m_maxCooldownParry)),
        m_defaultScaleParry.fY,
        m_defaultScaleParry.fZ });
    m_livesMeterP1->SetScale({ m_defaultScaleLives.fX * ((float)m_pilotP1->m_lives / (float)m_pilotP1->m_maxLives),
        m_defaultScaleLives.fY,
        m_defaultScaleLives.fZ });
    if (m_pilotP2->m_cooldownDash > 0)
    {
        m_dashMeterP2->SetScale({
            m_defaultScaleDash.fX - (m_defaultScaleDash.fX * (m_pilotP2->m_cooldownDash / m_pilotP2->m_maxCooldownDash)),
            m_defaultScaleDash.fY,
            m_defaultScaleDash.fZ });
    }
    else
    {
        m_dashMeterP2->SetScale({
            m_defaultScaleDash.fX - (m_defaultScaleDash.fX * ((float)m_pilotP2->m_usedDashes / (float)m_pilotP2->m_maxDashes)),
            m_defaultScaleDash.fY,
            m_defaultScaleDash.fZ });
    }
    m_parryMeterP2->SetScale({ m_defaultScaleParry.fX - (m_defaultScaleParry.fX * (m_pilotP2->m_cooldownParry / m_pilotP2->m_maxCooldownParry)),
        m_defaultScaleParry.fY,
        m_defaultScaleParry.fZ });
    m_livesMeterP2->SetScale({ m_defaultScaleLives.fX * ((float)m_pilotP2->m_lives / (float)m_pilotP2->m_maxLives),
        m_defaultScaleLives.fY,
        m_defaultScaleLives.fZ });

    // Ship-associated UI
    if (m_pilotP1->m_ship->m_cooldownNeutral > 0)
    {
        m_neutralMeterP1->SetScale({
            m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * (m_pilotP1->m_ship->m_cooldownNeutral / m_pilotP1->m_ship->m_maxCooldownNeutral)),
            m_defaultScaleNeutral.fY,
            m_defaultScaleNeutral.fZ });
    }
    else
    {
        m_neutralMeterP1->SetScale({
            m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * ((float)m_pilotP1->m_ship->m_clipIndexNeutral / (float)m_pilotP1->m_ship->m_clipSizeNeutral)),
            m_defaultScaleNeutral.fY,
            m_defaultScaleNeutral.fZ });
    }
    if (m_pilotP1->m_ship->m_cooldownUpward > 0)
    {
        m_upwardMeterP1->SetScale({
            m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * (m_pilotP1->m_ship->m_cooldownUpward / m_pilotP1->m_ship->m_maxCooldownUpward)),
            m_defaultScaleUpward.fY,
            m_defaultScaleUpward.fZ });
    }
    else
    {
        m_upwardMeterP1->SetScale({
            m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * ((float)m_pilotP1->m_ship->m_clipIndexUpward / (float)m_pilotP1->m_ship->m_clipSizeUpward)),
            m_defaultScaleUpward.fY,
            m_defaultScaleUpward.fZ });
    }
    if (m_pilotP1->m_ship->m_cooldownDownward > 0)
    {
        m_downwardMeterP1->SetScale({
            m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * (m_pilotP1->m_ship->m_cooldownDownward / m_pilotP1->m_ship->m_maxCooldownDownward)),
            m_defaultScaleDownward.fY,
            m_defaultScaleDownward.fZ });
    }
    else
    {
        m_downwardMeterP1->SetScale({
            m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * ((float)m_pilotP1->m_ship->m_clipIndexDownward / (float)m_pilotP1->m_ship->m_clipSizeDownward)),
            m_defaultScaleDownward.fY,
            m_defaultScaleDownward.fZ });
    }
    m_superMeterP1->SetScale({
        m_defaultScaleSuper.fX - (m_defaultScaleSuper.fX * (m_pilotP1->m_ship->m_cooldownSuper / m_pilotP1->m_ship->m_maxCooldownSuper)),
        m_defaultScaleSuper.fY,
        m_defaultScaleSuper.fZ });
    if (m_pilotP2->m_ship->m_cooldownNeutral > 0)
    {
        m_neutralMeterP2->SetScale({
            m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * (m_pilotP2->m_ship->m_cooldownNeutral / m_pilotP2->m_ship->m_maxCooldownNeutral)),
            m_defaultScaleNeutral.fY,
            m_defaultScaleNeutral.fZ });
    }
    else
    {
        m_neutralMeterP2->SetScale({
            m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * ((float)m_pilotP2->m_ship->m_clipIndexNeutral / (float)m_pilotP2->m_ship->m_clipSizeNeutral)),
            m_defaultScaleNeutral.fY,
            m_defaultScaleNeutral.fZ });
    }
    if (m_pilotP2->m_ship->m_cooldownUpward > 0)
    {
        m_upwardMeterP2->SetScale({
            m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * (m_pilotP2->m_ship->m_cooldownUpward / m_pilotP2->m_ship->m_maxCooldownUpward)),
            m_defaultScaleUpward.fY,
            m_defaultScaleUpward.fZ });
    }
    else
    {
        m_upwardMeterP2->SetScale({
            m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * ((float)m_pilotP2->m_ship->m_clipIndexUpward / (float)m_pilotP2->m_ship->m_clipSizeUpward)),
            m_defaultScaleUpward.fY,
            m_defaultScaleUpward.fZ });
    }
    if (m_pilotP2->m_ship->m_cooldownDownward > 0)
    {
        m_downwardMeterP2->SetScale({
            m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * (m_pilotP2->m_ship->m_cooldownDownward / m_pilotP2->m_ship->m_maxCooldownDownward)),
            m_defaultScaleDownward.fY,
            m_defaultScaleDownward.fZ });
    }
    else
    {
        m_downwardMeterP2->SetScale({
            m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * ((float)m_pilotP2->m_ship->m_clipIndexDownward / (float)m_pilotP2->m_ship->m_clipSizeDownward)),
            m_defaultScaleDownward.fY,
            m_defaultScaleDownward.fZ });
    }
    m_superMeterP2->SetScale({
        m_defaultScaleSuper.fX - (m_defaultScaleSuper.fX * (m_pilotP2->m_ship->m_cooldownSuper / m_pilotP2->m_ship->m_maxCooldownSuper)),
        m_defaultScaleSuper.fY,
        m_defaultScaleSuper.fZ });
}

void Arena::CreateMeterBorder(const orxCHAR *_meterName, const ScrollMod *_meter, const int &_clipSize)
{
    orxBOOL p1 = orxString_SearchString(_meterName, "P1") != orxNULL;
    int playerMultiplier = p1 ? -1 : 1;
    orxVECTOR posRef;
    orxVECTOR scaleRef;
    ScrollObject *clipBorderTop = CreateObject("O-ClipBorderTop");
    ScrollObject *clipBorderBottom = CreateObject("O-ClipBorderBottom");
    clipBorderTop->SetPosition({ _meter->GetPosition(posRef).fX + playerMultiplier * (GetVector("Scale", &scaleRef, _meterName)->fX * GetFloat("FrustumWidth", "MainCamera")) / 2,
                                       _meter->GetPosition(posRef).fY - (GetVector("Scale", &scaleRef, _meterName)->fY * GetFloat("FrustumHeight", "MainCamera")) / 2,
                                       0 });
    clipBorderBottom->SetPosition({ _meter->GetPosition(posRef).fX + playerMultiplier * (GetVector("Scale", &scaleRef, _meterName)->fX * GetFloat("FrustumWidth", "MainCamera")) / 2,
                                       _meter->GetPosition(posRef).fY + (GetVector("Scale", &scaleRef, _meterName)->fY * GetFloat("FrustumHeight", "MainCamera")) / 2,
                                       0 });
    for (int i = 0; i <= _clipSize; i++)
    {
        ScrollObject *clipBorder;
        if (i == 0)
        {
            clipBorder = p1 ? CreateObject("O-ClipBorderRight") : CreateObject("O-ClipBorderLeft");
        }
        else if (i == _clipSize)
        {
            clipBorder = p1 ? CreateObject("O-ClipBorderLeft") : CreateObject("O-ClipBorderRight");
        }
        else
        {
            clipBorder = CreateObject("O-ClipBorder");
        }
        clipBorder->SetPosition({ _meter->GetPosition(posRef).fX + playerMultiplier * (i * ((GetVector("Scale", &scaleRef, _meterName)->fX * GetFloat("FrustumWidth", "MainCamera")) / _clipSize)),
                                       _meter->GetPosition(posRef).fY,
                                       0 });
    }
}
