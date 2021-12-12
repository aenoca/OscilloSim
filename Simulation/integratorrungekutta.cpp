#include "integratorrungekutta.h"
//#include "vector.h"
#include "../Oscillators/oscillator.h"

void IntegratorRungeKutta::integrate(Oscillator& oscillo, double dt, double t)
{
    Vector Pi(oscillo.getP());


    Vector k1	(oscillo.getQ());
    Vector k_1	(oscillo.f(t));
    Vector k2	(k1 + (dt/2.0) * k_1);

    oscillo.setP(Pi + (dt/2.0) * k1);
    oscillo.setQ(k1 + (dt/2.0) * k_1);
    Vector k_2	(oscillo.f(t + dt/2.0));

    Vector k3 (k1 + (dt/2.0) * k_2);

    oscillo.setP(Pi + (dt/2.0) * k2);
    oscillo.setQ(k1 + (dt/2.0) * k_2);
    Vector k_3 (oscillo.f(t + dt/2.0));

    Vector k4(k1 + dt * k_3);

    oscillo.setP(Pi + dt * k3);
    oscillo.setQ(k1 + dt * k_3);
    Vector k_4(oscillo.f(t + dt));


    oscillo.setP(Pi + (dt/6.0) * (k1+2.0*k2+2.0*k3+k4));
    oscillo.setQ(k1 + (dt/6.0) * (k_1+2.0*k_2+2.0*k_3+k_4));
}
