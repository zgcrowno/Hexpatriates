#include "Arena.h"
#include "Zone.h"

using namespace hexpatriates;

void Arena::OnCreate()
{
    m_timer = 90.0;
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
    m_timerText = static_cast<ScrollMod*>(GetChildByName("O-TimerText"));
    m_defaultScaleDash = m_dashMeterP1->GetScale();
    m_defaultScaleParry = m_parryMeterP1->GetScale();
    m_defaultScaleLives = m_livesMeterP1->GetScale();
    m_defaultScaleNeutral = m_neutralMeterP1->GetScale();
    m_defaultScaleUpward = m_upwardMeterP1->GetScale();
    m_defaultScaleDownward = m_downwardMeterP1->GetScale();
    m_defaultScaleSuper = m_superMeterP1->GetScale();
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
    // Handle timer decrement and response
    m_timer -= _rstInfo.fDT;
    if (m_timer <= 0.0)
    {
        Restart();
    }
    SetTimerText();

    // Force Pilots to face each other
    orxFLOAT pilotP1X = m_pilotP1->GetPosition().fX;
    orxFLOAT pilotP2X = m_pilotP2->GetPosition().fX;

    if (pilotP1X <= pilotP2X)
    {
        if (!m_pilotP1->m_ship->IsEnabled())
        {
            m_pilotP1->SetFlip(orxFALSE, orxFALSE);
        }
        if (!m_pilotP2->m_ship->IsEnabled())
        {
            m_pilotP2->SetFlip(orxTRUE, orxFALSE);
        }
    }
    else
    {
        if (!m_pilotP1->m_ship->IsEnabled())
        {
            m_pilotP1->SetFlip(orxTRUE, orxFALSE);
        }
        if (!m_pilotP2->m_ship->IsEnabled())
        {
            m_pilotP2->SetFlip(orxFALSE, orxFALSE);
        }
    }

    // Respond to pilot death(s)
    if (!m_pilotP1->IsEnabled() || !m_pilotP2->IsEnabled())
    {
        if (m_pilotP1->m_lives == 0 || m_pilotP2->m_lives == 0)
        {
            Restart();
        }
        else
        {
            m_pilotP1->Enable(orxTRUE);
            m_pilotP2->Enable(orxTRUE);
            m_pilotP1->ConstructShip();
            m_pilotP2->ConstructShip();
            m_timer = 90.0;
        }
    }

    // TODO: I'll probably move this stuff to arrays at some point so as to lessen the possibility of error.
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

    //Disable meters with scales of 0 (and enable meters with scales greater than 0) so as to prevent the renderer from complaining.
    if (m_dashMeterP1->GetScale().fX <= 0)
    {
        m_dashMeterP1->Enable(false);
    }
    else
    {
        m_dashMeterP1->Enable(true);
    }
    if (m_parryMeterP1->GetScale().fX <= 0)
    {
        m_parryMeterP1->Enable(false);
    }
    else
    {
        m_parryMeterP1->Enable(true);
    }
    if (m_livesMeterP1->GetScale().fX <= 0)
    {
        m_livesMeterP1->Enable(false);
    }
    else
    {
        m_livesMeterP1->Enable(true);
    }
    if (m_neutralMeterP1->GetScale().fX <= 0)
    {
        m_neutralMeterP1->Enable(false);
    }
    else
    {
        m_neutralMeterP1->Enable(true);
    }
    if (m_upwardMeterP1->GetScale().fX <= 0)
    {
        m_upwardMeterP1->Enable(false);
    }
    else
    {
        m_upwardMeterP1->Enable(true);
    }
    if (m_downwardMeterP1->GetScale().fX <= 0)
    {
        m_downwardMeterP1->Enable(false);
    }
    else
    {
        m_downwardMeterP1->Enable(true);
    }
    if (m_superMeterP1->GetScale().fX <= 0)
    {
        m_superMeterP1->Enable(false);
    }
    else
    {
        m_superMeterP1->Enable(true);
    }
    if (m_dashMeterP2->GetScale().fX <= 0)
    {
        m_dashMeterP2->Enable(false);
    }
    else
    {
        m_dashMeterP2->Enable(true);
    }
    if (m_parryMeterP2->GetScale().fX <= 0)
    {
        m_parryMeterP2->Enable(false);
    }
    else
    {
        m_parryMeterP2->Enable(true);
    }
    if (m_livesMeterP2->GetScale().fX <= 0)
    {
        m_livesMeterP2->Enable(false);
    }
    else
    {
        m_livesMeterP2->Enable(true);
    }
    if (m_neutralMeterP2->GetScale().fX <= 0)
    {
        m_neutralMeterP2->Enable(false);
    }
    else
    {
        m_neutralMeterP2->Enable(true);
    }
    if (m_upwardMeterP2->GetScale().fX <= 0)
    {
        m_upwardMeterP2->Enable(false);
    }
    else
    {
        m_upwardMeterP2->Enable(true);
    }
    if (m_downwardMeterP2->GetScale().fX <= 0)
    {
        m_downwardMeterP2->Enable(false);
    }
    else
    {
        m_downwardMeterP2->Enable(true);
    }
    if (m_superMeterP2->GetScale().fX <= 0)
    {
        m_superMeterP2->Enable(false);
    }
    else
    {
        m_superMeterP2->Enable(true);
    }
}

void Arena::Restart()
{
    // TODO: I'm calling all of this code here, and in PilotSelectMenu. I'll need to clean this up quite a bit at some point.
    Arena *restartedArena = static_cast<Arena*>(CreateObject("O-Arena"));
    restartedArena->m_pilotP1 = (Pilot*)CreateObject(m_pilotP1->GetModelName());
    restartedArena->m_pilotP1->m_zone = (Zone*)CreateObject(m_pilotP1->m_zone->GetModelName());
    restartedArena->m_pilotP2 = (Pilot*)CreateObject(m_pilotP2->GetModelName());
    restartedArena->m_pilotP2->m_zone = (Zone*)CreateObject(m_pilotP2->m_zone->GetModelName());
    restartedArena->m_pilotP1->m_opposingPilot = restartedArena->m_pilotP2;
    restartedArena->m_pilotP2->m_opposingPilot = restartedArena->m_pilotP1;

    // TODO: This will do for now, but I ought to manage this using the config, eventually.
    // Create and place the meter borders (and clip dividers)
    restartedArena->CreateMeterBorders();

    m_pilotP1->Destroy();
    m_pilotP2->Destroy();
    Destroy();
}

void Arena::SetTimerText()
{
    orxCHAR formattedTimerText[3];
    orxCOLOR color;

    orxString_Print(formattedTimerText, "%1.0f", m_timer);
    color.vRGB = { 1.0, 1.0, 1.0 };
    color.fAlpha = 1.0;
    orxObject_SetTextString(m_timerText->GetOrxObject(), formattedTimerText);
    orxObject_SetColor(m_timerText->GetOrxObject(), &color);
}

// TODO: This will do for now, but I ought to manage this using the config, eventually.
void Arena::CreateMeterBorder(const orxCHAR *_meterName, const ScrollMod *_meter, const int &_clipSize)
{
    orxBOOL p1 = orxString_SearchString(_meterName, "P1") != orxNULL;
    int playerMultiplier = p1 ? -1 : 1;
    orxFLOAT borderThicknessY = _meter->GetScale().fY / 10;
    orxFLOAT borderThicknessX = borderThicknessY * (_meter->GetSize().fY / _meter->GetSize().fX);

    // Create the top clip border
    ScrollObject *clipBorderTop = CreateObject("O-ClipBorderTop");
    clipBorderTop->SetPosition({ _meter->GetPosition().fX + playerMultiplier * (GetVector("Scale", _meterName).fX * GetFloat("FrustumWidth", "MainCamera")) / 2,
                                       _meter->GetPosition().fY - (GetVector("Scale", _meterName).fY * GetFloat("FrustumHeight", "MainCamera")) / 2,
                                       0 });
    clipBorderTop->SetScale({ _meter->GetScale().fX,
                                       borderThicknessY,
                                       0 });
    // Create the bottom clip border
    ScrollObject *clipBorderBottom = CreateObject("O-ClipBorderBottom");
    clipBorderBottom->SetPosition({ _meter->GetPosition().fX + playerMultiplier * (GetVector("Scale", _meterName).fX * GetFloat("FrustumWidth", "MainCamera")) / 2,
                                       _meter->GetPosition().fY + (GetVector("Scale", _meterName).fY * GetFloat("FrustumHeight", "MainCamera")) / 2,
                                       0 });
    clipBorderBottom->SetScale({ _meter->GetScale().fX,
                                       borderThicknessY,
                                       0 });
    // Create all of the clip dividers (if there are any)
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
        clipBorder->SetPosition({ _meter->GetPosition().fX + playerMultiplier * (i * ((GetVector("Scale", _meterName).fX * GetFloat("FrustumWidth", "MainCamera")) / _clipSize)),
                                       _meter->GetPosition().fY,
                                       0 });
        clipBorder->SetScale({ borderThicknessX,
                                       _meter->GetScale().fY,
                                       0 });
    }
}

void Arena::CreateMeterBorders()
{
    CreateMeterBorder("O-DashMeterP1", m_dashMeterP1, m_pilotP1->m_maxDashes);
    CreateMeterBorder("O-ParryMeterP1", m_parryMeterP1, 1);
    CreateMeterBorder("O-NeutralMeterP1", m_neutralMeterP1, m_pilotP1->m_ship->m_clipSizeNeutral);
    CreateMeterBorder("O-UpwardMeterP1", m_upwardMeterP1, m_pilotP1->m_ship->m_clipSizeUpward);
    CreateMeterBorder("O-DownwardMeterP1", m_downwardMeterP1, m_pilotP1->m_ship->m_clipSizeDownward);
    CreateMeterBorder("O-SuperMeterP1", m_superMeterP1, 1);
    CreateMeterBorder("O-LivesMeterP1", m_livesMeterP1, m_pilotP1->m_maxLives);
    CreateMeterBorder("O-DashMeterP2", m_dashMeterP2, m_pilotP2->m_maxDashes);
    CreateMeterBorder("O-ParryMeterP2", m_parryMeterP2, 1);
    CreateMeterBorder("O-NeutralMeterP2", m_neutralMeterP2, m_pilotP2->m_ship->m_clipSizeNeutral);
    CreateMeterBorder("O-UpwardMeterP2", m_upwardMeterP2, m_pilotP2->m_ship->m_clipSizeUpward);
    CreateMeterBorder("O-DownwardMeterP2", m_downwardMeterP2, m_pilotP2->m_ship->m_clipSizeDownward);
    CreateMeterBorder("O-SuperMeterP2", m_superMeterP2, 1);
    CreateMeterBorder("O-LivesMeterP2", m_livesMeterP2, m_pilotP2->m_maxLives);
}
