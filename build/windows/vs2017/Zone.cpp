#include "Zone.h"

using namespace hexpatriates;

void Zone::OnCreate()
{
    PlayerSpecific::OnCreate();
}

void Zone::OnDelete()
{

}

orxBOOL Zone::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void Zone::Update(const orxCLOCK_INFO &_rstInfo)
{

}
