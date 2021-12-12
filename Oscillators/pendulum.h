#ifndef PENDULUM_H
#define PENDULUM_H

#include "oscillator.h"

class DrawingSupport;
class Vector;

//!abstract class for pendulums. Virtual inheritance useful when
//!class inherits from two that both inherit from same
//!(diamond inheritance)
class Pendulum : public virtual Oscillator
{
public:
    //Constructeur
    Pendulum(DrawingSupport* supp, std::size_t dof ,
            double fr, Vector A , Vector o);
};

#endif // PENDULUM_H
