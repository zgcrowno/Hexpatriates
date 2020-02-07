#include "Action.h"
#include "MathUtil.h"

using namespace hexpatriates;

float Action::M_LogitXMin = 0.5f;

void Action::OnCreate()
{
    m_actionType = static_cast<ActionType>(GetU32(GetModelName(), "O-ActionType"));
    m_weight = GetFloat("Weight", GetModelName());
    m_momentum = GetFloat("Momentum", GetModelName());
    // TODO: Alter m_function's behavior as appropriate.
    switch (m_actionType)
    {
    case MoveAggressively:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case MoveDefensively:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case DontMove:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case Jump:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case DontJump:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case Fall:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case DontFall:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case DashAggressively:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case DashDefensively:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case Parry:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case Melee:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case Downstab:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case FireNeutral:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case FireUpward:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case FireDownward:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case FireSuper:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    case DontAct:
        m_function = [this](float _normalizedUtility)
        {
            // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
            float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
            float logitResult = MathUtil::Logit(logitX, EULER, false);

            return ceilf(logitResult * m_weight * m_momentum * m_granularity);
        };
        break;
    }
}

void Action::OnDelete()
{

}

orxBOOL Action::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{

    return orxTRUE;
}

void Action::Update(const orxCLOCK_INFO &_rstInfo)
{

}

const float Compensate(const float &_score, const int _numFactors)
{
    float modificationFactor = 1 - (1 / _numFactors);
    float makeUpValue = (1 - _score) * modificationFactor;
    return _score + (makeUpValue * _score);
}
