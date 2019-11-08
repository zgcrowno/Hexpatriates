#pragma once

#include "Hexpatriates.h"
#include "Ship.h"

namespace hexpatriates
{
    /// <summary>Represents a vessel which is operated by a Pilot.</summary>
    class Ship5 : public Ship
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
        /// <summary>Handles the actual spawning/firing of the Ship's neutral attack.</summary>
        virtual void FireNeutral();
        /// <summary>Handles the actual spawning/firing of the Ship's upward attack.</summary>
        virtual void FireUpward();
        /// <summary>Handles the actual spawning/firing of the Ship's downward attack.</summary>
        virtual void FireDownward();
        /// <summary>Handles the actual spawning/firing of the Ship's super attack.</summary>
        virtual void FireSuper();
    };
}
