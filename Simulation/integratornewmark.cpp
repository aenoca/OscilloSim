#include "integratornewmark.h"
//#include "vector.h"
#include "../Oscillators/oscillator.h"

IntegratorNewmark::IntegratorNewmark(double epsilon)
:eps(epsilon)
{}

void IntegratorNewmark::integrate(Oscillator & oscillo, double dt, double t)
{
    Vector Pi	(oscillo.getP());
    Vector Vi	(oscillo.getQ());

    Vector Ai	(oscillo.f(t));

    Vector q (0);
    Vector r (0);


    do{
        q  = oscillo.getP();
        r  = oscillo.f(t + dt);

        oscillo.setQ(Vi + dt*(r+Ai)*0.5);
        oscillo.setP(Pi + dt*Vi + dt*dt/3.0*(0.5*r+Ai));
    }while((oscillo.getP()-q).squareNorm()>=eps*eps);
}
