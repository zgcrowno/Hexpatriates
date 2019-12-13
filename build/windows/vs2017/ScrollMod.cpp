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

void ScrollMod::Substring(const orxCHAR *_strIn, orxCHAR *_strOut, const int &_index, const int &_size)
{
    int i = 0;

    while (i < _size)
    {
        _strOut[i] = _strIn[_index + i];
        i++;
    }

    _strOut[i] = '\0';
}

const float inline ScrollMod::AngleBetween(orxVECTOR _from, orxVECTOR _to)
{
    return atan2f(_to.fY - _from.fY, _to.fX - _from.fX);
}

const orxVECTOR ScrollMod::NormalizeVector(const orxVECTOR &_vec)
{
    orxVECTOR normalizedVector = orxVECTOR_0;

    return *orxVector_Normalize(&normalizedVector, &_vec);
}

const float ScrollMod::VectorToRadians(const orxVECTOR &_vec)
{
    return orxMath_ATan(_vec.fY, _vec.fX);
}

const orxVECTOR ScrollMod::RadiansToVector(const float &_angle)
{
    return { orxMath_Cos(_angle), orxMath_Sin(_angle) };
}

const orxVECTOR ScrollMod::ReflectionVector(const orxVECTOR &_hit, const orxVECTOR &_normal)
{
    float dot = orxVector_2DDot(&_hit, &_normal);
    orxVECTOR subtrahend = { 2 * dot * _normal.fX, 2 * dot * _normal.fY };

    return { _hit.fX - subtrahend.fX, _hit.fY - subtrahend.fY };
}

const std::vector<orxVECTOR> ScrollMod::Raycast(
    const orxVECTOR &_begin,
    const float &_direction,
    const int &_checkMask,
    const int &_selfFlags,
    const float &_distance,
    const bool &_bEarlyExit)
{
    orxVECTOR endingPos = { _begin.fX + orxMath_Cos(_direction) * _distance, _begin.fY + orxMath_Sin(_direction) * _distance };
    orxVECTOR hitPos;
    orxVECTOR hitNormal;
    orxObject_Raycast(&_begin, &endingPos, _selfFlags, _checkMask, _bEarlyExit, &hitPos, &hitNormal);

    return std::vector<orxVECTOR> { hitPos, hitNormal };
}

ScrollMod *ScrollMod::CreateObject(
    const orxCHAR *_modelName,
    std::map<const orxCHAR*, const orxBOOL> _boolParamMap,
    std::map<const orxCHAR*, const orxFLOAT> _floatParamMap,
    std::map<const orxCHAR*, const orxVECTOR*> _vectorParamMap,
    std::map<const orxCHAR*, const orxSTRING> _stringParamMap)
{
    std::map<const orxCHAR*, const orxBOOL> initialBoolMap;
    std::map<const orxCHAR*, const orxFLOAT> initialFloatMap;
    std::map<const orxCHAR*, const orxVECTOR*> initialVectorMap;
    std::map<const orxCHAR*, const orxSTRING> initialStringMap;

    for (auto it = _boolParamMap.begin(); it != _boolParamMap.end(); it++)
    {
        initialBoolMap.insert({it->first, GetBool(it->first, _modelName) });
        SetBool(it->first, it->second, _modelName);
    }
    for (auto it = _floatParamMap.begin(); it != _floatParamMap.end(); it++)
    {
        initialFloatMap.insert({ it->first, GetFloat(it->first, _modelName) });
        SetFloat(it->first, it->second, _modelName);
    }
    for (auto it = _vectorParamMap.begin(); it != _vectorParamMap.end(); it++)
    {
        initialVectorMap.insert({ it->first, &GetVector(it->first, _modelName) });
        SetVector(it->first, it->second, _modelName);
    }
    for (auto it = _stringParamMap.begin(); it != _stringParamMap.end(); it++)
    {
        initialStringMap.insert({ it->first, GetString(it->first, _modelName) });
        SetString(it->first, it->second, _modelName);
    }

    ScrollMod *retVal = (ScrollMod*)Hexpatriates::GetInstance().CreateObject(_modelName);

    // Reset config values so as not to muck up future object creation.
    for (auto it = initialBoolMap.begin(); it != initialBoolMap.end(); it++)
    {
        SetBool(it->first, it->second, _modelName);
    }
    for (auto it = initialFloatMap.begin(); it != initialFloatMap.end(); it++)
    {
        SetFloat(it->first, it->second, _modelName);
    }
    for (auto it = initialVectorMap.begin(); it != initialVectorMap.end(); it++)
    {
        SetVector(it->first, it->second, _modelName);
    }
    for (auto it = initialStringMap.begin(); it != initialStringMap.end(); it++)
    {
        SetString(it->first, it->second, _modelName);
    }

    return retVal;
}

const orxVECTOR __fastcall ScrollMod::GetPosition(const bool &_bWorld) const
{
    orxVECTOR vecRef;
    ScrollObject::GetPosition(vecRef, _bWorld);

    return vecRef;
}

const orxVECTOR __fastcall ScrollMod::GetPositionNextFrame(const float &_fDT, const bool &_bWorld) const
{
    orxVECTOR curPos = GetPosition(_bWorld);
    orxVECTOR curSpeed = GetSpeed();

    return { curPos.fX + curSpeed.fX * _fDT, curPos.fY + curSpeed.fY * _fDT, curPos.fZ + curSpeed.fZ * _fDT };
}

const orxVECTOR __fastcall ScrollMod::GetScale(const bool &_bWorld) const
{
    orxVECTOR vecRef;
    ScrollObject::GetScale(vecRef, _bWorld);

    return vecRef;
}

const orxVECTOR __fastcall ScrollMod::GetSize() const
{
    orxVECTOR vecRef;
    ScrollObject::GetSize(vecRef);

    return vecRef;
}

const orxVECTOR __fastcall ScrollMod::GetScaledSize(const bool &_bWorld) const
{
    orxVECTOR size = GetSize();
    orxVECTOR scale = GetScale(_bWorld);

    return { size.fX * scale.fX, size.fY * scale.fY, size.fZ * scale.fZ };
}

const orxVECTOR __fastcall ScrollMod::GetSpeed(const bool &_bRelative) const
{
    orxVECTOR vecRef;
    ScrollObject::GetSpeed(vecRef, _bRelative);

    return vecRef;
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

orxBOOL __fastcall ScrollMod::GetListBool(const char *_key, const int _index, const char *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxBOOL retVal = orxConfig_GetListBool(_key, _index);
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

orxFLOAT __fastcall ScrollMod::GetListFloat(const char *_key, const int _index, const char *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxFLOAT retVal = orxConfig_GetListFloat(_key, _index);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxVECTOR __fastcall ScrollMod::GetVector(const orxCHAR *_key, const orxCHAR *_sectionName)
{
    orxVECTOR vecRef = orxVECTOR_0;
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxVECTOR *vec = orxConfig_GetVector(_key, &vecRef);
    orxVECTOR retVal = vec == NULL ? orxVECTOR_0 : *vec;
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxVECTOR __fastcall ScrollMod::GetListVector(const char *_key, const int _index, const char *_sectionName)
{
    orxVECTOR vecRef = orxVECTOR_0;
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxVECTOR *vec = orxConfig_GetListVector(_key, _index, &vecRef);
    orxVECTOR retVal = vec == NULL ? orxVECTOR_0 : *vec;
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

const char *__fastcall ScrollMod::GetListString(const char *_key, const int _index, const char *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    const orxCHAR *retVal = orxConfig_GetListString(_key, _index);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }
    
    return retVal;
}

const int __fastcall ScrollMod::GetListCount(const char *_key, const char *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    const int retVal = orxConfig_GetListCount(_key);
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

orxSTATUS __fastcall ScrollMod::SetListString(const char *_key, const char **_list, int _numValues, const char *_sectionName)
{
    orxBOOL sectionPassed = orxString_Compare(_sectionName, "") != 0;

    if (sectionPassed)
    {
        orxConfig_PushSection(_sectionName);
    }
    orxSTATUS retVal = orxConfig_SetListString(_key, _list, _numValues);
    if (sectionPassed)
    {
        orxConfig_PopSection();
    }

    return retVal;
}

orxSTRUCTURE *__fastcall ScrollMod::GetOwner()
{
    return orxObject_GetOwner(GetOrxObject());
}

orxSTRUCTURE *__fastcall ScrollMod::GetParent()
{
    return orxObject_GetParent(GetOrxObject());
}

void __fastcall ScrollMod::SetOwner(const ScrollObject *_owner)
{
    orxObject_SetOwner(GetOrxObject(), _owner->GetOrxObject());
}

orxSTATUS __fastcall ScrollMod::SetParent(const ScrollObject *_parent)
{
    return orxObject_SetParent(GetOrxObject(), _parent->GetOrxObject());
}

orxU16 __fastcall ScrollMod::GetSelfFlags(const orxBODY_PART *_part)
{
    return orxBody_GetPartSelfFlags(_part);
}

orxU16 __fastcall ScrollMod::GetCheckMask(const orxBODY_PART *_part)
{
    return orxBody_GetPartCheckMask(_part);
}

orxSTATUS __fastcall ScrollMod::SetSelfFlags(orxBODY_PART *_part, orxU16 _selfFlags)
{
    return orxBody_SetPartSelfFlags(_part, _selfFlags);
}

orxSTATUS __fastcall ScrollMod::SetCheckMask(orxBODY_PART *_part, orxU16 _checkMask)
{
    return orxBody_SetPartCheckMask(_part, _checkMask);
}

orxSTRUCTURE *ScrollMod::GetStructure(orxSTRUCTURE_ID _structureID)
{
    orxOBJECT *obj = GetOrxObject();
    
    return _orxStructure_GetPointer(_orxObject_GetStructure(obj, _structureID), _structureID);
}

int __fastcall ScrollMod::GetNumChildren()
{
    int result;

    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        result++;
    }

    return result;
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

orxSTATUS __fastcall ScrollMod::SetCustomGravity(orxVECTOR &_customGravity)
{
    return orxObject_SetCustomGravity(GetOrxObject(), &_customGravity);
}

void ScrollMod::SetBodyPartSolid(const orxCHAR *_partName, const orxBOOL &_bSolid)
{
    orxBody_SetPartSolid(GetBodyPartByName(_partName), _bSolid);
}

void ScrollMod::MoveTo(const orxVECTOR &_destination, const float &_speed, const float &_decelerationDistance)
{
    orxVECTOR position = GetPosition();
    float angleBetweenSelfAndTarget = AngleBetween(position, _destination);
    orxVECTOR normalizedSpeed = RadiansToVector(angleBetweenSelfAndTarget);
    float distance = orxVector_GetDistance(&position, &_destination);
    float speed = distance <= _decelerationDistance ? _speed * (distance / _decelerationDistance) : _speed;
    SetSpeed({ normalizedSpeed.fX * speed, normalizedSpeed.fY * speed });
}

void ScrollMod::Destroy()
{
    SetLifeTime(0.0);
}
