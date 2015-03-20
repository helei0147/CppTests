#include "Model.h"
model::model(domain* tempdomainPointer,
             variable* tempvariablePointer,
             constraint* tempConstraintPointer,
             int** tempMatrix,
             maxandmin** edge
             )
{
    domainPointer = tempdomainPointer;
    variablePointer = tempvariablePointer;
    constraintPointer = tempConstraintPointer;
    Matrix = tempMatrix;
    edgeStorage = edge;
}