#include "pendulum.h"


Pendulum::Pendulum(std::string n, DrawingSupport* supp, std::size_t dof ,
                   double fr, Vector A , Vector o)
    : Oscillator(n, supp, dof, fr, A, o)
{}
