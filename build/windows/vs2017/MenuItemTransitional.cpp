#include "MenuItemTransitional.h"
#include "Scene.h"

using namespace hexpatriates;

void MenuItemTransitional::OnCreate()
{
    MenuItem::OnCreate();

    m_toScene = GetString("ToScene", GetModelName());
}

void MenuItemTransitional::OnDelete()
{
    MenuItem::OnDelete();
}

orxBOOL MenuItemTransitional::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    MenuItem::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return orxTRUE;
}

void MenuItemTransitional::Update(const orxCLOCK_INFO &_rstInfo)
{
    MenuItem::Update(_rstInfo);

    if (m_bIsSelected)
    {
        if (orxInput_HasBeenActivated("DownwardP1"))
        {
            Transition();
        }
    }
}

void MenuItemTransitional::Transition()
{
    // Transition to next scene.
    if (orxString_Compare(GetModelName().c_str(), "O-QuitText") == 0)
    {
        exit(orxSTATUS_SUCCESS);
    }
    else
    {
        Scene::TransitionToScene(m_toScene);
    }
}

void MenuItemTransitional::Select(const bool _p1)
{
    MenuItem::Select(_p1);

    AddShader("SH-OutlineText");
}

void MenuItemTransitional::Deselect(const bool _p1)
{
    MenuItem::Deselect(_p1);

    RemoveShader("SH-OutlineText");
}
