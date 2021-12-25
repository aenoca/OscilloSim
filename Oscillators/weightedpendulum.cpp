#include "weightedpendulum.h"
#include "constants.h"
#include "../Display/drawingsupport.h"

using namespace std;

//!call to base class oscillator here bc virtual inheritance
//!1 here is the dof
WeightedPendulum::WeightedPendulum(std::string n, DrawingSupport* supp, double mass ,
                 double length , double fr, Vector A, Vector o)
:Oscillator(n, supp, 1, fr, A, o), Pendulum(n, supp, 1, fr, A, o), m(mass), l(length)
{}

//!equation of motion
Vector WeightedPendulum::f(double t)
{
    //theta.. = (-lambda / m*L^2) * theta. - g * 1/L * sin(theta)
    return Vector({(-lambda) / (m*l*l) * Q[1] - g_CONST * (1/l) * sin(P[1])});
}

//!getter for length
double WeightedPendulum::getL() const
{
    return l;
}

//!corrects angles to interval [-pi, pi]
void WeightedPendulum::correct()
{
    if(P[1] >= M_PI) setP(Vector{P[1] - 2*M_PI});
    else if (P[1] < -M_PI) setP(Vector{P[1] + 2*M_PI});
}

//!display pendulum properties
ostream& WeightedPendulum::display(ostream& sortie) const
{
    sortie  <<"## Weighted Pendulum"<<endl
            <<"Length (m) : "<<l<<endl
            <<"Mass (kg) : "<<m<<endl
            <<"Friction (lambda) : "<<lambda<<endl<<endl;

    Oscillator::display(sortie);
    return sortie;
}


void WeightedPendulum::draw()
{
    support->draw(*this);
}

std::unique_ptr<WeightedPendulum> WeightedPendulum::clone() const
{
    return std::unique_ptr<WeightedPendulum>(new WeightedPendulum(*this));
}

std::unique_ptr<Oscillator> WeightedPendulum::copy() const
{
    return clone();
}
