#pragma once
#include "preDefines.h"


class Goal_Evaluator
{
public:

    virtual float CalculateDesirability(Actor* a) = 0;

    virtual void SetGoal(Actor* a) = 0;

};
