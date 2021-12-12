#include "springpendulum.h"
#include "constants.h"
#include "../Display/drawingsupport.h"

using namespace std;

SpringPendulum::SpringPendulum(DrawingSupport* supp, double mass,
                               double cst, double length,
                               Vector A, Vector o)
:Oscillator(supp, 2, 0, A, o), Pendulum(supp, 2, 0, A, o),
 Spring(supp, mass, cst), L(length)
{}

Vector SpringPendulum::f(double t)
{
    return Vector({ - (k/m)*(1.0 - L/P.norm()) * P[1], g_CONST - (k/m)*(1.0 - L/P.norm()) * P[2]});
}

ostream& SpringPendulum::display(ostream& sortie) const
{
    sortie	<<"## Spring-Pendulum"<<endl
            <<"- Stiffness (k) : "<<k<<endl
            <<"- Length at rest (L) : "<<L<<endl
            <<"- Mass (kg):\t"<<m<<endl<<endl;

    Oscillator::display(sortie);
    return sortie;
}

void SpringPendulum::draw()
{
    support->draw(*this);
}

std::unique_ptr<SpringPendulum> SpringPendulum::clone() const
{
    return std::unique_ptr<SpringPendulum>(new SpringPendulum(*this));
}

std::unique_ptr<Oscillator> SpringPendulum::copy() const
{
    return clone();
}

