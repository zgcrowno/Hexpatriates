#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"

namespace hexpatriates
{
    /// <summary>Represents a vessel which is operated by a Pilot.</summary>
    class Ship : public ScrollMod
    {
    private:
        orxVECTOR m_defaultScaleNeutral;
        orxVECTOR m_defaultScaleUpward;
        orxVECTOR m_defaultScaleDownward;
        orxVECTOR m_defaultScaleSuper;
        ScrollMod *m_neutralMeter;
        ScrollMod *m_upwardMeter;
        ScrollMod *m_downwardMeter;
        ScrollMod *m_superMeter;

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
        int m_maxNeutral;
        int m_usedNeutral;
        float m_maxCooldownNeutral;
        float m_cooldownNeutral;
        int m_maxUpward;
        int m_usedUpward;
        float m_maxCooldownUpward;
        float m_cooldownUpward;
        int m_maxDownward;
        int m_usedDownward;
        float m_maxCooldownDownward;
        float m_cooldownDownward;
        float m_maxCooldownSuper;
        float m_cooldownSuper;
        ScrollMod *m_neutralGun;
        ScrollMod *m_upwardGun;
        ScrollMod *m_downwardGun;
        ScrollMod *m_superGun;

        /// <summary>Executes the Ship's neutral attack.</summary>
        void Neutral();
        /// <summary>Executes the Ship's upward attack.</summary>
        void Upward();
        /// <summary>Executes the Ship's downward attack.</summary>
        void Downward();
        /// <summary>Executes the Ship's super attack.</summary>
        void Super();
    };
}
