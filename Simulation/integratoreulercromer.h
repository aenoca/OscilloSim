#ifndef INTEGRATOREULERCROMER_H
#define INTEGRATOREULERCROMER_H

#include "integrator.h"

class IntegratorEulerCromer: public Integrator
{
public:
    virtual ~IntegratorEulerCromer (){}
    //!Méthode d'intégration d'Euler-Cromer
    void integrate(Oscillator & oscillo, double dt, double t = 0) override;
};

#endif // INTEGRATOREULERCROMER_H
