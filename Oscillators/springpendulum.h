#ifndef SPRINGPENDULUM_H
#define SPRINGPENDULUM_H

#include "pendulum.h"
#include "spring.h"

class DrawingSupport;

//!SpringPendulum class
class SpringPendulum: public Pendulum, public Spring
{
private:
    //!length at rest of spring
    double L;

public:
    //!constructor
    SpringPendulum(std::string n, DrawingSupport* supp, double masse,
                   double cst, double length = 1,
                   Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

    //!equation of motion
    Vector f(double t) override;

    //!for polymorphic copy
    std::unique_ptr<SpringPendulum> clone() const;
    virtual std::unique_ptr<Oscillator> copy() const override;

    //!to display text
    std::ostream& display(std::ostream& sortie) const override;

    //!calls the appropriate DrawingSupport method
    void draw() override;
};

#endif // SPRINGPENDULUM_H
