#pragma once

#include "Hexpatriates.h"
#include "Pilot.h"
#include "Familiar.h"

namespace hexpatriates
{
    class Pilot6 : public Pilot
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
        virtual void Move(const orxCLOCK_INFO &_rstInfo, const bool &_bAllowVerticalMovement);
    public:
        int m_maxFamiliars;
        std::vector<Familiar*> m_familiars;
        /// <summary>Handles the actual spawning/firing of the Pilot's neutral attack.</summary>
        virtual void FireNeutral();
        /// <summary>Handles the actual spawning/firing of the Pilot's upward attack.</summary>
        virtual void FireUpward();
        /// <summary>Handles the actual spawning/firing of the Pilot's downward attack.</summary>
        virtual void FireDownward();
        /// <summary>Handles the actual spawning/firing of the Pilot's super attack.</summary>
        virtual void FireSuper();
        void FireFamiliar(const float _direction, const Familiar::Type _type);
        /// <summary>Spawns a Familiar, if m_ship is of the correct type to allow for it.</summary>
        void SpawnFamiliar();
    };
}
