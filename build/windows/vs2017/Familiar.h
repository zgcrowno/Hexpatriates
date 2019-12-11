#pragma once

#include "Hexpatriates.h"
#include "Parryable.h"
#include "Spawner.h"
#include <queue>

namespace hexpatriates
{
    class Familiar : public Parryable
    {
    private:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete();
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        enum Type
        {
            Turret,
            RemoteDetonation
        };

        Type m_type;
        bool m_bIsFired;
        bool m_bIsAttached;
        int m_framesBehind;
        float m_attachedMovementDirection;
        std::queue<orxVECTOR> m_upcomingPositions;
        Spawner *m_gun;

        virtual void ParriedBehavior();
        void Move();
        void FireSelf(const float _direction, const Type _type);
        void Detonate();
    };
}
