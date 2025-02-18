#pragma once

#include "Hexpatriates.h"
#include "MenuItem.h"

namespace hexpatriates
{
    class MenuItemTransitional : public MenuItem
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
        std::string m_toScene;

        virtual void Select(const bool _p1);
        virtual void Deselect(const bool _p1);
        virtual void HandleInput(const std::string &_playerType);
        void Transition();
    };
}
