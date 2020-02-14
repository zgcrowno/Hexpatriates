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
        virtual void ExecuteMovement();
    public:
        int m_maxFamiliars;
        std::vector<Familiar*> m_familiars;
        /// <summary>Destroy's the Pilot's ship.</summary>
        virtual void DestroyShip();
        /// <summary>Handles the actual spawning/firing of the Pilot's neutral attack.</summary>
        virtual void FireNeutral(int &_indexInWave);
        /// <summary>Handles the actual spawning/firing of the Pilot's upward attack.</summary>
        virtual void FireUpward(int &_indexInWave);
        /// <summary>Handles the actual spawning/firing of the Pilot's downward attack.</summary>
        virtual void FireDownward(int &_indexInWave);
        /// <summary>Handles the actual spawning/firing of the Pilot's super attack.</summary>
        virtual void FireSuper(int &_indexInWave);
        void FireFamiliar(const float _direction, const Familiar::Type _type);
        /// <summary>Spawns a Familiar, if m_ship is of the correct type to allow for it.</summary>
        void SpawnFamiliar();
        /// <summary>Returns the Pilot's familiar (if any) which has been fired, but not yet detonated, and which is still in mid-flight.</summary>
        Familiar *SuperInPlay();
        virtual void HandleSuperCooldown(const float &_fDT);
    };
}
