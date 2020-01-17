#include "ScenePause.h"
#include "AudioManager.h"
#include "SceneArena.h"
#include "SceneMenu.h"

using namespace hexpatriates;

void ScenePause::OnCreate()
{
    SceneMenu::OnCreate();
}

void ScenePause::OnDelete()
{
    SceneMenu::OnDelete();
}

orxBOOL ScenePause::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void ScenePause::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Handle menu/scene transitions
    if (orxString_Compare(m_transition.c_str(), "") != 0)
    {
        CreateObject(m_transition);
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
        Hexpatriates::GetInstance().PauseGame(false);

        if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName().c_str(), "O-ContinueText") == 0)
        {
            for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
            {
                SceneArena *arena = dynamic_cast<SceneArena*>(child);
                if (arena != nullptr)
                {
                    m_transition = "O-ToSceneArenaFromPause";
                    // Ensure that menu music is stopped upon exiting from pause menu into arena.
                    orxSound_Stop(AudioManager::GetInstance()->m_menuMusic);
                    orxSound_SetTime(AudioManager::GetInstance()->m_menuMusic, 0);
                    // Re-activate arena's music.
                    orxSound_Play(arena->m_pilotP1Music);
                    orxSound_Play(arena->m_pilotP2Music);
                    break;
                }
            }
        }
        else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName().c_str(), "O-RestartMatchText") == 0)
        {
            m_transition = "O-ToSceneArena";
            // Ensure that menu music is stopped upon exiting from pause menu into arena.
            orxSound_Stop(AudioManager::GetInstance()->m_menuMusic);
            orxSound_SetTime(AudioManager::GetInstance()->m_menuMusic, 0);
            // Reset arena music
            SceneArena *arena = dynamic_cast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
            orxSound_Stop(arena->m_pilotP1Music);
            orxSound_SetTime(arena->m_pilotP1Music, 0);
            orxSound_Stop(arena->m_pilotP2Music);
            orxSound_SetTime(arena->m_pilotP2Music, 0);
        }
        else if (orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName().c_str(), "O-ExitText") == 0)
        {
            m_transition = "O-ToSceneMain";
            // Reset arena music
            SceneArena *arena = dynamic_cast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
            orxSound_Stop(arena->m_pilotP1Music);
            orxSound_SetTime(arena->m_pilotP1Music, 0);
            orxSound_Stop(arena->m_pilotP2Music);
            orxSound_SetTime(arena->m_pilotP2Music, 0);
        }
        else // orxString_Compare(m_menuItems.at(m_selectedItemIndex)->GetModelName().c_str(), "O-QuitText") == 0
        {
            exit(orxSTATUS_SUCCESS);
        }
    }
}
