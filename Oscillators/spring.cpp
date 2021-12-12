#include "spring.h"
#include "constants.h"
//#include "../Simulation/vector.h"
#include "../Display/drawingsupport.h"

using namespace std;

Spring::Spring(DrawingSupport* supp, double mass, double cst, double fr,
               Vector A, Vector o)
:Oscillator(supp, 1, fr, A, o), m(mass), k(cst)
{}

Vector Spring::f(double t)
{
    return Vector({-(k/m) * P[1] - (lambda/m) * Q[1] + G_CONST * a});
}

ostream& Spring::display(ostream& sortie) const
{
    sortie  <<"## Spring"<<endl
            <<"Stiffness (k) : "<<k<<endl
            <<"Mass (kg) : "<<m<<endl
            <<"Friction (lambda) : "<<lambda<<endl<<endl;

    Oscillator::display(sortie);
    return sortie;
}

void Spring::draw()
{
    support->draw(*this);
}

std::unique_ptr<Spring> Spring::clone() const
{
    return std::unique_ptr<Spring>(new Spring(*this));
}

std::unique_ptr<Oscillator> Spring::copy() const
{
    return clone();
}
