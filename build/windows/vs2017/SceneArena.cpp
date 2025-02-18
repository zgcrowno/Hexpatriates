#include "SceneArena.h"
#include "AudioManager.h"
#include "SceneMenu.h"
#include "Zone.h"

using namespace hexpatriates;

void SceneArena::OnCreate()
{
    Scene::OnCreate();

    m_matchTime = GetFloat("MatchTime", GetModelName());
    m_timer = m_matchTime;
    m_contractionSpeed = GetFloat("ContractionSpeed", GetModelName());
    m_bounds = ScrollCast<ArenaBounds*>(GetChildByName("O-Walls"));

    // Making sure to Set O-Pilot's parent before each pilot creation, so they inherit the correct section values based upon player.
    orxConfig_SetParent("O-Pilot", "O-PilotP1");
    m_pilotP1 = ScrollCast<Pilot*>(CreateObject(GetString("PilotP1", GetModelName())));
    orxConfig_SetParent("O-Pilot", "O-PilotP2");
    m_pilotP2 = ScrollCast<Pilot*>(CreateObject(GetString("PilotP2", GetModelName())));

    m_pilotP1->SetOwner(this);
    m_pilotP2->SetOwner(this);
    m_pilotP1->m_opposingPilot = m_pilotP2;
    m_pilotP2->m_opposingPilot = m_pilotP1;
    m_targetScalePilotP1 = m_pilotP1->GetScale();
    m_targetScalePilotP2 = m_pilotP2->GetScale();
    m_targetScale1PilotP1 = { m_targetScalePilotP1.fX + 0.6f, m_targetScalePilotP1.fY + 0.6f, m_targetScalePilotP1.fZ };
    m_targetScale2PilotP1 = { m_targetScalePilotP1.fX + 1.2f, m_targetScalePilotP1.fY + 1.2f, m_targetScalePilotP1.fZ };
    m_targetScale3PilotP1 = { m_targetScalePilotP1.fX + 1.8f, m_targetScalePilotP1.fY + 1.8f, m_targetScalePilotP1.fZ };
    m_targetScale1PilotP2 = { m_targetScalePilotP2.fX + 0.6f, m_targetScalePilotP2.fY + 0.6f, m_targetScalePilotP2.fZ };
    m_targetScale2PilotP2 = { m_targetScalePilotP2.fX + 1.2f, m_targetScalePilotP2.fY + 1.2f, m_targetScalePilotP2.fZ };
    m_targetScale3PilotP2 = { m_targetScalePilotP2.fX + 1.8f, m_targetScalePilotP2.fY + 1.8f, m_targetScalePilotP2.fZ };
    m_pilotP1Music = AudioManager::GetInstance()->m_pilotMusicMap.at(m_pilotP1->m_genericName);
    m_pilotP2Music = AudioManager::GetInstance()->m_pilotMusicMap.at(m_pilotP2->m_genericName);
    m_partition = ScrollCast<ScrollMod*>(GetChildByName("O-Partition"));
    m_livesMeterP1 = ScrollCast<ScrollMod*>(GetChildByName("O-LivesMeterP1"));
    m_superMeterP1 = ScrollCast<ScrollMod*>(GetChildByName("O-SuperMeterP1"));
    m_livesMeterP2 = ScrollCast<ScrollMod*>(GetChildByName("O-LivesMeterP2"));
    m_superMeterP2 = ScrollCast<ScrollMod*>(GetChildByName("O-SuperMeterP2"));
    m_timerText = ScrollCast<ScrollMod*>(GetChildByName("O-TimerText"));
    m_defaultScaleLives = m_livesMeterP1->GetScale();
    m_defaultScaleSuper = m_superMeterP1->GetScale();
    CreateMeterBorders();

    // Ensure that menu music is stopped upon arena creation
    orxSound_Stop(AudioManager::GetInstance()->m_menuMusic);
    orxSound_SetTime(AudioManager::GetInstance()->m_menuMusic, 0);
    // Play arena music
    orxSound_Play(m_pilotP1Music);
    orxSound_Play(m_pilotP2Music);
    orxSound_SetVolume(m_pilotP1Music, 1);
    if (m_pilotP1Music != m_pilotP2Music)
    {
        orxSound_SetVolume(m_pilotP2Music, 0);
    }
}

void SceneArena::OnDelete()
{
    Scene::OnDelete();
}

orxBOOL SceneArena::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Scene::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void SceneArena::Update(const orxCLOCK_INFO &_rstInfo)
{
    Scene::Update(_rstInfo);

    if (!m_bIsRoundOver)
    {
        if (!m_bIsPausedForContraction)
        {
            // Handle timer decrement and response
            m_timer -= _rstInfo.fDT;
            if (m_timer <= 0.0)
            {
                m_bIsRoundOver = true;
            }
            SetTimerText();

            // Play expansion warning sounds as appropriate
            int threeFourthsMatchTime = 3 * m_matchTime / 4;
            int oneHalfMatchTime = m_matchTime / 2;
            int oneFourthMatchTime = m_matchTime / 4;
            bool bPlayTimerBeep =
                (m_timer <= threeFourthsMatchTime + 3 && m_timer + _rstInfo.fDT > threeFourthsMatchTime + 3) ||
                (m_timer <= threeFourthsMatchTime + 2 && m_timer + _rstInfo.fDT > threeFourthsMatchTime + 2) ||
                (m_timer <= threeFourthsMatchTime + 1 && m_timer + _rstInfo.fDT > threeFourthsMatchTime + 1) ||
                (m_timer <= oneHalfMatchTime + 3 && m_timer + _rstInfo.fDT > oneHalfMatchTime + 3) ||
                (m_timer <= oneHalfMatchTime + 2 && m_timer + _rstInfo.fDT > oneHalfMatchTime + 2) ||
                (m_timer <= oneHalfMatchTime + 1 && m_timer + _rstInfo.fDT > oneHalfMatchTime + 1) ||
                (m_timer <= oneFourthMatchTime + 3 && m_timer + _rstInfo.fDT > oneFourthMatchTime + 3) ||
                (m_timer <= oneFourthMatchTime + 2 && m_timer + _rstInfo.fDT > oneFourthMatchTime + 2) ||
                (m_timer <= oneFourthMatchTime + 1 && m_timer + _rstInfo.fDT > oneFourthMatchTime + 1);
            if (bPlayTimerBeep)
            {
                orxSound_Play(AudioManager::GetInstance()->m_timerBeep);
            }
        }

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
                m_bIsRoundOver = true;
            }
            else
            {
                if (!m_pilotP1->IsEnabled())
                {
                    m_pilotP1->Enable(true);
                    m_pilotP1->ConstructShip();
                }
                if (!m_pilotP2->IsEnabled())
                {
                    m_pilotP2->Enable(true);
                    m_pilotP2->ConstructShip();
                }
            }
        }
        // Handle music shifting.
        if (m_pilotP1->m_lives > m_pilotP2->m_lives)
        {
            AudioManager::CrossFade(m_pilotP2Music, m_pilotP1Music, 1, _rstInfo.fDT);
        }
        else if (m_pilotP2->m_lives > m_pilotP1->m_lives)
        {
            AudioManager::CrossFade(m_pilotP1Music, m_pilotP2Music, 1, _rstInfo.fDT);
        }

        // TODO: Make a method for this, so as to avoid repeated code.
        // Handle arena contraction.
        if (m_timer <= m_matchTime / 4)
        {
            m_targetScalePilotP1 = m_targetScale3PilotP1;
            m_targetScalePilotP2 = m_targetScale3PilotP2;
        }
        else if (m_timer <= m_matchTime / 2)
        {
            m_targetScalePilotP1 = m_targetScale2PilotP1;
            m_targetScalePilotP2 = m_targetScale2PilotP2;
        }
        else if (m_timer <= 3 * m_matchTime / 4)
        {
            m_targetScalePilotP1 = m_targetScale1PilotP1;
            m_targetScalePilotP2 = m_targetScale1PilotP2;
        }
        orxVECTOR curPilotP1Scale = m_pilotP1->GetScale();
        orxVECTOR curPilotP2Scale = m_pilotP2->GetScale();
        if (m_targetScalePilotP1.fX > curPilotP1Scale.fX || m_targetScalePilotP2.fX > curPilotP2Scale.fX)
        {
            PauseForContraction(true);

            float newPilotP1ScaleX = curPilotP1Scale.fX + m_contractionSpeed * _rstInfo.fDT;
            float newPilotP1ScaleY = curPilotP1Scale.fY + m_contractionSpeed * _rstInfo.fDT;
            orxVECTOR newPilotP1Scale = { newPilotP1ScaleX, newPilotP1ScaleY, m_targetScalePilotP1.fZ };
            float newPilotP2ScaleX = curPilotP2Scale.fX + m_contractionSpeed * _rstInfo.fDT;
            float newPilotP2ScaleY = curPilotP2Scale.fY + m_contractionSpeed * _rstInfo.fDT;
            orxVECTOR newPilotP2Scale = { newPilotP2ScaleX, newPilotP2ScaleY, m_targetScalePilotP1.fZ };
            orxVector_Clamp(&newPilotP1Scale, &newPilotP1Scale, &curPilotP1Scale, &m_targetScalePilotP1);
            orxVector_Clamp(&newPilotP2Scale, &newPilotP2Scale, &curPilotP2Scale, &m_targetScalePilotP2);
            m_pilotP1->SetScale({ newPilotP1ScaleX, newPilotP1ScaleY, m_targetScalePilotP1.fZ });
            m_pilotP2->SetScale({ newPilotP2ScaleX, newPilotP2ScaleY, m_targetScalePilotP2.fZ });
        }
        else
        {
            if (!m_pilotP1->m_ship->IsEnabled())
            {
                std::string shipName = m_pilotP1->GetModelName();
                std::string shipNumber = shipName.substr(7, 1);
                m_pilotP1->SetBodyPartSolid("BP-Ship" + shipNumber, false);
            }
            if (!m_pilotP2->m_ship->IsEnabled())
            {
                std::string shipName = m_pilotP2->GetModelName();
                std::string shipNumber = shipName.substr(7, 1);
                m_pilotP2->SetBodyPartSolid("BP-Ship" + shipNumber, false);
            }
            PauseForContraction(false);

            // Handle pausing.
            if (orxInput_HasBeenActivated(m_pilotP1->m_pauseInput.c_str()) || orxInput_HasBeenActivated(m_pilotP2->m_pauseInput.c_str()))
            {
                Hexpatriates::GetInstance().PauseGame(true);
                // Pause music.
                orxSound_Pause(m_pilotP1Music);
                orxSound_Pause(m_pilotP2Music);
            }
        }

        // TODO: I'll probably move this stuff to arrays at some point so as to lessen the possibility of error.
        // Handle UI appearance
        // Pilot-associated UI
        m_livesMeterP1->SetScale({ m_defaultScaleLives.fX * ((float)m_pilotP1->m_lives / (float)m_pilotP1->m_maxLives),
            m_defaultScaleLives.fY,
            m_defaultScaleLives.fZ });
        m_livesMeterP2->SetScale({ m_defaultScaleLives.fX * ((float)m_pilotP2->m_lives / (float)m_pilotP2->m_maxLives),
            m_defaultScaleLives.fY,
            m_defaultScaleLives.fZ });

        // Ship-associated UI
        m_superMeterP1->SetScale({
            m_defaultScaleSuper.fX - (m_defaultScaleSuper.fX * (m_pilotP1->m_cooldownSuper / m_pilotP1->m_maxCooldownSuper)),
            m_defaultScaleSuper.fY,
            m_defaultScaleSuper.fZ });
        m_superMeterP2->SetScale({
            m_defaultScaleSuper.fX - (m_defaultScaleSuper.fX * (m_pilotP2->m_cooldownSuper / m_pilotP2->m_maxCooldownSuper)),
            m_defaultScaleSuper.fY,
            m_defaultScaleSuper.fZ });

        if (m_livesMeterP1->GetScale().fX <= 0)
        {
            m_livesMeterP1->Enable(false);
        }
        else
        {
            m_livesMeterP1->Enable(true);
        }
        if (m_superMeterP1->GetScale().fX <= 0)
        {
            m_superMeterP1->Enable(false);
        }
        else
        {
            m_superMeterP1->Enable(true);
        }
        if (m_livesMeterP2->GetScale().fX <= 0)
        {
            m_livesMeterP2->Enable(false);
        }
        else
        {
            m_livesMeterP2->Enable(true);
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
    // Execute round over behavior.
    else
    {
        // Transition to the match end scene.
        Scene::TransitionToScene("O-ToSceneMatchEnd");
    }
}

void SceneArena::SetTimerText()
{
    orxCHAR formattedTimerText[4];
    orxCOLOR color;

    orxString_Print(formattedTimerText, "%1.0f", m_timer);
    color.vRGB = { 1.0, 1.0, 1.0 };
    color.fAlpha = 1.0;
    orxObject_SetTextString(m_timerText->GetOrxObject(), formattedTimerText);
    orxObject_SetColor(m_timerText->GetOrxObject(), &color);
}

// TODO: This will do for now, but I ought to manage this using the config, eventually.
void SceneArena::CreateMeterBorder(const std::string _meterName, const ScrollMod *_meter, const int &_clipSize)
{
    orxBOOL p1 = orxString_SearchString(_meterName.c_str(), "P1") != orxNULL;
    int playerMultiplier = p1 ? -1 : 1;
    orxFLOAT borderThicknessY = _meter->GetScale().fY / 10;
    orxFLOAT borderThicknessX = borderThicknessY * (_meter->GetSize().fY / _meter->GetSize().fX);

    // Create the top clip border
    ScrollObject *clipBorderTop = CreateObject("O-ClipBorderTop");
    clipBorderTop->SetPosition({ _meter->GetPosition().fX + playerMultiplier * (GetVector("Scale", _meterName).fX * GetFloat("FrustumWidth", "MainCamera")) / 2,
                                       _meter->GetPosition().fY - (GetVector("Scale", _meterName).fY * GetFloat("FrustumHeight", "MainCamera")) / 2,
                                       GetVector("Position", clipBorderTop->GetModelName()).fZ });
    clipBorderTop->SetScale({ _meter->GetScale().fX,
                                       borderThicknessY,
                                       0 });
    orxObject_SetOwner(clipBorderTop->GetOrxObject(), _meter->GetOrxObject());
    // Create the bottom clip border
    ScrollObject *clipBorderBottom = CreateObject("O-ClipBorderBottom");
    clipBorderBottom->SetPosition({ _meter->GetPosition().fX + playerMultiplier * (GetVector("Scale", _meterName).fX * GetFloat("FrustumWidth", "MainCamera")) / 2,
                                       _meter->GetPosition().fY + (GetVector("Scale", _meterName).fY * GetFloat("FrustumHeight", "MainCamera")) / 2,
                                       GetVector("Position", clipBorderBottom->GetModelName()).fZ });
    clipBorderBottom->SetScale({ _meter->GetScale().fX,
                                       borderThicknessY,
                                       0 });
    orxObject_SetOwner(clipBorderBottom->GetOrxObject(), _meter->GetOrxObject());
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
                                       GetVector("Position", clipBorder->GetModelName()).fZ });
        clipBorder->SetScale({ borderThicknessX,
                                       _meter->GetScale().fY,
                                       0 });
        orxObject_SetOwner(clipBorder->GetOrxObject(), _meter->GetOrxObject());
    }
}

void SceneArena::PauseForContraction(bool _pause)
{
    m_bIsPausedForContraction = _pause;
    for (ScrollObject *poObject = Hexpatriates::GetInstance().GetNextObject(); poObject; poObject = Hexpatriates::GetInstance().GetNextObject(poObject))
    {
        if (poObject->TestFlags(ScrollObject::FlagPausable) &&
            orxString_Compare(poObject->GetModelName(), GetModelName().c_str()) != 0)
        {
            poObject->Pause(_pause);
        }
    }
    orxPhysics_EnableSimulation(!_pause);
}

void SceneArena::CreateMeterBorders()
{
    CreateMeterBorder("O-SuperMeterP1", m_superMeterP1, 1);
    CreateMeterBorder("O-LivesMeterP1", m_livesMeterP1, m_pilotP1->m_maxLives);
    CreateMeterBorder("O-SuperMeterP2", m_superMeterP2, 1);
    CreateMeterBorder("O-LivesMeterP2", m_livesMeterP2, m_pilotP2->m_maxLives);
}
