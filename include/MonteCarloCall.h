#ifndef MONTE_CARLO_CALL_H
#define MONTE_CARLO_CALL_H

#include <utility>
#include <vector>

#include "Option.h"

namespace optioncalc
{

static constexpr int NUMBER_OF_PATHS = 4;
static constexpr int NUMBER_OF_TRIALS = 10;

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

template<typename T>
concept MonteCarloData = std::is_convertible_v<T, MonteCarloOptionData>;

class MonteCarloCall : public Option
{
public:

    using CallPremium = double;
    using Prob = double;

    // Just wanted to use concept(C++20) No need
    template<MonteCarloData T>
    explicit MonteCarloCall(T&& data) 
        : mData(std::forward<T>(data)) {}

    // Copy ctr
    MonteCarloCall(const MonteCarloCall& rhs) : mData(rhs.mData), mRetStore(rhs.mRetStore) {}

    // Copy assignment
    MonteCarloCall& operator=(const MonteCarloCall& rhs)
    {
        if (this != &rhs)
        {
            mData = rhs.mData;
            mRetStore = rhs.mRetStore;
        }
        return *this;
    }

    // Move ctr
    MonteCarloCall(MonteCarloCall&& rhs) noexcept
        : mData(rhs.mData), mRetStore(std::move(rhs.mRetStore)) {} 

    // Move assignment
    MonteCarloCall& operator=(MonteCarloCall&& rhs)
    {
        if (this != &rhs)
        {
            mData = rhs.mData;
            mRetStore = std::move(rhs.mRetStore);
        }
        return *this;
    }

    ~MonteCarloCall() // dtr
    {
        mRetStore.clear();
        mRetStore.shrink_to_fit();
    }

    // entry function
    double compute() override;

private:
    MonteCarloOptionData mData;
    std::vector<CallPremium> mRetStore;

    // variables needed to calculate.
    void initValues(); 
    double stepRange; // e.g. if year 1 and num of paths 4 then 0.25
    double discountFactor; // dF
    double forwardPrice; // spotrate / df;
    double stepPrice; // Price that is used to calculate each step's call premium; thus this will be updated.

    double calcCallPrice();
    double calcCallPriceStepsThrough();
};

}

#endif