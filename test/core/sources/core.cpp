
// Include
#include "core/includes/core.h"

double core::compute(operators pOperation, double pValueA, double pValueB) const
{
    switch (pOperation)
    {
        case operators::ADDITION:
        {
            return this->addition(pValueA, pValueB);
        }
        default:
        {
            return core::invalid;
        }
    }
    return core::invalid;
}

double core::addition(double pValueA, double pValueB) const
{
    return pValueA + pValueB;
}
