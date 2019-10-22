#include "ScrollMod.h"

using namespace hexpatriates;

void ScrollMod::OnCreate()
{

}

void ScrollMod::OnDelete()
{

}

void ScrollMod::Update(const orxCLOCK_INFO &_rstInfo)
{

}

orxSTRUCTURE *ScrollMod::GetStructure(orxSTRUCTURE_ID _structureID)
{
    orxOBJECT *obj = GetOrxObject();

    return _orxStructure_GetPointer(_orxObject_GetStructure(obj, _structureID), _structureID);
}

ScrollObject *ScrollMod::GetChildByName(const orxSTRING _childName)
{
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        if (orxString_Compare(child->GetModelName(), _childName) == 0)
        {
            return child;
        }
    }
}

orxVECTOR ScrollMod::GetWorldGravity()
{
    orxVECTOR worldGravity = orxVECTOR_0;

    return *orxPhysics_GetGravity(&worldGravity);
}

orxBODY_PART *ScrollMod::GetBodyPartByName(const orxSTRING &_partName)
{
    orxBODY *body = (orxBODY*)GetStructure(orxSTRUCTURE_ID_BODY);

    for (orxBODY_PART *part = orxBody_GetNextPart(body, orxNULL); part; part = orxBody_GetNextPart(body, part))
    {
        if (orxString_Compare(orxBody_GetPartName(part), _partName) == 0)
        {
            return part;
        }
    }
}

void ScrollMod::SetCustomGravity(orxVECTOR &_customGravity)
{
    orxObject_SetCustomGravity(GetOrxObject(), orxPhysics_GetGravity(&_customGravity));
}

void ScrollMod::SetBodyPartSolid(const orxCHAR *_partName, const orxBOOL &_bSolid)
{
    orxBody_SetPartSolid(GetBodyPartByName(_partName), _bSolid);
}

void ScrollMod::Destroy()
{
    SetLifeTime(0.0);
}
