#include "tower_sim.hpp"
#include "point.hpp"

void test_generic_point() {
    Point<2, float> p1;
    Point<2, float> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3.; // ou 3.f, ou 3.0 en fonction du type de Point
    std::cout << p3.x() << std::endl;
}

int main(int argc, char** argv)
{
    test_generic_point();
    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}
