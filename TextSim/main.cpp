#include "../Oscillators/weightedpendulum.h"
#include "../Oscillators/doublependulum.h"
#include "../Oscillators/spring.h"
#include "../Oscillators/springpendulum.h"

#include "../Simulation/integratoreuler.h"
#include "../Simulation/system.h"

#include "../Display/drawingsupport.h"
#include "../Simulation/vector.h"
#include <string>



using namespace std;

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
