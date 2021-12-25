#include "doublependulum.h"
#include "constants.h"
#include "../Display/drawingsupport.h"

using namespace std;

DoublePendulum::DoublePendulum(std::string n, DrawingSupport* supp, double mass1,
                               double mass2, double length1,
                               double length2, Vector A, Vector o)
:Oscillator(n, supp, 2, 0, A, o),
 WeightedPendulum(n, supp, mass1, length1, 0, A, o), m2(mass2), l2(length2)
{}

Vector DoublePendulum::f(double t)
{
    //Ces conditions permettent de remettre les valeurs du pendule entre 0 et 2*PI afin de réduire l'acccumulation d'erreur

    double theta1((m2*g_CONST*cos(P[1]-P[2])*sin(P[2])-(m+m2)*g_CONST*sin(P[1])-m2*l*Q[1]*Q[1]*cos(P[1]-P[2])*sin(P[1]-P[2])-m2*l2*Q[2]*Q[2]*sin(P[1]-P[2]))/((m + m2*sin(P[1]-P[2])*sin(P[1]-P[2]))*l));

    double theta2(((m+m2)*g_CONST*cos(P[1]-P[2])*sin(P[1])-(m+m2)*g_CONST*sin(P[2])+m2*l2*Q[2]*Q[2]*cos(P[1]-P[2])*sin(P[1]-P[2])+(m+m2)*l*Q[1]*Q[1]*sin(P[1]-P[2]))/((m + m2*sin(P[1]-P[2])*sin(P[1]-P[2]))*l2));

    return {theta1, theta2};
}

double DoublePendulum::getL2() const
{
    return l2;
}

ostream& DoublePendulum::display(ostream& sortie) const
{
    sortie	<<"## Double Pendulum"<<endl
            <<"- length 1 (m) :\t"<<l<<endl
            <<"- mass 1 (kg) :\t"<<m<<endl
            <<"- length 2 (m) :\t"<<l2<<endl
            <<"- mass 2 (kg) :\t"<<m2<<endl<<endl;

    Oscillator::display(sortie);
    return sortie;
}

void DoublePendulum::correct()
{
    if(P[1] >= M_PI) setP(getP() + Vector{-2*M_PI, 0});
    if (P[1] < -M_PI) setP(getP() + Vector{+2*M_PI, 0});
    if(P[2] >= M_PI) setP(getP() + Vector{0, -2*M_PI});
    if (P[2] < -M_PI) setP(getP() + Vector{0, +2*M_PI});
}

void DoublePendulum::draw()
{
    support->draw(*this);
}

std::unique_ptr<DoublePendulum> DoublePendulum::clone() const
{
    return std::unique_ptr<DoublePendulum>(new DoublePendulum(*this));
}

std::unique_ptr<Oscillator> DoublePendulum::copy() const
{
    return clone();
}
