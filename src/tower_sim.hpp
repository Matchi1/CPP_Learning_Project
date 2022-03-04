#pragma once

#include "aircraft_manager.hpp"
#include "aircraft_factory.hpp"

#include <memory>
#include <vector>

class Airport;
class Aircraft;
struct AircraftType;

class ContextInitializer {
    public:
        ContextInitializer(int argc, char** argv) {
            MediaPath::initialize(argv[0]);
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            GL::init_gl(argc, argv, "Airport Tower Simulation");
        }
};

class TowerSimulation
{
private:
    bool help                = false;
    Airport* airport         = nullptr;
    AircraftManager* manager = nullptr;
    ContextInitializer context_initializer;
    AircraftFactory factory;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_keystrokes() const;
    void display_help() const;

    void init_airport();
    void init_aircraft_manager();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
