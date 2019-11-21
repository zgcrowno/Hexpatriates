#include "Ship.h"

using namespace hexpatriates;

void Ship::OnCreate()
{
    m_clipSizeNeutral = GetFloat("ClipSizeNeutral", GetModelName());
    m_clipSizeUpward = GetFloat("ClipSizeUpward", GetModelName());
    m_clipSizeDownward = GetFloat("ClipSizeDownward", GetModelName());
    m_waveSizeNeutral = GetFloat("WaveSizeNeutral", GetModelName());
    m_waveSizeUpward = GetFloat("WaveSizeUpward", GetModelName());
    m_waveSizeDownward = GetFloat("WaveSizeDownward", GetModelName());
    m_waveSizeSuper = GetFloat("WaveSizeSuper", GetModelName());
    m_numWavesNeutral = GetFloat("NumWavesNeutral", GetModelName());
    m_numWavesUpward = GetFloat("NumWavesUpward", GetModelName());
    m_numWavesDownward = GetFloat("NumWavesDownward", GetModelName());
    m_numWavesSuper = GetFloat("NumWavesSuper", GetModelName());
    m_maxCooldownNeutral = GetFloat("MaxCooldownNeutral", GetModelName());
    m_maxCooldownUpward = GetFloat("MaxCooldownUpward", GetModelName());
    m_maxCooldownDownward = GetFloat("MaxCooldownDownward", GetModelName());
    m_maxCooldownSuper = GetFloat("MaxCooldownSuper", GetModelName());
    m_maxWaveDelayNeutral = GetFloat("MaxWaveDelayNeutral", GetModelName());
    m_maxWaveDelayUpward = GetFloat("MaxWaveDelayUpward", GetModelName());
    m_maxWaveDelayDownward = GetFloat("MaxWaveDelayDownward", GetModelName());
    m_maxWaveDelaySuper = GetFloat("MaxWaveDelaySuper", GetModelName());
    m_cooldownSuper = m_maxCooldownSuper;

    int typeLength = strlen("1P1");
    orxCHAR gunTypeText[512] = "O-NeutralGun";
    orxCHAR shipTypeText[512];
    ScrollMod::Substring(GetModelName(), shipTypeText, strlen(GetModelName()) - typeLength, typeLength);
    m_neutralGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
    strcpy(gunTypeText, "O-UpwardGun");
    m_upwardGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
    strcpy(gunTypeText, "O-DownwardGun");
    m_downwardGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));
    strcpy(gunTypeText, "O-SuperGun");
    m_superGun = static_cast<Spawner*>(GetChildByName(strcat(gunTypeText, shipTypeText)));

    if (orxString_SearchString(GetModelName(), "P1") != orxNULL)
    {
        m_neutralInput = "NeutralP1";
        m_upwardInput = "UpwardP1";
        m_downwardInput = "DownwardP1";
        m_superInput = "SuperP1";
        m_enemyDirection = 0;
    }
    else
    {
        m_neutralInput = "NeutralP2";
        m_upwardInput = "UpwardP2";
        m_downwardInput = "DownwardP2";
        m_superInput = "SuperP2";
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
}

void Ship::Neutral()
{
    if (orxInput_HasBeenActivated(m_neutralInput))
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
    if (orxInput_HasBeenActivated(m_upwardInput))
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
    if (orxInput_HasBeenActivated(m_downwardInput))
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
    if (orxInput_HasBeenActivated(m_superInput))
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
