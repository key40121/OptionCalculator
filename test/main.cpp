#include <iostream>
#include <memory>

#include "BSCall.h"
#include "MonteCarloCall.h"
#include "OptionCalc.h"
#include "util.h"
#include "Logger.h"

int main()
{
    optioncalc::OptionData data = optioncalc::util::optionDataInit();
    auto bsCall = std::make_unique<optioncalc::BSCall>(data);

    optioncalc::MonteCarloOptionData montedata = optioncalc::util::monteCarloOptionDataInit();
    auto mCCall = std::make_unique<optioncalc::MonteCarloCall>(montedata);

    optioncalc::OptionCalc calculator;

    /* strategy : Pass instance */

    calculator.optionSet(std::move(bsCall));
    calculator.compute();

    calculator.optionSet(std::move(mCCall));
    calculator.compute();

    return 0;
}