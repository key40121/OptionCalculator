#include <iostream>
#include <memory>

#include "BSCall.h"
#include "MonteCarloCall.h"
#include "OptionCalc.h"
#include "OptionDef.h"
#include "util.h"
#include "Logger.h"

int main()
{
    //optioncalc::def::OptionData data = {};
    //auto bsCall = std::make_unique<optioncalc::BSCall>(data);

    optioncalc::def::MonteCarloOptionData montedata = optioncalc::util::monteCarloOptionDataInit();
    auto mCCall = std::make_unique<optioncalc::MonteCarloCall>(montedata);

    optioncalc::OptionCalc calculator;

    // calculator.optionSet(std::move(bsCall));
    // calculator.compute();

    // Strategy pattern => Just passing a class
    calculator.optionSet(std::move(mCCall));
    calculator.compute();

    std::string temp{"Ttemp"};
    Logger::INFO(temp);
    Logger::ERROR(temp);
    Logger::INFO(temp);



    return 0;
}