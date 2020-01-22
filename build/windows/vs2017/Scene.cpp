#include "Scene.h"
#include "SceneArena.h"
#include "SceneMenu2D.h"
#include "AudioManager.h"
#include <string>

using namespace hexpatriates;

std::map<std::string, std::function<void()>> Scene::m_transitionBehaviorMap =
{
    {
        "O-ToSceneArenaFromPause",
        []()
            {
                SceneArena *arena = dynamic_cast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
                // Ensure that menu music is stopped upon exiting from pause menu into arena.
                orxSound_Stop(AudioManager::GetInstance()->m_menuMusic);
                orxSound_SetTime(AudioManager::GetInstance()->m_menuMusic, 0);
                // Re-activate arena's music.
                orxSound_Play(arena->m_pilotP1Music);
                orxSound_Play(arena->m_pilotP2Music);
                Hexpatriates::GetInstance().PauseGame(false);
            }
    },
    {
        "O-ToSceneArena",
        []()
            {
                SceneArena *arena = ScrollCast<SceneArena*>(Hexpatriates::GetInstance().GetArena());

                // The behavior to execute is different depending on whether we're transitioning to the arena from the pilot select scene or the pause/match end scene.
                if (arena != nullptr)
                {
                    // Ensure that menu music is stopped upon exiting from pause menu into arena.
                    orxSound_Stop(AudioManager::GetInstance()->m_menuMusic);
                    orxSound_SetTime(AudioManager::GetInstance()->m_menuMusic, 0);
                    // Reset arena music
                    SceneArena *arena = dynamic_cast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
                    orxSound_Stop(arena->m_pilotP1Music);
                    orxSound_SetTime(arena->m_pilotP1Music, 0);
                    orxSound_Stop(arena->m_pilotP2Music);
                    orxSound_SetTime(arena->m_pilotP2Music, 0);
                    Hexpatriates::GetInstance().PauseGame(false);
                }
                else
                {
                    SceneMenu2D *pilotSelectScene = ScrollCast<SceneMenu2D*>(Hexpatriates::GetInstance().GetSceneMenu2D());
                    std::string pilotBaseName = "O-Pilot";
                    std::string p1 = "P1";
                    std::string p2 = "P2";
                    std::string pilotP1FullName = pilotBaseName + std::to_string(pilotSelectScene->m_selectedItemIndex + 1) + p1;
                    std::string pilotP2FullName = pilotBaseName + std::to_string(pilotSelectScene->m_selectedItemIndexP2 + 1) + p2;
                    SetString("PilotP1", pilotP1FullName.c_str(), "O-SceneArena");
                    SetString("PilotP2", pilotP2FullName.c_str(), "O-SceneArena");
                }
            }
    },
    {
        "O-ToSceneMain",
        []()
            {
                // Reset arena music
                SceneArena *arena = dynamic_cast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
                orxSound_Stop(arena->m_pilotP1Music);
                orxSound_SetTime(arena->m_pilotP1Music, 0);
                orxSound_Stop(arena->m_pilotP2Music);
                orxSound_SetTime(arena->m_pilotP2Music, 0);
                Hexpatriates::GetInstance().PauseGame(false);
            }
    },
    {
        "O-ToSceneMatchEnd",
        []()
            {
                SceneArena *arena = ScrollCast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
                // Pause action.
                Hexpatriates::GetInstance().PauseAction(true);
                // Pause music.
                orxSound_Pause(arena->m_pilotP1Music);
                orxSound_Pause(arena->m_pilotP2Music);

                // Position "WON" and "LOST" text correctly
                orxVECTOR wonPos = orxVECTOR_0;
                orxVECTOR lostPos = orxVECTOR_0;
                orxVECTOR drawPos = orxVECTOR_0;
                if (arena->m_pilotP1->m_lives > arena->m_pilotP2->m_lives)
                {
                    wonPos = { -0.25f, -0.25f };
                    lostPos = { 0.25f, -0.25f };
                    // Positioning this text offscreen so it's not visible.
                    drawPos = {0, -1.0f};
                }
                else if (arena->m_pilotP1->m_lives < arena->m_pilotP2->m_lives)
                {
                    wonPos = { 0.25f, -0.25f };
                    lostPos = { -0.25f, -0.25f };
                    // Positioning this text offscreen so it's not visible.
                    drawPos = { 0, -1.0f };
                }
                else
                {
                    drawPos = { 0, -0.25f };
                    // Positioning this text offscreen so it's not visible.
                    wonPos = { -1.0f, -0.25f };
                    lostPos = { 1.0f, -0.25f };
                }
                SetVector("Pos", &wonPos, "O-WonText");
                SetVector("Pos", &lostPos, "O-LostText");
                SetVector("Pos", &drawPos, "O-DrawText");
            }
    }
};

void Scene::OnCreate()
{
    
}

void Scene::OnDelete()
{

}

orxBOOL Scene::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void Scene::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}

void Scene::TransitionToScene(const std::string &_toScene)
{
    // Execute any associated behavior(s).
    auto it = m_transitionBehaviorMap.find(_toScene);
    if (it != m_transitionBehaviorMap.end())
    {
        m_transitionBehaviorMap.at(_toScene)();
    }

    // Transition to next scene.
    CreateObject(_toScene);
}
