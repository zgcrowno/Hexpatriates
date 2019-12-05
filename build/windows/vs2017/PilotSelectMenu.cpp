#include "PilotSelectMenu.h"
#include "Arena.h"
#include "Pilot1.h"
#include "Pilot2.h"
#include "Pilot3.h"
#include "Pilot4.h"
#include "Pilot5.h"
#include "Pilot6.h"
#include "Pilot7.h"
#include "Pilot8.h"

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
            if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon1") == 0)
            {
                arena->m_pilotP1 = (Pilot1*)CreateObject("O-Pilot1P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon2") == 0)
            {
                arena->m_pilotP1 = (Pilot2*)CreateObject("O-Pilot2P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon3") == 0)
            {
                arena->m_pilotP1 = (Pilot3*)CreateObject("O-Pilot3P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon4") == 0)
            {
                arena->m_pilotP1 = (Pilot4*)CreateObject("O-Pilot4P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon5") == 0)
            {
                arena->m_pilotP1 = (Pilot5*)CreateObject("O-Pilot5P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon6") == 0)
            {
                arena->m_pilotP1 = (Pilot6*)CreateObject("O-Pilot6P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon7") == 0)
            {
                arena->m_pilotP1 = (Pilot7*)CreateObject("O-Pilot7P1");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName(), "O-PilotSelectIcon8") == 0)
            {
                arena->m_pilotP1 = (Pilot8*)CreateObject("O-Pilot8P1");
            }
            if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon1") == 0)
            {
                arena->m_pilotP2 = (Pilot1*)CreateObject("O-Pilot1P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon2") == 0)
            {
                arena->m_pilotP2 = (Pilot2*)CreateObject("O-Pilot2P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon3") == 0)
            {
                arena->m_pilotP2 = (Pilot3*)CreateObject("O-Pilot3P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon4") == 0)
            {
                arena->m_pilotP2 = (Pilot4*)CreateObject("O-Pilot4P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon5") == 0)
            {
                arena->m_pilotP2 = (Pilot5*)CreateObject("O-Pilot5P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon6") == 0)
            {
                arena->m_pilotP2 = (Pilot6*)CreateObject("O-Pilot6P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon7") == 0)
            {
                arena->m_pilotP2 = (Pilot7*)CreateObject("O-Pilot7P2");
            }
            else if (orxString_Compare(m_menuItems.at(m_selectedItemIndexP2)->GetModelName(), "O-PilotSelectIcon8") == 0)
            {
                arena->m_pilotP2 = (Pilot8*)CreateObject("O-Pilot8P2");
            }
            // Else if player 2 hasn't chosen anyone
            else
            {
                arena->m_pilotP2 = (Pilot*)CreateObject("O-Pilot1P2");
            }
            arena->m_pilotP1->m_zone = (Zone*)CreateObject("O-ZoneP1");
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
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        }
        if (m_selectedItemIndex >= m_menuItems.size() / 2)
        {
            m_selectedItemIndex -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndex += m_menuItems.size() / 2;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
        }
    }
    else if (orxInput_HasBeenActivated("DownP1"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        }
        if (m_selectedItemIndex >= m_menuItems.size() / 2)
        {
            m_selectedItemIndex -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndex += m_menuItems.size() / 2;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
        }
    }
    else if (orxInput_HasBeenActivated("LeftP1"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        }
        if (m_selectedItemIndex % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndex += (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndex--;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
        }
    }
    else if (orxInput_HasBeenActivated("RightP1"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP1");
        }
        if ((m_selectedItemIndex + 1) % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndex -= (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndex++;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndex)->RemoveShader("SH-OutlineP2");
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndex)->AddShader("SH-OutlineP1");
        }
    }
    if (orxInput_HasBeenActivated("UpP2"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP2");
        }
        if (m_selectedItemIndexP2 >= m_menuItems.size() / 2)
        {
            m_selectedItemIndexP2 -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndexP2 += m_menuItems.size() / 2;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP2");
        }
    }
    else if (orxInput_HasBeenActivated("DownP2"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP2");
        }
        if (m_selectedItemIndexP2 >= m_menuItems.size() / 2)
        {
            m_selectedItemIndexP2 -= m_menuItems.size() / 2;
        }
        else
        {
            m_selectedItemIndexP2 += m_menuItems.size() / 2;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP2");
        }
    }
    else if (orxInput_HasBeenActivated("LeftP2"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP2");
        }
        if (m_selectedItemIndexP2 % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndexP2 += (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndexP2--;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP2");
        }
    }
    else if (orxInput_HasBeenActivated("RightP2"))
    {
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1AndP2");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP2");
        }
        if ((m_selectedItemIndexP2 + 1) % (m_menuItems.size() / 2) == 0)
        {
            m_selectedItemIndexP2 -= (m_menuItems.size() / 2) - 1;
        }
        else
        {
            m_selectedItemIndexP2++;
        }
        if (m_selectedItemIndex == m_selectedItemIndexP2)
        {
            m_menuItems.at(m_selectedItemIndexP2)->RemoveShader("SH-OutlineP1");
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP1AndP2");
        }
        else
        {
            m_menuItems.at(m_selectedItemIndexP2)->AddShader("SH-OutlineP2");
        }
    }

    // Handle selection inputs
    if (orxInput_HasBeenActivated("DownwardP1"))
    {
        m_nextMenu = "O-Arena";
    }
}
