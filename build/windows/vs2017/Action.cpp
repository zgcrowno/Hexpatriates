#include "Action.h"
#include "MathUtil.h"

using namespace hexpatriates;

float Action::M_LogitXMin = 0.5f;

void Action::OnCreate()
{
    m_actionType = static_cast<ActionType>(GetU32(GetModelName(), "O-ActionType"));
    m_weight = GetFloat("Weight", GetModelName());
    m_momentum = GetFloat("Momentum", GetModelName());
    for (int i = 0; i < GetListCount("Factors", GetModelName()); i++)
    {
        m_factors.push_back(static_cast<Factor>(GetU32(GetListString("Factors", i, GetModelName()), "O-Factor")));
    }
    // TODO: Alter utilityFunction's behavior as appropriate.
    std::function<int(float)> utilityFunction;
    switch (m_actionType)
    {
    case MoveAggressively:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ContaminationTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ConstructionTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case PartitionDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumOpposingProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case RemainingMatchTime:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case MoveDefensively:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ContaminationTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ConstructionTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case PartitionDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumOpposingProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case RemainingMatchTime:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case DontMove:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case ContaminationTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ConstructionTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case RemainingMatchTime:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case Jump:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case DontJump:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case Fall:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case DontFall:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case DashAggressively:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ContaminationTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ConstructionTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case PartitionDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumOpposingProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case RemainingMatchTime:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case DashDefensively:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ContaminationTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case ConstructionTimer:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case PartitionDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumOpposingProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case RemainingMatchTime:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case Parry:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case Melee:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case Downstab:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case NumLives:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case IFrames:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumOpposingProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case FireNeutral:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case OpposingPilotDistanceY:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case FireUpward:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case OpposingPilotDistanceY:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case FireDownward:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistanceX:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case OpposingPilotDistanceY:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case FireSuper:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
        break;
    case DontAct:
        for (Factor factor : m_factors)
        {
            switch (factor)
            {
            case MostPressingProjectileDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case OpposingPilotDistance:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            case NumOpposingProjectiles:
                utilityFunction = [this](float _normalizedUtility)
                {
                    // Dividing _normalizedUtility by 2 so as to prevent logitX from exceeding a value of 1.
                    float logitX = M_LogitXMin + (_normalizedUtility / 2.0f);
                    float logitResult = MathUtil::Logit(logitX, EULER, false);

                    return Compensate(logitResult);
                };
                break;
            }
            m_utilityFunctionMap.insert(std::pair<Factor, std::function<int(float)>>(factor, utilityFunction));
        }
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

const float Action::Compensate(const float &_score)
{
    int numFactors = m_factors.size();
    float modificationFactor = 1 - (1 / numFactors);
    float makeUpValue = (1 - _score) * modificationFactor;
    return _score + (makeUpValue * _score);
}
