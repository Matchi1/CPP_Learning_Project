#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "GL/displayable.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
    , manager {}
    , context_initializer { argc, argv }
    , factory {}
{
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { manager.add(factory.create_random_aircraft(airport)); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('m', []() { GL::change_framerate(-1); });
    GL::keystrokes.emplace('p', []() { GL::change_framerate(1); });
    GL::keystrokes.emplace('P', []() { GL::pause(); });
    GL::keystrokes.emplace('n', [this]() { manager.display_crashes(); });
    for(auto i = 0; i < 8; i++)
    {
        GL::keystrokes.emplace('0' + i, [this, i]() {
            auto airline = factory.get_airlines(i);
            auto count = manager.count_aircrafts(airline);
            std::cout << airline << " : " << count << std::endl;
        });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    assert (airport == nullptr);
    airport = new Airport { &manager, one_lane_airport, Point3D { .0f, .0f, .0f },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraft_manager()
{
    assert (GL::move_queue.find(&manager) == GL::move_queue.end());
    GL::move_queue.emplace(&manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    init_aircraft_manager();

    GL::loop();
}
