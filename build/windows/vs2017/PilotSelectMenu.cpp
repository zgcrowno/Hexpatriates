#include "PilotSelectMenu.h"
#include "Arena.h"

using namespace hexpatriates;

void PilotSelectMenu::OnCreate()
{
    Menu::OnCreate();
}

void PilotSelectMenu::OnDelete()
{
    Menu::OnDelete();
}

orxBOOL PilotSelectMenu::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void PilotSelectMenu::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Handle menu/scene transitions
    if (orxString_Compare(m_nextMenu, "") != 0)
    {
        if (orxString_Compare(m_nextMenu, "O-Arena") == 0)
        {
            Arena *arena = static_cast<Arena*>(CreateObject("O-Arena"));
            arena->m_pilotP1 = (Pilot*)CreateObject("O-Pilot1P1");
            arena->m_pilotP1->m_zone = (Zone*)CreateObject("O-ZoneP1");
            arena->m_pilotP2 = (Pilot*)CreateObject("O-Pilot1P2");
            arena->m_pilotP2->m_zone = (Zone*)CreateObject("O-ZoneP2");
            arena->m_pilotP1->m_opposingPilot = arena->m_pilotP2;
            arena->m_pilotP2->m_opposingPilot = arena->m_pilotP1;

            // TODO: This will do for now, but I ought to manage this using the config, eventually.
            // Create and place the meter borders (and clip dividers)
            arena->CreateMeterBorders();

            Destroy();
        }
    }

    // Handle menu navigation inputs
    if (orxInput_HasBeenActivated("UpP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        if (m_selectedItemIndex >= m_menuItems.size() / 2)
        {
            m_selectedItemIndex -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndex += m_menuItems.size() / 2;
        }
        m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
    }
    else if (orxInput_HasBeenActivated("DownP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        if (m_selectedItemIndex >= m_menuItems.size() / 2)
        {
            m_selectedItemIndex -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndex += m_menuItems.size() / 2;
        }
        m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
    }
    else if (orxInput_HasBeenActivated("LeftP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        if (m_selectedItemIndex % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndex += (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndex--;
        }
        m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
    }
    else if (orxInput_HasBeenActivated("RightP1"))
    {
        m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        if ((m_selectedItemIndex + 1) % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndex -= (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndex++;
        }
        m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
    }

    // Handle selection inputs
    if (orxInput_HasBeenActivated("DownwardP1"))
    {
        m_nextMenu = "O-Arena";
    }
}
