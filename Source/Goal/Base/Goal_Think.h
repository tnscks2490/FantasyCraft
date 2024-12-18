#pragma once
#include "Goal.h"
#include "Goal_Evaluator.h"
#include "Goal_Composite.h"


class Goal_Think : public Goal_Composite
{
    std::vector<Goal_Evaluator*> m_Evaluators;

public:

    Goal_Think(Actor* pE);

    void SelectTactic();

    void Start() override;
    int Do() override;
    void End() override;

};
