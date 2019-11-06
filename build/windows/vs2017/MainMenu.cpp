#include "MainMenu.h"

using namespace hexpatriates;

void MainMenu::OnCreate()
{
    Menu::OnCreate();
}

void MainMenu::OnDelete()
{
    Menu::OnDelete();
}

orxBOOL MainMenu::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void MainMenu::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Handle menu/scene transitions
    if (orxString_Compare(m_nextMenu, "") != 0)
    {
        CreateObject(m_nextMenu);
        Destroy();
    }

    // Handle menu navigation inputs
    if (orxInput_HasBeenActivated("UpP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineText");
        if (m_selectedItemIndex == 0)
        {
            m_selectedItemIndex = m_menuItems.size() - 1;
        }
        else
        {
            m_selectedItemIndex--;
        }
        m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineText");
    }
    else if (orxInput_HasBeenActivated("DownP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineText");
        if (m_selectedItemIndex == m_menuItems.size() - 1)
        {
            m_selectedItemIndex = 0;
        }
        else
        {
            m_selectedItemIndex++;
        }
        m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineText");
    }

    // Handle selection inputs
    if (orxInput_HasBeenActivated("DownwardP1"))
    {
        if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-ArcadeText") == 0)
        {

        }
        else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-VersusText") == 0)
        {
            m_nextMenu = "O-PilotSelectMenu";
        }
    }
}
