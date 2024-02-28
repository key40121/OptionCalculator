#ifndef BSCALL_H
#define BSCALL_H

#include <utility>

#include "Option.h"
#include "OptionDef.h"

namespace optioncalc
{

class BSCall : public Option
{
public: // TODO

    explicit BSCall(optioncalc::def::OptionData data) : mData(data) {}

    double compute() override;

private:
    optioncalc::def::OptionData mData;
};

}

#endif