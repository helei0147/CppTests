

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "constraint.h"
#include "value.h"
#include "variable.h"
#include "domain.h"
#include "maxmin.h"
class model
{
public:
    model(domain* tempdomainPointer,
          variable* tempvariablePointer,
          constraint* tempConstraintPointer,
          int** tempMatrix,
          maxandmin** edge);
private:
    domain* domainPointer;
    variable* variablePointer;
    constraint* constraintPointer;
    maxandmin** edgeStorage;
    int ** Matrix;//存储两边两之间是否有约束的矩阵
};
#endif
