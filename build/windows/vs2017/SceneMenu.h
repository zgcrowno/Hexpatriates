#pragma once

#include "Hexpatriates.h"
#include "MenuItem.h"
#include "Scene.h"
#include <vector>

namespace hexpatriates
{
    class SceneMenu : public Scene, public InputHandler
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
        int m_selectedItemIndex;
        int m_selectedItemIndexP2;
        // How many columns of menu items the scene contains.
        int m_menuItemsWidth;
        // How many rows of menu items the scene contains.
        int m_menuItemsHeight;
        std::vector<MenuItem*> m_menuItems;

        void HandleInput(const std::string &_playerType);
    };
}
