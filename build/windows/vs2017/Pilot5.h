#pragma once

#include "Hexpatriates.h"
#include "Pilot.h"

namespace hexpatriates
{
    class Pilot5 : public Pilot
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
        virtual void ExecuteMovement();
        //! Returns a bool which represents whether or not the Pilot can move vertically
        virtual bool CanMoveVertically();
    public:
        enum Stance
        {
            Airborne,
            Grounded
        };

        bool m_bIsShipPounding;
        float m_shipPoundSpeed;
        Stance m_stance;

        /// <summary>Handles the actual spawning/firing of the Pilot's neutral attack.</summary>
        virtual void FireNeutral(int &_indexInWave);
        /// <summary>Handles the actual spawning/firing of the Pilot's upward attack.</summary>
        virtual void FireUpward(int &_indexInWave);
        /// <summary>Handles the actual spawning/firing of the Pilot's downward attack.</summary>
        virtual void FireDownward(int &_indexInWave);
        /// <summary>Handles the actual spawning/firing of the Pilot's super attack.</summary>
        virtual void FireSuper(int &_indexInWave);
        void SwitchStance();
        void ShipPoundShockwave(const orxVECTOR &_shockwavePosition);
    };
}
