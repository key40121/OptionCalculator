#include "OptionCalc.h"

namespace optioncalc
{

double OptionCalc::compute()
{
    if (mOperation != nullptr)
    {
        return mOperation->compute();
    }
    else
    {
        return 0;
    }
}

void OptionCalc::optionSet(std::unique_ptr<Option> operation)
{
    mOperation = std::move(operation);
}

}