#ifndef INTEGRATORNEWMARK_H
#define INTEGRATORNEWMARK_H

#include "integrator.h"

class IntegratorNewmark: public Integrator
{
private:
    //!tolerance
    double eps;

public:
    //!constructor
    IntegratorNewmark(double epsilon=0.001);

    virtual ~IntegratorNewmark() {}

    //!Méthode d'intégration Newmark
    void integrate(Oscillator & oscillo, double dt, double t = 0) override;
};

#endif // INTEGRATORNEWMARK_H
