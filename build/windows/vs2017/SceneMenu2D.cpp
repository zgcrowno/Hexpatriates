#include "SceneMenu2D.h"

using namespace hexpatriates;

void SceneMenu2D::OnCreate()
{
    SceneMenu::OnCreate();
}

void SceneMenu2D::OnDelete()
{
    SceneMenu::OnDelete();
}

orxBOOL SceneMenu2D::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    SceneMenu::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void SceneMenu2D::Update(const orxCLOCK_INFO &_rstInfo)
{
    SceneMenu::Update(_rstInfo);

    // Handle menu navigation inputs
    if (orxInput_HasBeenActivated("UpP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->Deselect(true);
        if (m_selectedItemIndex >= m_menuItems.size() / 2)
        {
            m_selectedItemIndex -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndex += m_menuItems.size() / 2;
        }
        m_menuItems.at(m_selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated("DownP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->Deselect(true);
        if (m_selectedItemIndex >= m_menuItems.size() / 2)
        {
            m_selectedItemIndex -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndex += m_menuItems.size() / 2;
        }
        m_menuItems.at(m_selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated("LeftP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->Deselect(true);
        if (m_selectedItemIndex % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndex += (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndex--;
        }
        m_menuItems.at(m_selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated("RightP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->Deselect(true);
        if ((m_selectedItemIndex + 1) % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndex -= (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndex++;
        }
        m_menuItems.at(m_selectedItemIndex)->Select(true);
    }
    if (orxInput_HasBeenActivated("UpP2"))
    {
        m_menuItems.at(m_selectedItemIndexP2)->Deselect(false);
        if (m_selectedItemIndexP2 >= m_menuItems.size() / 2)
        {
            m_selectedItemIndexP2 -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndexP2 += m_menuItems.size() / 2;
        }
        m_menuItems.at(m_selectedItemIndexP2)->Select(false);
    }
    else if (orxInput_HasBeenActivated("DownP2"))
    {
        m_menuItems.at(m_selectedItemIndexP2)->Deselect(false);
        if (m_selectedItemIndexP2 >= m_menuItems.size() / 2)
        {
            m_selectedItemIndexP2 -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndexP2 += m_menuItems.size() / 2;
        }
        m_menuItems.at(m_selectedItemIndexP2)->Select(false);
    }
    else if (orxInput_HasBeenActivated("LeftP2"))
    {
        m_menuItems.at(m_selectedItemIndexP2)->Deselect(false);
        if (m_selectedItemIndexP2 % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndexP2 += (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndexP2--;
        }
        m_menuItems.at(m_selectedItemIndexP2)->Select(false);
    }
    else if (orxInput_HasBeenActivated("RightP2"))
    {
        m_menuItems.at(m_selectedItemIndexP2)->Deselect(false);
        if ((m_selectedItemIndexP2 + 1) % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndexP2 -= (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndexP2++;
        }
        m_menuItems.at(m_selectedItemIndexP2)->Select(false);
    }
}
