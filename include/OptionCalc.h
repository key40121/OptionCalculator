#ifndef CALC_C
#define CALC_C

#include <memory>
#include <utility>

#include "Option.h"

namespace optioncalc
{

class OptionCalc
{
public:
    // TBD Singleton

    void optionSet(std::unique_ptr<Option> operation);
    double compute();

private:
    int mCurrent{};
    std::unique_ptr<Option> mOperation;
};

}

#endif