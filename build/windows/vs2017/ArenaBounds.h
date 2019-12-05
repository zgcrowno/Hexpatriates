#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "ArenaBound.h"

namespace hexpatriates
{
    /// <summary>Represents an arena in which two pilots battle.</summary>
    class ArenaBounds : public ScrollMod
    {
    protected:
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
    public:
        float m_electrificationTimeP1;
        float m_electrificationTimeP2;
        float m_emberTimeP1;
        float m_emberTimeP2;
        float m_maxElectrificationTime;
        float m_maxEmberTime;
        float m_emberCreationTimeP1;
        float m_emberCreationTimeP2;
        float m_emberCreationRate;
        ArenaBound *m_leftBound;
        ArenaBound *m_rightBound;
        ArenaBound *m_topBound;
        ArenaBound *m_bottomBound;

        void Electrify(const bool &_bP1);
        void RainEmbers(const bool &_bP1);
        void HandleElectrificationBehavior(float &_electrificationTime, const float &_fDT);
        void HandleEmberBehavior(float &_emberTime, float &_emberCreationTime, const float &_fDT, const char *_emberName);
    };
}
