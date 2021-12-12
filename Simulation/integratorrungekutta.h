#ifndef INTEGRATORRUNGEKUTTA_H
#define INTEGRATORRUNGEKUTTA_H

#include "integrator.h"

class IntegratorRungeKutta: public Integrator
{
public:
    virtual ~IntegratorRungeKutta(){}
    //!Méthode d'intégration Runge-Kutta
    void integrate(Oscillator& oscillo, double dt, double t = 0) override;
};

#endif // INTEGRATORRUNGEKUTTA_H
