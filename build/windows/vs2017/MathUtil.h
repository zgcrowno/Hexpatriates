#pragma once

#define EULER 2.71828182845904523536

namespace hexpatriates
{
    class MathUtil
    {
    public:
        // Log function which returns the log (base _base) of the passed value.
        static float Log(
            const float &_value,
            const float &_base);
        // Curve functions.
        static float Linear(
            const float &_x,
            const float &_slope,
            const float &_yIntercept);
        static float Quadratic(
            const float &_x,
            const float &_exponent,
            const float &_verticalShift,
            const float &_horizontalShift,
            const float &_tilt,
            const bool &_leftOfVertexPositive);
        static float Logistic(
            const float &_x,
            const float &_logBase,
            const float &_horizontalShift,
            const bool &_flip);
        static float Logit(
            const float &_x,
            const float &_logBase,
            const bool &_shiftUp);
    };
}
