#include "oscillator.h"
#include "../Display/drawingsupport.h"

using namespace std;

//Constructeur avec nb_degre
Oscillator::Oscillator(std::string n, DrawingSupport* supp, size_t dof , double fr,
                       Vector A , Vector o)
:Drawable(supp), name(n), P(dof), Q(dof)
{
    if(o.size() != 3){
        throw string("Tried to initialize origin Vector O to size different than 3");
    } else{
         O = o;
    }
    if(A.size() == 3){
        a = A.unit();
    } else{
        throw string("Tried to initialize direction Vector a to size different than 3");
    }

    if (fr < 0) throw string("Friction coefficient cannot be negative");
    else lambda = fr;
}

Vector Oscillator::getP() const { return P; }
Vector Oscillator::getQ() const { return Q; }
Vector Oscillator::getO() const { return O; }
Vector Oscillator::getA() const { return a; }


void Oscillator::setP(Vector const& vec)
{
    if(vec.size()==P.size())
    {
        P=vec;
    }
    else
    {
        throw string("Error, assignement of Vector of different size than P");
    }
}

void Oscillator::setQ(Vector const& vec)
{
    if(vec.size()==Q.size())
    {
        Q=vec;
    }
    else
    {
        throw string("Error, assignement of Vector of different size than Q");
    }
}

void Oscillator::drawPhase()
{
    support->drawPhase(*this);
}

void Oscillator::addPoint(double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;
    curve.push_back(p);
}

const std::vector<Point>& Oscillator::getCurve() const
{
    return curve;
}

//surcharge de l'operateur d'affichage <<

ostream& Oscillator::display(ostream& output) const
{
    output<<"	-position: \t"<< P <<endl;

    output<<"	-velocity: \t"<< Q <<endl;

    return output;
}

ostream& operator<<(ostream& output, Oscillator const& osc)
{
    return osc.display(output);
}
