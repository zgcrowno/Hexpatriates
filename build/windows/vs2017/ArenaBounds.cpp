#include "ArenaBounds.h"
#include "Ember.h"

using namespace hexpatriates;

void ArenaBounds::OnCreate()
{
    m_maxElectrificationTime = GetFloat("MaxElectrificationTime", GetModelName());
    m_maxEmberTime = GetFloat("MaxEmberTime", GetModelName());
    m_emberCreationRate = GetFloat("EmberCreationRate", GetModelName());
    m_leftBound = static_cast<ArenaBound*>(GetChildByName("O-WallLeftWall"));
    m_rightBound = static_cast<ArenaBound*>(GetChildByName("O-WallRightWall"));
    m_topBound = static_cast<ArenaBound*>(GetChildByName("O-WallCeiling"));
    m_bottomBound = static_cast<ArenaBound*>(GetChildByName("O-WallFloor"));
}

void ArenaBounds::OnDelete()
{

}

orxBOOL ArenaBounds::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void ArenaBounds::Update(const orxCLOCK_INFO &_rstInfo)
{
    HandleElectrificationBehavior(m_electrificationTimeP1, _rstInfo.fDT);
    HandleElectrificationBehavior(m_electrificationTimeP2, _rstInfo.fDT);
    HandleEmberBehavior(m_emberTimeP1, m_emberCreationTimeP1, _rstInfo.fDT, "O-EmberP1");
    HandleEmberBehavior(m_emberTimeP2, m_emberCreationTimeP2, _rstInfo.fDT, "O-EmberP2");
}

void ArenaBounds::Electrify(const bool &_bP1)
{
    if (_bP1)
    {
        m_electrificationTimeP1 = m_maxElectrificationTime;
        m_leftBound->m_electricityIconP1->Enable(true);
        m_rightBound->m_electricityIconP1->Enable(true);
        m_topBound->m_electricityIconP1->Enable(true);
        m_bottomBound->m_electricityIconP1->Enable(true);
    }
    else
    {
        m_electrificationTimeP2 = m_maxElectrificationTime;
        m_leftBound->m_electricityIconP2->Enable(true);
        m_rightBound->m_electricityIconP2->Enable(true);
        m_topBound->m_electricityIconP2->Enable(true);
        m_bottomBound->m_electricityIconP2->Enable(true);
    }
}

void ArenaBounds::RainEmbers(const bool &_bP1)
{
    if (_bP1)
    {
        m_emberTimeP1 = m_maxEmberTime;
        m_emberCreationTimeP1 = m_emberCreationRate;
    }
    else
    {
        m_emberTimeP2 = m_maxEmberTime;
        m_emberCreationTimeP2 = m_emberCreationRate;
    }
}

void ArenaBounds::HandleElectrificationBehavior(float &_electrificationTime, const float &_fDT)
{
    if (_electrificationTime > 0)
    {
        _electrificationTime -= _fDT;
    }
    else
    {
        _electrificationTime = 0;

        if (_electrificationTime == m_electrificationTimeP1)
        {
            m_leftBound->m_electricityIconP1->Enable(false);
            m_rightBound->m_electricityIconP1->Enable(false);
            m_topBound->m_electricityIconP1->Enable(false);
            m_bottomBound->m_electricityIconP1->Enable(false);
        }
        else
        {
            m_leftBound->m_electricityIconP2->Enable(false);
            m_rightBound->m_electricityIconP2->Enable(false);
            m_topBound->m_electricityIconP2->Enable(false);
            m_bottomBound->m_electricityIconP2->Enable(false);
        }
    }
}

void ArenaBounds::HandleEmberBehavior(float &_emberTime, float &_emberCreationTime, const float &_fDT, const char *_emberName)
{
    if (_emberTime > 0)
    {
        _emberTime -= _fDT;
        _emberCreationTime -= _fDT;

        if (_emberCreationTime <= 0)
        {
            float ceilingLeftExtent = m_topBound->GetPosition().fX - m_topBound->GetScaledSize().fX;
            float ceilingRightExtent = m_topBound->GetPosition().fX + m_topBound->GetScaledSize().fX;
            Ember *ember = static_cast<Ember*>(CreateObject(_emberName));
            ember->SetPosition({ orxMath_GetRandomFloat(ceilingLeftExtent, ceilingRightExtent), m_topBound->GetPosition().fY });
            _emberCreationTime = m_emberCreationRate;
        }
    }
    else
    {
        _emberTime = 0;
        _emberCreationTime = 0;
    }
}
