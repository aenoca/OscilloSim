#include "integratoreulercromer.h"
//#include "vector.h"
#include "../Oscillators/oscillator.h"

void IntegratorEulerCromer::integrate(Oscillator & oscillo, double dt, double t)
{
    //calcul de la vitesse en t+dt i.e.
    oscillo.setQ(oscillo.getQ()+ dt*oscillo.f(t));

    //clacul de la position en t+dt (avec la vitesse en t+dt)
    oscillo.setP(oscillo.getP()+ dt*oscillo.getQ());
}
