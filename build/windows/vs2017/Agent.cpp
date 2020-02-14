#include "Agent.h"

using namespace hexpatriates;

void Agent::OnCreate()
{
    //CalculateUtilities(this);
    CalculateUtilities();
    SetActionMap();
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
    //orxThread_RunTask(&CalculateUtilities, nullptr, nullptr, this);
    Act();
}

void Agent::SetActionMap()
{

}

void Agent::SetContext(Context *_context)
{
    m_context = _context;
}

//orxSTATUS orxFASTCALL Agent::CalculateUtilities(void *_context)
//{
//    Agent *agent = static_cast<Agent*>(_context);
//    for (RCurve *rCurve : agent->m_context->m_rCurves)
//    {
//        for (UBucket *uBucket : rCurve->m_uBuckets)
//        {
//            // Set size (and edge?) based upon value returned from m_action->Score().
//            int actionScore = agent->ScoreAction(uBucket->m_action);
//
//            if (actionScore <= 0)
//            {
//                uBucket->m_size = 1;
//            }
//            else
//            {
//                uBucket->m_size = actionScore;
//            }
//        }
//
//        rCurve->RebuildEdges(0);
//    }
//
//    return orxSTATUS_SUCCESS;
//}

void Agent::CalculateUtilities()
{
    for (RCurve *rCurve : m_context->m_rCurves)
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

void Agent::CalculateUtility(RCurve *_rCurve)
{
    for (UBucket *uBucket : _rCurve->m_uBuckets)
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

    _rCurve->RebuildEdges(0);
}

void Agent::Act()
{
    for (RCurve *rCurve : m_context->m_rCurves)
    {
        if (rCurve->m_calculationTime <= 0)
        {
            CalculateUtility(rCurve);
            m_actionMap.at(rCurve->SelectAction()->m_actionType)();
            rCurve->m_calculationTime = rCurve->m_calculationInterval;
        }
    }
}

int Agent::ScoreAction(Action *_action)
{
    return 0;
}
