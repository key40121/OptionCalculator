#ifndef BSCALL_H
#define BSCALL_H

#include <utility>

#include "Option.h"
#include "OptionDef.h"

namespace optioncalc
{

class BSCall : public Option // Base class
{
public:

    template<typename T>
    explicit BSCall(T&& data) : mData(std::forward<T>(data)) {}

    double compute() override;

private:
    optioncalc::def::OptionData mData;
};

}

#endif