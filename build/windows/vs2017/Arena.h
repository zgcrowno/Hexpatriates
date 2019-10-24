#pragma once

#include "Hexpatriates.h"
#include "Pilot.h"
#include "ScrollMod.h"

namespace hexpatriates
{
    /// <summary>Represents an arena in which two pilots battle.</summary>
    class Arena : public ScrollMod
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
        Pilot *m_pilotP1;
        Pilot *m_pilotP2;
        ScrollMod *m_dashMeterP1;
        ScrollMod *m_parryMeterP1;
        ScrollMod *m_livesMeterP1;
        ScrollMod *m_neutralMeterP1;
        ScrollMod *m_upwardMeterP1;
        ScrollMod *m_downwardMeterP1;
        ScrollMod *m_superMeterP1;
        ScrollMod *m_dashMeterP2;
        ScrollMod *m_parryMeterP2;
        ScrollMod *m_livesMeterP2;
        ScrollMod *m_neutralMeterP2;
        ScrollMod *m_upwardMeterP2;
        ScrollMod *m_downwardMeterP2;
        ScrollMod *m_superMeterP2;
        //! Associated UI elements' default scales
        // TODO: At least for these default scales, I should probably put together a UI manager to handle data like this. OR, make fully fleshed out classes for these UI elements.
        orxVECTOR m_defaultScaleDash;
        orxVECTOR m_defaultScaleParry;
        orxVECTOR m_defaultScaleLives;
        orxVECTOR m_defaultScaleNeutral;
        orxVECTOR m_defaultScaleUpward;
        orxVECTOR m_defaultScaleDownward;
        orxVECTOR m_defaultScaleSuper;
    };
}
