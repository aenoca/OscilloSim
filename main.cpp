#include "Oscillators/weightedpendulum.h"
#include "Oscillators/doublependulum.h"
#include "Simulation/integratoreuler.h"
#include "Simulation/system.h"
#include "Display/drawingsupport.h"
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    TextViewer t(std::cout);
    WeightedPendulum p(&t, 1.0, 1.0);
    Vector Q = {1.0};
    p.setQ(Q);

    DoublePendulum dp(&t, 1, 1, 1, 1);
    Vector Q2 = {1.0, -1.0};
    dp.setQ(Q2);

    double sim_time = 5.0;
    double time = 0.0;
    double dt = 0.01;

    System s(&t, new IntegratorEuler());
    s.addOscillo(p);
    s.addOscillo(dp);
    s.draw();

    while(time < sim_time){
        s.evolve(dt, time);
        s.draw();
        time += dt;
        cout<<time<<endl;
    }


    return 0;

}
