#include "pendulum.h"


Pendulum::Pendulum(DrawingSupport* supp, std::size_t dof ,
                   double fr, Vector A , Vector o)
    : Oscillator(supp, dof, fr, A, o)
{}
