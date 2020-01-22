#include "SceneMenu.h"
#include "AudioManager.h"

using namespace hexpatriates;

void SceneMenu::OnCreate()
{
    m_bAllowMultiInput = GetBool("AllowMultiInput", GetModelName());

    // TODO: Figure out if there's a way to use orxSound_GetStatus to prevent overlapping sounds. This is the only method that I've found to work so far.
    if (orxSound_GetTime(AudioManager::GetInstance()->m_menuMusic) == 0)
    {
        orxSound_Play(AudioManager::GetInstance()->m_menuMusic);
    }

    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        MenuItem *menuItem = dynamic_cast<MenuItem*>(child);
        if (menuItem != nullptr && menuItem->m_bIsInteractable)
        {
            m_menuItems.push_back(menuItem);
        }
    }

    // Select the default indeces.
    if (m_bAllowMultiInput)
    {
        m_menuItems.at(0)->Select(false);
    }
    m_menuItems.at(0)->Select(true);
}

void SceneMenu::OnDelete()
{

}

orxBOOL SceneMenu::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void SceneMenu::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
