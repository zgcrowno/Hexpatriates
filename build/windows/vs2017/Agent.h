#pragma once

#include "Action.h"
#include <vector>

namespace hexpatriates
{
    class Agent
    {
    public:
        std::vector<Action> m_actions;

        void Act();
    };
}
