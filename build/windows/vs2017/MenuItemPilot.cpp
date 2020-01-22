#include "MenuItemPilot.h"

using namespace hexpatriates;

void MenuItemPilot::OnCreate()
{
    MenuItemTransitional::OnCreate();
}

void MenuItemPilot::OnDelete()
{
    MenuItemTransitional::OnDelete();
}

orxBOOL MenuItemPilot::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    MenuItemTransitional::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return orxTRUE;
}

void MenuItemPilot::Update(const orxCLOCK_INFO &_rstInfo)
{
    MenuItem::Update(_rstInfo);

    if (orxInput_HasBeenActivated("DownwardP1"))
    {
        if (m_bIsCommitted)
        {
            Transition();
        }
        else if (m_bIsSelected)
        {
            m_bIsCommitted = true;
        }
    }
}

void MenuItemPilot::Select(const bool _p1)
{
    MenuItem::Select(_p1);

    if (_p1)
    {
        AddShader("SH-OutlineP1");
    }
    else
    {
        AddShader("SH-OutlineP2");
    }
}

void MenuItemPilot::Deselect(const bool _p1)
{
    MenuItem::Deselect(_p1);

    m_bIsCommitted = false;

    if (_p1)
    {
        RemoveShader("SH-OutlineP1");
    }
    else
    {
        RemoveShader("SH-OutlineP2");
    }
}
