#pragma once

#include "Hexpatriates.h"
#include "Parryable.h"

namespace hexpatriates
{
    class Legionnaire : public Parryable
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
        bool m_bDecelerate;
        float m_minFSpeed;
        float m_fSpeedDecrement;

        virtual void ParriedBehavior();
    };
}
