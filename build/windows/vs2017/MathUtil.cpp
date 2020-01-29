#include "MathUtil.h"
#include <math.h>

using namespace hexpatriates;

float MathUtil::Log(
    const float &_value,
    const float &_base)
{
    return logf(_value) / logf(_base);
}

float MathUtil::Linear(
    const float &_x,
    const float &_slope,
    const float &_yIntercept)
{
    return _slope * _x + _yIntercept;
}

float MathUtil::Quadratic(
    const float &_x,
    const float &_exponent,
    const float &_verticalShift,
    const float &_horizontalShift,
    const float &_tilt,
    const bool &_leftOfVertexPositive)
{
    float regularReturn = powf(_x - _horizontalShift, _exponent) + _verticalShift + (_tilt * _x);

    if (_leftOfVertexPositive)
    {
        return fabsf(regularReturn);
    }

    return regularReturn;
}

float MathUtil::Logistic(
    const float &_x,
    const float &_logBase,
    const float &_horizontalShift,
    const bool &_flip)
{
    float unflippedReturn = (1 / (1 + powf(_logBase, -_x + _horizontalShift)));

    if (_flip)
    {
        return 1 - unflippedReturn;
    }

    return unflippedReturn;
}

float MathUtil::Logit(
    const float &_x,
    const float &_logBase,
    const bool &_shiftUp)
{
    float unshiftedReturn = Log(_x / (1 - _x), _logBase);

    if (_shiftUp)
    {
        return unshiftedReturn + 5;
    }

    return unshiftedReturn;
}
