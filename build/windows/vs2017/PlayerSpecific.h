#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"

namespace hexpatriates
{
    class PlayerSpecific : public virtual ScrollMod
    {
    protected:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete() = 0;
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal) = 0;
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo) = 0;
    public:
        bool m_bIsP1;
        std::string m_genericName;
        std::string m_typeName;
        std::string m_otherTypeName;
    };
}
