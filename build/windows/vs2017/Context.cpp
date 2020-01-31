#include "Context.h"

using namespace hexpatriates;

void Context::OnCreate()
{
    for (ScrollObject *child = GetOwnedChild(); child; child = child->GetOwnedSibling())
    {
        RCurve *rCurve = dynamic_cast<RCurve*>(child);
        if (rCurve != nullptr)
        {
            m_rCurves.push_back(rCurve);
        }
    }
}

void Context::OnDelete()
{

}

orxBOOL Context::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void Context::Update(const orxCLOCK_INFO &_rstInfo)
{

}
