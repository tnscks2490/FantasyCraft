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


/*
* AI일 경우에 Goal_Evaluator를 돌린다.
* Find Enemy, Find Farm 등등
*
* SCV의 경우
Gather Resource,
Attack Target,
Repair Target,
Follow Target,
MoveTo Position,
Build Unit,
Stop

Marine 경우,
Follow Target,
MoveTo Position,
Attack Target,
Attack Position,
Hold,
Stop,

Ex ....
Follow Target,
MoveTo Position,
Attack Target,
Attack Position,
Hold,
Stop,

////Ex Skill

*/
