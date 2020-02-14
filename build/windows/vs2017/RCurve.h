#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "UBucket.h"
#include "Action.h"

namespace hexpatriates
{
    class RCurve : public virtual ScrollMod
    {
    private:
        int m_maxIndex;

        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete();
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);

        void AddBucket(UBucket *_bucket);
        void Sort();
        bool InBucket(int _i, int _index);
        // TODO: At some point, I may want to add a parameter that allows us to optimize our search (see Payload/ResponseCurve.GetBucketIndexByValue and page 314 of Behavior Mathematics for Game AI).
        int GetBucketIndexByValue(int _value);
    public:
        float m_calculationInterval;
        float m_calculationTime;
        std::vector<UBucket*> m_uBuckets;

        void RebuildEdges(int _iStartBucket);
        // returns a random Action associated with one of the UBucket objects in m_uBuckets.
        Action *SelectAction();
    };
}
