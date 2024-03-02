#include <iostream>
#include <numeric>
#include <cmath>

#include "BSCall.h"
#include "Logger.h"

namespace optioncalc
{

double BSCall::compute()
{
    Logger::INFO("BSCall start");

    initData();
    calcCallPrice();
    calcPutPrice();

    return 2.0;
}

void BSCall::initData()
{
    discountFactor = std::exp((-1) * mData.expiry * mData.riskFreeRate);
    forwardPrice = mData.spotPrice * std::exp((mData.riskFreeRate - mData.dividentYield) * mData.expiry);

    dPlus = (std::log(mData.spotPrice / mData.strike) + (mData.riskFreeRate - mData.dividentYield + std::pow(mData.volatility, 2) / 2) * mData.expiry)
            / (mData.volatility * std::sqrt(mData.expiry));
    dMinus = dPlus - mData.volatility * std::sqrt(mData.expiry);

    Logger::DEBUG("Discount Factor : " + std::to_string(discountFactor));
    Logger::DEBUG("Forward Price : " + std::to_string(forwardPrice));
    Logger::DEBUG("d+ : " + std::to_string(dPlus));
    Logger::DEBUG("d- : " + std::to_string(dMinus));
}

double BSCall::normalCDF(double x)
{
    return (1 + std::erf(x / std::sqrt(2))) / 2;
}

void BSCall::calcCallPrice()
{
    /* 
    C = S ・ e(-δt) ・ N(d1) - K ・ e(-rt) ・ N(d2)
    */

    double Ndplus = normalCDF(dPlus);
    double Ndminus = normalCDF(dMinus);

    longCallPrice = mData.spotPrice * std::exp((-1) * mData.dividentYield * mData.expiry) * Ndplus
         - mData.strike * std::exp((-1) * mData.riskFreeRate * mData.expiry) * Ndminus;

    Logger::DEBUG("Long Call Price : " + std::to_string(longCallPrice));
}

// using put call parity formula
void BSCall::calcPutPrice()
{
    longPutPrice = putCallParity(longCallPrice);
    Logger::DEBUG("Long Put Price : " + std::to_string(longPutPrice));
}

// Return put price
double BSCall::putCallParity(double call)
{
    double put;

    put = call - mData.spotPrice + mData.strike / (1 + mData.riskFreeRate * mData.expiry);

    return put;
}

}