#ifndef UTIL_H
#define UTIL_H

#include <random>

#include "BSCall.h"
#include "MonteCarloCall.h"

namespace optioncalc::util
{
    inline double putCallParity()
    {
        return 1.0;
    }

    inline constexpr optioncalc::OptionData optionDataInit()
    {

        optioncalc::OptionData data = {};
        data.expiry = 1.0; // t = 1;
        data.spotPrice = 100.0; // S = 100;
        data.volatility = 0.20; // σ = 20%;
        data.riskFreeRate = 0.0121; // r = 1.21%;
        data.strike = 100; // K = 100.21
        data.dividentYield = 0.01;

        return data;
    }

    inline constexpr optioncalc::MonteCarloOptionData monteCarloOptionDataInit()
    {
        optioncalc::MonteCarloOptionData data = {};
        data.expiry = 1.0; // t = 1;
        data.spotPrice = 100.0; // S = 100;
        data.volatility = 0.20; // σ = 20%;
        data.riskFreeRate = 0.0121; // r = 1.21%;
        data.strike = 100.21; // K = 100.21
        data.numberOfPaths = optioncalc::NUMBER_OF_PATHS;
        data.numberOfTrials = optioncalc::NUMBER_OF_TRIALS;

        return data;
    }

    inline double GetOneGaussianByRandomLibrary()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::normal_distribution<double> dist(0.0, 1.0);

        return dist(gen);
    }
}

#endif