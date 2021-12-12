#ifndef INTEGRATOR_H
#define INTEGRATOR_H

//#include "../Oscillators/oscillator.h"

class Oscillator;

//!abstact class for integrators
class Integrator
{
public:
    virtual ~Integrator() {}
    //! integrate function for children classes
    virtual void integrate(Oscillator & oscillo, double dt, double t = 0) = 0;
};

#endif // INTEGRATOR_H
