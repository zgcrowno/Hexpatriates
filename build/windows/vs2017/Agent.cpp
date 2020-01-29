#include "Agent.h"

using namespace hexpatriates;

void Agent::OnCreate()
{
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        RCurve *rCurve = dynamic_cast<RCurve*>(child);
        if (rCurve != nullptr)
        {
            m_rCurves.push_back(rCurve);
        }
    }
    CalculateUtilities();
}

void Agent::OnDelete()
{

}

orxBOOL Agent::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void Agent::Update(const orxCLOCK_INFO &_rstInfo)
{
    CalculateUtilities();
    Act();
}

void Agent::SetActionMap()
{

}

void Agent::CalculateUtilities()
{
    for (RCurve *rCurve : m_rCurves)
    {
        for (UBucket *uBucket : rCurve->m_uBuckets)
        {
            // Set size (and edge?) based upon value returned from m_action->Score().
            int actionScore = ScoreAction(uBucket->m_action);

            if (actionScore <= 0)
            {
                uBucket->m_size = 1;
            }
            else
            {
                uBucket->m_size = actionScore;
            }
        }

        rCurve->RebuildEdges(0);
    }
}

void Agent::Act()
{
    for (RCurve *rCurve : m_rCurves)
    {
        m_actionMap.at(rCurve->SelectAction()->m_actionType)();
    }
}

int Agent::ScoreAction(Action *_action)
{
    int retVal = 0;

    switch (_action->m_actionType)
    {
    case Action::ActionType::Move:
        retVal = 1;
        break;
    case Action::ActionType::Jump:
        retVal = 1;
        break;
    case Action::ActionType::Fall:
        retVal = 1;
        break;
    case Action::ActionType::Dash:
        retVal = 1;
        break;
    case Action::ActionType::Parry:
        retVal = 1;
        break;
    case Action::ActionType::Melee:
        retVal = 1;
        break;
    case Action::ActionType::Downstab:
        retVal = 1;
        break;
    case Action::ActionType::FireNeutral:
        retVal = 1;
        break;
    case Action::ActionType::FireUpward:
        retVal = 1;
        break;
    case Action::ActionType::FireDownward:
        retVal = 1;
        break;
    case Action::ActionType::FireSuper:
        retVal = 1;
        break;
    }

    return retVal;
}
