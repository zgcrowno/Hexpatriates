#include "SceneMenu.h"
#include "AudioManager.h"

using namespace hexpatriates;

void SceneMenu::OnCreate()
{
    Scene::OnCreate();
    InputHandler::OnCreate();

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

    m_menuItemsWidth = GetFloat("MenuItemsWidth", GetModelName());
    m_menuItemsHeight = GetFloat("MenuItemsHeight", GetModelName());

    // Select the default indeces.
    if (m_bAllowMultiInput)
    {
        m_menuItems.at(0)->Select(false);
    }
    m_menuItems.at(0)->Select(true);
}

void SceneMenu::OnDelete()
{
    Scene::OnDelete();
    InputHandler::OnDelete();
}

orxBOOL SceneMenu::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Scene::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);
    InputHandler::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void SceneMenu::Update(const orxCLOCK_INFO &_rstInfo)
{
    Scene::Update(_rstInfo);
    InputHandler::Update(_rstInfo);
}

void SceneMenu::HandleInput(const std::string &_playerType)
{
    // Handle menu item index selection
    int &selectedItemIndex = orxString_Compare(_playerType.c_str(), "P1") == 0 ? m_selectedItemIndex : m_selectedItemIndexP2;
    if (orxInput_HasBeenActivated(("Up" + _playerType).c_str()))
    {
        m_menuItems.at(selectedItemIndex)->Deselect(true);
        if (selectedItemIndex >= m_menuItemsWidth)
        {
            selectedItemIndex -= m_menuItemsWidth;
        }
        else
        {
            selectedItemIndex += m_menuItemsWidth * (m_menuItemsHeight - 1);
        }
        m_menuItems.at(selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated(("Down" + _playerType).c_str()))
    {
        m_menuItems.at(selectedItemIndex)->Deselect(true);
        if (selectedItemIndex >= m_menuItemsWidth * (m_menuItemsHeight - 1))
        {
            selectedItemIndex -= m_menuItemsWidth * (m_menuItemsHeight - 1);
        }
        else
        {
            selectedItemIndex += m_menuItemsWidth;
        }
        m_menuItems.at(selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated(("Left" + _playerType).c_str()))
    {
        m_menuItems.at(selectedItemIndex)->Deselect(true);
        if (selectedItemIndex % m_menuItemsWidth == 0)
        {
            selectedItemIndex += m_menuItemsWidth - 1;
        }
        else
        {
            selectedItemIndex--;
        }
        m_menuItems.at(selectedItemIndex)->Select(true);
    }
    else if (orxInput_HasBeenActivated(("Right" + _playerType).c_str()))
    {
        m_menuItems.at(selectedItemIndex)->Deselect(true);
        if ((selectedItemIndex + 1) % m_menuItemsWidth == 0)
        {
            selectedItemIndex -= m_menuItemsWidth - 1;
        }
        else
        {
            selectedItemIndex++;
        }
        m_menuItems.at(selectedItemIndex)->Select(true);
    }
    // Handle previous scene navigation
    if (orxInput_HasBeenActivated(("Super" + _playerType).c_str()) && orxString_Compare(m_cancelToScene.c_str(), "") != 0)
    {
        orxSound_Play(AudioManager::GetInstance()->m_sndCancel);
        TransitionToScene(m_cancelToScene);
    }
}
