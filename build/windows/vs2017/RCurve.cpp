#include "RCurve.h"
#include <algorithm>

using namespace hexpatriates;

void RCurve::OnCreate()
{
    for (UBucket *uBucket = ScrollCast<UBucket*>(GetOwnedChild()); uBucket; uBucket = ScrollCast<UBucket*>(uBucket->GetOwnedSibling()))
    {
        m_uBuckets.push_back(uBucket);
    }
}

void RCurve::OnDelete()
{

}

orxBOOL RCurve::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void RCurve::Update(const orxCLOCK_INFO &_rstInfo)
{

}

void RCurve::AddBucket(UBucket *_bucket)
{
    m_maxIndex += _bucket->m_size;

    m_uBuckets.push_back(_bucket);
    Sort();
}

void RCurve::RebuildEdges(int _iStartBucket)
{
    int uBucketCount = m_uBuckets.size();
    Sort();
    for (int i = _iStartBucket; i < uBucketCount; i++)
    {
        UBucket *uBucket = m_uBuckets.at(i);
        if (i > 0)
        {
            uBucket->m_edge = m_uBuckets.at(i - 1)->m_edge + uBucket->m_size;
        }
        else
        {
            uBucket->m_edge = uBucket->m_size;
        }
    }
    m_maxIndex = m_uBuckets.at(uBucketCount - 1)->m_edge;
}

void RCurve::Sort()
{
    std::sort(
        m_uBuckets.begin(),
        m_uBuckets.end(),
        [](UBucket *first, UBucket *second)
        {
            return first->m_size > second->m_size;
        });
}

bool RCurve::InBucket(int _i, int _index)
{
    if (_i == 0 && _index <= m_uBuckets.at(_i)->m_edge)
    {
        return true;
    }

    if (_index <= m_uBuckets.at(_i)->m_edge && _index > m_uBuckets.at(_i - 1)->m_edge)
    {
        return true;
    }
    
    return false;
}

int RCurve::GetBucketIndexByValue(int _value)
{
    int iHigh = m_uBuckets.size() - 1;
    int iLow = 0;
    int iGuess;

    while (true)
    {
        iGuess = iLow + ((iHigh - iLow) / 2);
        
        if (InBucket(iGuess, _value))
        {
            return iGuess;
        }

        if (_value > m_uBuckets.at(iGuess)->m_edge)
        {
            if (iLow == iGuess)
            {
                // Since C++ truncates integer divisions, we have to account for the situation in which iGuess and iLow are equal to one another, both being one index below the target.
                iLow++;
            }
            else
            {
                iLow = iGuess;
            }
        }
        else
        {
            iHigh = iGuess;
        }
    }

    return 0; //Returning a default value of 0
}

Action *RCurve::SelectAction()
{
    int index = orxMath_GetRandomU32(0, m_maxIndex);
    return m_uBuckets.at(GetBucketIndexByValue(index))->m_action;
}
