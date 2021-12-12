#ifndef INTEGRATOREULER_H
#define INTEGRATOREULER_H

#include "integrator.h"

//!euler integrator
class IntegratorEuler: public Integrator
{
public:
    virtual ~IntegratorEuler() {}
    //!integration method euler
    void integrate(Oscillator& oscillo, double dt, double t = 0) override;
};

#endif // INTEGRATOREULER_H
