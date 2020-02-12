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
    const bool &_flip,
    const bool &_unidirectional,
    const float &_verticalShift,
    const float &_horizontalShift,
    const float &_tilt)
{
    float retVal = powf(_x - _horizontalShift, _exponent) + _verticalShift + (_tilt * _x);

    if (_unidirectional)
    {
        retVal = fabsf(retVal);
    }

    if (_flip)
    {
        return 1 - retVal;
    }

    return retVal;
}

float MathUtil::Logistic(
    const float &_x,
    const bool &_flip,
    const float &_l,
    const float &_logBase,
    const float &_k,
    const float &_horizontalShift)
{
    float unflippedReturn = (_l / (1 + powf(_logBase, -_k * (_x - _horizontalShift))));

    if (_flip)
    {
        return 1 - unflippedReturn;
    }

    return unflippedReturn;
}

float MathUtil::Logit(
    const float &_x,
    const bool &_flip,
    const bool &_shiftUp,
    const float &_compressionFactor,
    const float &_logBase)
{
    float retVal = Log(_x / (1 - _x), _logBase);

    if (_shiftUp)
    {
        retVal += 5;
    }

    retVal /= _compressionFactor;

    if (_flip)
    {
        return 1 - retVal;
    }

    return retVal;
}
