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
            const float &_x, // The x-value we're feeding into the function.
            const float &_slope = 1, // The slope or intensity of the line.
            const float &_yIntercept = 0); // The x-value at which the line crosses the y-axis.
        static float Quadratic(
            const float &_x, // The x-value we're feeding into the function.
            const float &_exponent = 2, // The function's exponential factor.
            const bool &_flip = false, // Whether or not the function is to be vertically flipped.
            const bool &_unidirectional = false, // Whether or not both sides of the parabola's vertex should move in the same direction.
            const float &_verticalShift = 0, // The amount by which we're shifting the function vertically.
            const float &_horizontalShift = 0, // The amount by which we're shifting the function horizontally.
            const float &_tilt = 0); // The amount by which we're "tilting" the function (See Dave Mark's Behavior Mathematics for Game AI, page 233).
        static float Logistic(
            const float &_x, // The x-value we're feeding into the function.
            const bool &_flip = false, // Whether or not the function is to be vertically flipped.
            const float &_l = 1, // The curve's maximum value.
            const float &_logBase = EULER, // The logarithm base.
            const float &_k = 20, // The logistic growth rate or steepness of the curve.
            const float &_horizontalShift = 0.5f); // The x-value of the sigmoid's midpoint.
        static float Logit(
            const float &_x, // The x-value we're feeding into the function.
            const bool &_flip = false, // Whether or not the function is to be vertically flipped.
            const bool &_shiftUp = true, // Whether or not the function is to be shifted up by five (doing so prevents x-values between 0.5 and 0 from returning negative values).
            const float &_compressionFactor = 10, // The amount by which we're deviding the remainder of the function (sans flipping considerations), so as to result in a more compressed result (a value of 10 fits all relevant function information within a range of 0-1 when shifted up).
            const float &_logBase = EULER); // The logarithm base.
    };
}
