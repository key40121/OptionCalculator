#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "MonteCarloCall.h"
#include "util.h"

namespace optioncalc
{

double MonteCarloCall::compute()
{
    initValues();

    for (int i=0; i<mData.numberOfTrials; i++)
    {
        calcCallPriceStepsThrough();
    }

    double retSum = std::accumulate(mRetStore.cbegin(), mRetStore.cend(), 0.0);
    double ret = retSum / mRetStore.size();

    std::cout << __func__ << " | Call Premium : " <<  ret << std::endl;

    return ret;
}

void MonteCarloCall::initValues()
{
    stepRange = mData.expiry / mData.numberOfPaths;
    discountFactor = std::exp((-1) * mData.riskFreeRate * mData.expiry);
    forwardPrice = mData.spotPrice * std::exp(mData.riskFreeRate * mData.expiry);
    stepPrice = mData.spotPrice;
}

double MonteCarloCall::calcCallPrice()
{
    double ret;

    ret = std::exp(mData.volatility * std::sqrt(stepRange) * optioncalc::util::GetOneGaussianByRandomLibrary()
            - std::pow(mData.volatility, 2) * stepRange / 2) * stepPrice; 

    return ret;
}

double MonteCarloCall::calcCallPriceStepsThrough()
{
    std::cout << "spotprice : " << mData.spotPrice << " | ";
    double ret;
    for (int j=0; j<mData.numberOfPaths; j++)
    {
        ret = calcCallPrice();
        std::cout << ret << " | ";
        stepPrice = ret;
    }

    // std::max(thisPayOff, 0);
    double thisPayOff = stepPrice - mData.strike;
    thisPayOff = std::max(thisPayOff, 0.0);

    std::cout << "Call Premium : " << thisPayOff;
    std::cout << "\n";

    mRetStore.push_back(thisPayOff); // Done
    stepPrice = mData.spotPrice; // Reset

    return thisPayOff;
}

}