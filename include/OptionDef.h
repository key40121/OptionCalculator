#ifndef OPTION_DEF_H
#define OPTION_DEF_H

namespace optioncalc::def
{

static constexpr int NUMBER_OF_PATHS = 4;
static constexpr int NUMBER_OF_TRIALS = 10;

struct OptionData
{
    double expiry;
};

struct MonteCarloOptionData
{
    double expiry; // t
    double strike; // K
    double spotPrice; // S 
    double volatility; // σ
    double riskFreeRate; // r
    int numberOfPaths; // number of steps, paths
    int numberOfTrials; // number of trials of this experiments
};

}

#endif