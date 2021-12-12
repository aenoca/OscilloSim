#include "integratoreuler.h"
//#include "vector.h"
#include "../Oscillators/oscillator.h"

void IntegratorEuler::integrate(Oscillator& oscillo, double dt, double t)
{
    Vector temp = oscillo.getP()+ dt*oscillo.getQ();
    //!compute velocity in t+dt
    oscillo.setQ(oscillo.getQ()+ dt*oscillo.f(t));

    //!compute postion in t+dt with velocity in t
    oscillo.setP(temp);
}
