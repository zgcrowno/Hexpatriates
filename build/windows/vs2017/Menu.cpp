#include "Menu.h"

using namespace hexpatriates;

void Menu::OnCreate()
{
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        m_menuItems.push_back(static_cast<ScrollMod*>(child));
    }
}

void Menu::OnDelete()
{

}

orxBOOL Menu::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void Menu::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
