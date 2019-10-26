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

ScrollMod *ScrollMod::CreateObject(
    const orxCHAR *_modelName,
    std::map<const orxCHAR*, const orxBOOL> _boolParamMap,
    std::map<const orxCHAR*, const orxFLOAT> _floatParamMap,
    std::map<const orxCHAR*, const orxVECTOR*> _vectorParamMap,
    std::map<const orxCHAR*, const orxSTRING> _stringParamMap)
{
    for (auto it = _boolParamMap.begin(); it != _boolParamMap.end(); it++)
    {
        SetBool(it->first, it->second, _modelName);
    }
    for (auto it = _floatParamMap.begin(); it != _floatParamMap.end(); it++)
    {
        SetFloat(it->first, it->second, _modelName);
    }
    for (auto it = _vectorParamMap.begin(); it != _vectorParamMap.end(); it++)
    {
        SetVector(it->first, it->second, _modelName);
    }
    for (auto it = _stringParamMap.begin(); it != _stringParamMap.end(); it++)
    {
        SetString(it->first, it->second, _modelName);
    }

    return (ScrollMod*)Hexpatriates::GetInstance().CreateObject(_modelName);
}

orxBOOL __fastcall ScrollMod::GetBool(const orxCHAR *_key, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxBOOL retVal = orxConfig_GetBool(_key);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxFLOAT __fastcall ScrollMod::GetFloat(const orxCHAR *_key, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxFLOAT retVal = orxConfig_GetFloat(_key);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxVECTOR *__fastcall ScrollMod::GetVector(const orxCHAR *_key, orxVECTOR *_passedVector, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxVECTOR *retVal = orxConfig_GetVector(_key, _passedVector);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

const orxCHAR *__fastcall ScrollMod::GetString(const orxCHAR *_key, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    const orxCHAR *retVal = orxConfig_GetString(_key);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxSTATUS __fastcall ScrollMod::SetBool(const orxCHAR *_key, orxBOOL _value, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxSTATUS retVal = orxConfig_SetBool(_key, _value);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxSTATUS __fastcall ScrollMod::SetFloat(const orxCHAR *_key, orxFLOAT _value, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxSTATUS retVal = orxConfig_SetFloat(_key, _value);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxSTATUS __fastcall ScrollMod::SetVector(const orxCHAR *_key, const orxVECTOR *_value, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxSTATUS retVal = orxConfig_SetVector(_key, _value);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxSTATUS __fastcall ScrollMod::SetString(const orxCHAR *_key, const orxCHAR *_value, const orxCHAR *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxSTATUS retVal = orxConfig_SetString(_key, _value);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
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

ScrollObject *ScrollMod::GetChildByName(const std::vector<orxSTRING> &_childNameList)
{
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        for (orxSTRING str : _childNameList)
        {
            if (orxString_Compare(child->GetModelName(), str) == 0)
            {
                return child;
            }
        }
    }
}

orxVECTOR ScrollMod::GetWorldGravity()
{
    orxVECTOR worldGravity = orxVECTOR_0;

    return *orxPhysics_GetGravity(&worldGravity);
}

orxBODY_PART *ScrollMod::GetBodyPartByName(const orxCHAR *_partName)
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

void ScrollMod::SetTargetAnim(const orxCHAR *_animName)
{
    orxObject_SetTargetAnim(GetOrxObject(), _animName);
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
