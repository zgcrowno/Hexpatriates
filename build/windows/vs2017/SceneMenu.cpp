#include "SceneMenu.h"
#include <iostream>

using namespace hexpatriates;

// Define static class members.
orxSOUND *SceneMenu::m_music = nullptr;

void SceneMenu::OnCreate()
{
    // Assign m_music its intended value if it hasn't been assigned already.
    if (m_music == nullptr)
    {
        m_music = orxSound_CreateFromConfig("SM-Menu");
    }
    // TODO: Figure out if there's a way to use orxSound_GetStatus to prevent overlapping sounds. This is the only method that I've found to work so far.
    if (orxSound_GetTime(m_music) == 0)
    {
        orxSound_Play(m_music);
    }
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        m_menuItems.push_back(ScrollCast<ScrollMod*>(child));
    }
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
