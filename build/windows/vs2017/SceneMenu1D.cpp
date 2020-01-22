#include "SceneMenu1D.h"

using namespace hexpatriates;

void SceneMenu1D::OnCreate()
{
    SceneMenu::OnCreate();
}

void SceneMenu1D::OnDelete()
{
    SceneMenu::OnDelete();
}

orxBOOL SceneMenu1D::OnCollide(
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

void SceneMenu1D::Update(const orxCLOCK_INFO &_rstInfo)
{
    SceneMenu::Update(_rstInfo);

    // Handle menu navigation inputs.
    if (orxInput_HasBeenActivated("UpP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->Deselect(true);
        if (m_selectedItemIndex == 0)
        {
            m_selectedItemIndex = m_menuItems.size() - 1;
        }
        else
        {
            m_selectedItemIndex--;
        }
        m_menuItems.at(m_selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated("DownP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->Deselect(true);
        if (m_selectedItemIndex == m_menuItems.size() - 1)
        {
            m_selectedItemIndex = 0;
        }
        else
        {
            m_selectedItemIndex++;
        }
        m_menuItems.at(m_selectedItemIndex)->Select(true);
    }
}
