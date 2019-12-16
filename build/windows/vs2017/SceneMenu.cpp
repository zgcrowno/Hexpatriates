#include "SceneMenu.h"

using namespace hexpatriates;

void SceneMenu::OnCreate()
{
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        m_menuItems.push_back(static_cast<ScrollMod*>(child));
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
