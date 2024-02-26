#include <iostream>
#include <memory>

#include "BSCall.h"
#include "MonteCarloCall.h"
#include "OptionCalc.h"
#include "OptionDef.h"
#include "util.h"

int main()
{
    optioncalc::def::OptionData data = {};
    optioncalc::def::MonteCarloOptionData montedata = optioncalc::util::monteCarloOptionDataInit();
    auto bsCall = std::make_unique<optioncalc::BSCall>(data);
    auto mCCall = std::make_unique<optioncalc::MonteCarloCall>(montedata);

    optioncalc::OptionCalc calculator;

    calculator.optionSet(std::move(bsCall));
    calculator.compute();

    calculator.optionSet(std::move(mCCall));
    calculator.compute();

    return 0;
}