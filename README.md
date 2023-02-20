# OscilloSim

OscilloSim is a program that allows to simulate the time evolution of different type of oscillators. There are 4 different types of oscillators available to simulate:
- ``WeightedPendulum`` : A simple pendulum. A weight is a attached to end of a rod of fixed length and can swing freely or with friction. The pendulum is subject to gravity. It has one degree of freedom, the angle of the rod with respect to the vector defined by gravity.
- ``DoublePendulum`` : Two rods and two weights. The second mass is attached to the end of the second rod which can swing freely around the first mass. The pendulum is subject to gravity. It has two degrees of freedom, the angle of the first rod with respect to the vector defined by gravity and the angle of the second rod with respect to the first rod.
- ``Spring`` : A simple spring with a mass. The length at rest is zero. The spring is forced to oscillate along an axis. There may be friction involved. The pendulum is subject to gravity. It has one degree of freedom, the position along the direction of the axis formed by the spring.
- ``SpringPendulum`` : A spring that is free to oscillate in a two dimensional plane. It has a non-zero length at rest. The pendulum is subject to gravity. It has two degrees of freedom, the x and y positions of the mass at the end of the spring. In this case the y direction is the same as gravity.

The time evolution computations are performed using integrators. There are 4 integrators available for use:
- `IntegratorEuler` : A Euler integrator.
- `IntegratorEulerCromer` : A Euler-Cromer integrator.
- `IntegratorNewmark` : A Newmark integrator.
- `IntegratorRungeKutta` : A RK4 integrator.

There are two different ways of simulating the oscillators, either by a text simulation or by a visual simulation. We start by explaining how to perform a text simulation.

## TextSim
Go in the TextSim folder. In order to run the simulation, two steps need to be taken :
1. make the libraries : ``make -f maketext.mk libs``
2. make the main executable : ``make -f maketext.mk``

Then one can simply run ``./OscilloSimText``

The program is contained within the TextSim/main.cpp file. Let's take a look at the code :

First we must include the important files :
```
#include "../Oscillators/weightedpendulum.h"
#include "../Oscillators/doublependulum.h"
#include "../Oscillators/spring.h"
#include "../Oscillators/springpendulum.h"

#include "../Simulation/integratoreuler.h"
#include "../Simulation/system.h"

#include "../Display/drawingsupport.h"
#include "../Simulation/vector.h"
#include <string>
```

In the main, we have :
```
int main(int argc, char *argv[])
{
// 1 - define drawing support, define and initialize oscillators
FileLogger t;
WeightedPendulum p("pendulum", &t, 1.0, 1.0);
Vector Q = {1.0};
p.setQ(Q);

DoublePendulum dp("doublependulum", &t, 1.0, 1.0, 1.0, 1.0);
Vector Q2 = {1.0, -1.0};
dp.setQ(Q2);

Spring sp("spring", &t, 1.0, 1.0);
Vector Q3 = {-1.0};
sp.setQ(Q3);

SpringPendulum spp("springpendulum", &t, 1.0, 1.0, 1.0);
Vector P4 = {1.0, 1.0};
spp.setP(P4);

// 2 - add oscillators to system
System s(&t, new IntegratorEuler());
s.addOscillo(p);
s.addOscillo(dp);
s.addOscillo(sp);
s.addOscillo(spp);
s.draw();

// 3 - simulate the system
double sim_time = 5.0;
double time = 0.0;
double dt = 0.01;

while(time < sim_time){
    s.evolve(dt, time);
    s.draw();
    time += dt;
    cout<<time<<endl;
}

return 0;
}
```
This may be a bit scary on first approach so let's break it down into pieces.

In the first part, we define the oscillators and set their initial velocities. We also define the ``DrawingSupport``, i.e. where the position and velocities of the oscillators over time are displayed / saved. In this example, it is a ``FileLogger``, so the output of the simulation is saved in a file format. The constructor of the different oscillators are :
```
WeightedPendulum(std::string n, DrawingSupport* supp, double mass, double length , double fr = 0 , Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

DoublePendulum(std::string n, DrawingSupport* supp, double mass1, double mass2, double length1, double length2, Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

Spring(std::string n, DrawingSupport* supp, double m, double cst, double fr = 0, Vector A = {1, 0, 0}, Vector o = {0, 0, 0});

SpringPendulum(std::string n, DrawingSupport* supp, double masse, double cst, double length = 1, Vector A = {1, 0, 0}, Vector o = {0, 0, 0});
```

The ``string n`` argument is the name of the oscillator, which is then used for the name of the output files. The ``DrawingSupport* supp`` defines the medium through which the simulation is saved or displayed. The ``Vector A``, combined with the vector of gravity ``g = {0, 0, -9.81}`` forms the plane in which the oscillators evolve. Additionally, a ``Spring`` is forced to oscillate along the direction of this vector. The ``Vector o`` defines the origin of the oscillator, i.e., the point around which it swings. For ``Spring`` and ``SpringPendulum``, the ``cst`` value is the spring constant.

It is possible to set the positions and the velocities of the oscillators using ``setP(Vector)`` and ``setQ(Vector)``. It is important to know that the position is always defined with respect to the origin. The size of the ``Vector`` must be the same as the number of degrees of freedom of the oscillator. If the original value is an angle, then its corresponding velocity is an angular velocity.

In the second part, we define a ``System``, which contains oscillators. It is initialized with an Integrator. The respective oscillators are then added to the system. The system is drawn once. In this case, it means it outputs the positions and velocities of each oscillator in the system to a file.

In the third part, we define the total simulation time, the initial time and the time step. The system is integrated and drawn over the time of the simulation.

## VisualSim

Instead of having to write down the oscillators and the initial conditions for each oscillator in c++, which is annoying, a user interface was developed using Qt and the simulated oscillators are rendered using OpenGL.

In order to run the user interface, Qt6 needs to be downloaded on your computer and mingw32-make available.

In the Qt console, in the base folder,
1. run the ``qmake`` command
2. run the ``mingw32-make`` (or simply ``make`` for linux-based systems) command and wait for the console to settle down
3. cd into the ``VisualSim/release`` folder and execute the ``OscilloSim`` executable.

A window like to following should open:
![The homepage of OscilloSim software. One can see a representation of the 4 oscillators.](pics/homepage.JPG)

When you click on the ``next`` button, we get to the page to select oscillators. They are the following:

![Pendulum Page](pics/WeightedPendulum.JPG)

![Spring Page](pics/Spring.JPG)

![Double Pendulum Page](pics/DoublePendulum.JPG)

![Spring Pendulum Page](pics/SpringPendulum.JPG)


The vector O is the fixing point of the oscillator. The vector A is has two purposes :
- for the pendulums and the spring pendulum, it defines the plane in which the oscillators evolve (also using the direction of gravity).
- for the spring, it defines the direction along which the oscillation occurs.

The position/velocity vector has different meanings :
- For the Pendulum, the position is the angle in radians between the rod and the direction of gravity. The velocity is simply the angular velocity.
- For the Spring, the position in meters is the distance from the fixing point along the vector A. It should not be set to zero. The velocity is the change in position along the vector A.
- For the DoublePendulum, the first element of the position is the angle in radians between the rod and the direction of gravity. The second element of the position is the angle in radians between the second rod and the first rod. The velocity is simply the time derivative of the angles.
- For the SpringPendulum, the position has two entries in meters. The second is the distance along the direction of gravity. The first is the distance from the origin along the plane formed by gravity and the vector A, and perpendicular to the vector of gravity. The position should not be zero.

For the two springs, the position is given with respect to the fixing point.

In order to launch a simulation with an oscillator, one must specify the initial conditions and the properties of the oscillator. Then, one presses the ``Add`` button. If the one wishes to remove the oscillator, one can press the ``Remove last`` button. Finally, when all oscillators of interest (can add any type of oscillator at the same time) are added, one can choose the integrator and then launch the simulation. When the simulation is launched, a new window opens with the oscillators. There are a few controls to move around in the rendering window:

- home : return to initial view.
- space : pause/restart the simulation.
- click and drag mouse : rotation around current position depending on motion of mouse.
- scroll : move in or out of view.
- arrows : small rotation around current position.

- s : move back in the view.
- w : move forward in the view.
- a : move left in the view.
- d : move right in the view.
- r : move up in the view.
- f : move down in the view.
- q : roll left around axis colinear with view.
- e : roll right around axis colinear with view.

- j : use Euler integrator.
- u : use Euler-cromer integrator.
- n : use Newmark integrator.
- k : use Runge-Kutta integrator.

If one presses the ``launch`` button again while the simulation is ongoing, this updates the integrator to the current selection.

The OpenGL window opened when launching the simulation looks like this :

![Simulation Window](pics/window.JPG)

The white object is a DoublePendulum, the blue object is a WeightedPendulum, the horizontal red object is a Spring, while the other one is a SpringPendulum.

## Additional notes
This project was done using the Open-source version of Qt and is not meant for lucrative ventures.

The project was originally done using QT4, and was transferred to QT6. There is some functionality that does not work in this version for reasons yet unknown (there used to be a grid to better visualize the oscillators).


Aurelio Noca

Louis Jaugey