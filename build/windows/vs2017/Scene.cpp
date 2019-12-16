#include "Scene.h"

using namespace hexpatriates;

void Scene::OnCreate()
{
    
}

void Scene::OnDelete()
{

}

orxBOOL Scene::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    return true;
}

void Scene::Update(const orxCLOCK_INFO &_rstInfo)
{
    
}
