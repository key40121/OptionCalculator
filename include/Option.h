#ifndef OPTION_H
#define OPTION_H

namespace optioncalc
{

class Option // Base class
{
public:
    virtual ~Option() = default;
    virtual double compute() = 0;
};

}

#endif