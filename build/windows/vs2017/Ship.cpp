#include "Ship.h"
#include <iostream>

using namespace hexpatriates;

void Ship::OnCreate()
{
    m_clipSizeNeutral = orxConfig_GetFloat("ClipSizeNeutral");
    m_clipSizeUpward = orxConfig_GetFloat("ClipSizeUpward");
    m_clipSizeDownward = orxConfig_GetFloat("ClipSizeDownward");
    m_waveSizeNeutral = orxConfig_GetFloat("WaveSizeNeutral");
    m_waveSizeUpward = orxConfig_GetFloat("WaveSizeUpward");
    m_waveSizeDownward = orxConfig_GetFloat("WaveSizeDownward");
    m_waveSizeSuper = orxConfig_GetFloat("WaveSizeSuper");
    m_numWavesNeutral = orxConfig_GetFloat("NumWavesNeutral");
    m_numWavesUpward = orxConfig_GetFloat("NumWavesUpward");
    m_numWavesDownward = orxConfig_GetFloat("NumWavesDownward");
    m_numWavesSuper = orxConfig_GetFloat("NumWavesSuper");
    m_maxCooldownNeutral = orxConfig_GetFloat("MaxCooldownNeutral");
    m_maxCooldownUpward = orxConfig_GetFloat("MaxCooldownUpward");
    m_maxCooldownDownward = orxConfig_GetFloat("MaxCooldownDownward");
    m_maxCooldownSuper = orxConfig_GetFloat("MaxCooldownSuper");
    m_maxWaveDelayNeutral = orxConfig_GetFloat("MaxWaveDelayNeutral");
    m_maxWaveDelayUpward = orxConfig_GetFloat("MaxWaveDelayUpward");
    m_maxWaveDelayDownward = orxConfig_GetFloat("MaxWaveDelayDownward");
    m_maxWaveDelaySuper = orxConfig_GetFloat("MaxWaveDelaySuper");
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

    m_neutralGun = static_cast<Spawner*>(GetChildByName({ "O-NeutralGunP1", "O-NeutralGunP2" }));
    m_upwardGun = static_cast<Spawner*>(GetChildByName({ "O-UpwardGunP1", "O-UpwardGunP2" }));
    m_downwardGun = static_cast<Spawner*>(GetChildByName({ "O-DownwardGunP1", "O-DownwardGunP2" }));
    m_superGun = static_cast<Spawner*>(GetChildByName({ "O-SuperGunP1", "O-SuperGunP2" }));

    // TODO: I'll probably need to think of a better way to do this at some point, since the names won't always be either "O-ShipP1" or "O-ShipP2".
    if (orxString_Compare(GetModelName(), "O-ShipP1") == 0)
    {
        m_enemyDirection = 0;
    }
    else
    {
        m_enemyDirection = orxMATH_KF_PI;
    }
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
    // Handle Waves
    if (m_wavesIndexNeutral != 0 && m_wavesIndexNeutral < m_numWavesNeutral)
    {
        if (m_waveDelayNeutral > 0)
        {
            m_waveDelayNeutral -= _rstInfo.fDT;
        }
        else
        {
            FireNeutral();
            m_wavesIndexNeutral++;
            m_waveDelayNeutral = m_maxWaveDelayNeutral;
        }
    }
    else
    {
        m_wavesIndexNeutral = 0;
        m_waveDelayNeutral = 0;
    }
    if (m_wavesIndexUpward != 0 && m_wavesIndexUpward < m_numWavesUpward)
    {
        if (m_waveDelayUpward > 0)
        {
            m_waveDelayUpward -= _rstInfo.fDT;
        }
        else
        {
            FireUpward();
            m_wavesIndexUpward++;
            m_waveDelayUpward = m_maxWaveDelayUpward;
        }
    }
    else
    {
        m_wavesIndexUpward = 0;
        m_waveDelayUpward = 0;
    }
    if (m_wavesIndexDownward != 0 && m_wavesIndexDownward < m_numWavesDownward)
    {
        if (m_waveDelayDownward > 0)
        {
            m_waveDelayDownward -= _rstInfo.fDT;
        }
        else
        {
            FireDownward();
            m_wavesIndexDownward++;
            m_waveDelayDownward = m_maxWaveDelayDownward;
        }
    }
    else
    {
        m_wavesIndexDownward = 0;
        m_waveDelayDownward = 0;
    }
    if (m_wavesIndexSuper != 0 && m_wavesIndexSuper < m_numWavesSuper)
    {
        if (m_waveDelaySuper > 0)
        {
            m_waveDelaySuper -= _rstInfo.fDT;
        }
        else
        {
            FireSuper();
            m_wavesIndexSuper++;
            m_waveDelaySuper = m_maxWaveDelaySuper;
        }
    }
    else
    {
        m_wavesIndexSuper = 0;
        m_waveDelaySuper = 0;
    }
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
        m_neutralMeter->SetScale({ m_defaultScaleNeutral.fX - (m_defaultScaleNeutral.fX * ((float)m_clipIndexNeutral / (float)m_clipSizeNeutral)), m_defaultScaleNeutral.fY, m_defaultScaleNeutral.fZ });
    }
    if (m_cooldownUpward > 0)
    {
        m_upwardMeter->SetScale({ m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * (m_cooldownUpward / m_maxCooldownUpward)), m_defaultScaleUpward.fY, m_defaultScaleUpward.fZ });
    }
    else
    {
        m_upwardMeter->SetScale({ m_defaultScaleUpward.fX - (m_defaultScaleUpward.fX * ((float)m_clipIndexUpward / (float)m_clipSizeUpward)), m_defaultScaleUpward.fY, m_defaultScaleUpward.fZ });
    }
    if (m_cooldownDownward > 0)
    {
        m_downwardMeter->SetScale({ m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * (m_cooldownDownward / m_maxCooldownDownward)), m_defaultScaleDownward.fY, m_defaultScaleDownward.fZ });
    }
    else
    {
        m_downwardMeter->SetScale({ m_defaultScaleDownward.fX - (m_defaultScaleDownward.fX * ((float)m_clipIndexDownward / (float)m_clipSizeDownward)), m_defaultScaleDownward.fY, m_defaultScaleDownward.fZ });
    }
    m_superMeter->SetScale({ m_defaultScaleSuper.fX - (m_defaultScaleSuper.fX * (m_cooldownSuper / m_maxCooldownSuper)), m_defaultScaleSuper.fY, m_defaultScaleSuper.fZ });
}

void Ship::Neutral()
{
    if (orxInput_HasBeenActivated("Neutral"))
    {
        if (m_cooldownNeutral <= 0 && m_wavesIndexNeutral == 0)
        {
            m_waveDelayNeutral = m_maxWaveDelayNeutral;

            m_clipIndexNeutral++;
            m_wavesIndexNeutral++;

            FireNeutral();

            if (m_clipIndexNeutral == m_clipSizeNeutral)
            {
                m_clipIndexNeutral = 0;
                m_cooldownNeutral = m_maxCooldownNeutral;
            }
        }
    }
}

void Ship::Upward()
{
    if (orxInput_HasBeenActivated("Upward"))
    {
        if (m_cooldownUpward <= 0 && m_wavesIndexUpward == 0)
        {
            m_waveDelayUpward = m_maxWaveDelayUpward;

            m_clipIndexUpward++;
            m_wavesIndexUpward++;

            FireUpward();

            if (m_clipIndexUpward == m_clipSizeUpward)
            {
                m_clipIndexUpward = 0;
                m_cooldownUpward = m_maxCooldownUpward;
            }
        }
    }
}

void Ship::Downward()
{
    if (orxInput_HasBeenActivated("Downward"))
    {
        if (m_cooldownDownward <= 0 && m_wavesIndexDownward == 0)
        {
            m_waveDelayDownward = m_maxWaveDelayDownward;

            m_clipIndexDownward++;
            m_wavesIndexDownward++;

            FireDownward();

            if (m_clipIndexDownward == m_clipSizeDownward)
            {
                m_clipIndexDownward = 0;
                m_cooldownDownward = m_maxCooldownDownward;
            }
        }
    }
}

void Ship::Super()
{
    if (orxInput_HasBeenActivated("Super"))
    {
        if (m_cooldownSuper <= 0 && m_wavesIndexSuper == 0)
        {
            m_wavesIndexSuper++;

            m_waveDelaySuper = m_maxWaveDelaySuper;

            m_cooldownSuper = m_maxCooldownSuper;

            FireSuper();

            m_cooldownSuper = m_maxCooldownSuper;
        }
    }
}

void Ship::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_neutralGun->Spawn(m_enemyDirection);
    }
}

void Ship::FireUpward()
{
    std::cout << cosf(m_enemyDirection) << std::endl;
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_upwardGun->Spawn(-orxMATH_KF_PI_BY_2 + (copysignf(1, cosf(m_enemyDirection)) * orxMATH_KF_PI_BY_4));
    }
}

void Ship::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_downwardGun->Spawn(orxMath_GetRandomFloat(orxMATH_KF_PI_BY_4 + orxMATH_KF_PI_BY_4 / 2.0, orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_4 / 2.0));
    }
}

void Ship::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        if (m_wavesIndexSuper % 2 == 0)
        {
            m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i);
        }
        else
        {
            m_superGun->Spawn((m_enemyDirection + orxMATH_KF_PI_BY_4) * i + (m_enemyDirection + orxMATH_KF_PI_BY_4) / 2);
        }
    }
}
