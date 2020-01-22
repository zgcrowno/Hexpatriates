#pragma once

#include "Hexpatriates.h"
#include "MenuItemTransitional.h"

namespace hexpatriates
{
    class MenuItemPilot : public MenuItemTransitional
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
        bool m_bIsCommitted;

        virtual void Select(const bool _p1);
        virtual void Deselect(const bool _p1);
    };
}
