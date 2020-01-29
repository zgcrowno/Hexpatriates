#include "UBucket.h"

using namespace hexpatriates;

void UBucket::OnCreate()
{
    m_action = ScrollCast<Action*>(GetOwnedChild());
}

void UBucket::OnDelete()
{

}

orxBOOL UBucket::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void UBucket::Update(const orxCLOCK_INFO &_rstInfo)
{

}
