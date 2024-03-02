#ifndef BSCALL_H
#define BSCALL_H

#include <utility>

#include "Option.h"

namespace optioncalc
{

struct OptionData
{
    double expiry; // t
    double strike; // K
    double spotPrice; // S 
    double volatility; // σ
    double riskFreeRate; // r
    double dividentYield; // δ
};

class BSCall : public Option
{
/* Calculation of 
    Vannila Long Call and Long Put
    by Using Black scholes equation */
public:
    explicit BSCall(OptionData data) : mData(data) {}
    BSCall(const BSCall& rhs) : mData(rhs.mData) {}
    BSCall& operator=(const BSCall& rhs)
    {
        if (this != &rhs)
        {
            mData = rhs.mData;
        }
        return *this;
    }
    BSCall(BSCall&& rhs) noexcept : mData(std::move(mData)) {}
    BSCall& operator=(BSCall&& rhs)
    {
        if (this != &rhs)
        {
            mData = rhs.mData;
        }
        return *this;
    }

    ~BSCall() = default;

    double compute() override;

    double getCall() const;
    double getPut() const;

    /* Greek  sensitivity */
    double getDelta() const;
    double getVega() const;
    double getRho() const;
    double getTheta() const;

private:
    optioncalc::OptionData mData;
    
    void initData();
    double discountFactor; // dF
    double forwardPrice; // If there's divident yield, it has to be considered.
    double dPlus; // d+
    double dMinus; // d- = (d+ - σ√t)

    double longCallPrice;
    double longPutPrice;

    double normalCDF(double x); // For N(d+) amd N(d-)

    void calcCallPrice();
    void calcPutPrice();
    double putCallParity(double callPrice);

};

}

#endif