#include "MenuItem.h"
#include "SceneArena.h"
#include "AudioManager.h"

using namespace hexpatriates;

void MenuItem::OnCreate()
{
    InputHandler::OnCreate();

    m_bIsInteractable = GetBool("IsInteractable", ScrollMod::GetModelName());
}

void MenuItem::OnDelete()
{
    InputHandler::OnDelete();
}

orxBOOL MenuItem::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    InputHandler::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return orxTRUE;
}

void MenuItem::Update(const orxCLOCK_INFO &_rstInfo)
{
    InputHandler::Update(_rstInfo);
}

void MenuItem::Select(const bool _p1)
{
    if (_p1)
    {
        m_bIsSelected = true;
    }
    else
    {
        m_bIsSelectedP2 = true;
    }
}

void MenuItem::Deselect(const bool _p1)
{
    if (_p1)
    {
        m_bIsSelected = false;
    }
    else
    {
        m_bIsSelectedP2 = false;
    }
}

void MenuItem::HandleInput(const std::string &_playerType)
{

}
