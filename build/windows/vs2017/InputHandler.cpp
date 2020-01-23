#include "InputHandler.h"

using namespace hexpatriates;

void InputHandler::OnCreate()
{
    m_bAllowMultiInput = GetBool("AllowMultiInput", GetModelName());
}

void InputHandler::OnDelete()
{

}

orxBOOL InputHandler::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void InputHandler::Update(const orxCLOCK_INFO &_rstInfo)
{
    HandleInput("P1");
    if (m_bAllowMultiInput)
    {
        HandleInput("P2");
    }
}
