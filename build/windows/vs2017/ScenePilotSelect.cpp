#include "ScenePilotSelect.h"
#include "SceneArena.h"
#include "Pilot1.h"
#include "Pilot2.h"
#include "Pilot3.h"
#include "Pilot4.h"
#include "Pilot5.h"
#include "Pilot6.h"
#include "Pilot7.h"
#include "Pilot8.h"
#include <string>

using namespace hexpatriates;

void ScenePilotSelect::OnCreate()
{
    SceneMenu::OnCreate();
}

void ScenePilotSelect::OnDelete()
{
    SceneMenu::OnDelete();
}

orxBOOL ScenePilotSelect::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void ScenePilotSelect::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Handle menu/scene transitions
    if (orxString_Compare(m_transition.c_str(), "") != 0)
    {
        if (orxString_Compare(m_transition.c_str(), "O-ToSceneArena") == 0)
        {
            std::string pilotBaseName = "O-Pilot";
            std::string p1 = "P1";
            std::string p2 = "P2";
            std::string pilotP1FullName = pilotBaseName + std::to_string(m_selectedItemIndex + 1) + p1;                       
            std::string pilotP2FullName = pilotBaseName + std::to_string(m_selectedItemIndexP2 + 1) + p2;
            SetString("PilotP1", pilotP1FullName.c_str(), "O-SceneArena");
            SetString("PilotP2", pilotP2FullName.c_str(), "O-SceneArena");
        }

        CreateObject(m_transition);
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
        m_transition = "O-ToSceneArena";
    }
    else if (orxInput_HasBeenActivated("SuperP1"))
    {
        m_transition = "O-ToSceneMain";
    }
}
