#ifndef WEIGHTEDPENDULUM_H
#define WEIGHTEDPENDULUM_H

#include "pendulum.h"
//#include "../Simulation/vector.h"

class DrawingSupport;

//!WeightedPendulum class
class WeightedPendulum : public Pendulum
{
protected:
    //!mass
    double m;

    //!length
    double l;
public:
    //Constructeur
    WeightedPendulum(std::string n, DrawingSupport* supp, double mass ,
                     double length , double fr = 0 ,
                     Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

    //!equation of motion
    Vector f(double t) override;

    //getter
    double getL() const;

    //!corrects angles to interval [-pi, pi]
    void correct() override;

    //!methods for polymorphic copy
    std::unique_ptr<WeightedPendulum> clone() const;
    virtual std::unique_ptr<Oscillator> copy() const override;

    //!display in text form
    std::ostream& display(std::ostream& output) const override;

    //!calls the appropriate drawing method in the DrawingSupport
    void draw() override;

};

#endif // WEIGHTEDPENDULUM_H
