#pragma once

#include "Consideration.h"
#include <vector>

namespace hexpatriates
{
    class Action
    {
    public:
        // Generally speaking, how important is this action?
        float m_weight;
        // Generally speaking, how likely is an agent to deviate from this action once they're already engaged in it?
        float m_momentum;
        std::vector<Consideration> m_considerations;

        float Score();
    };
}
