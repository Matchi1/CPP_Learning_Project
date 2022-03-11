#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::move()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), 
                              aircrafts.end(),
                              [](std::unique_ptr<Aircraft>& aircraft){return aircraft->move();}),
                              aircrafts.end());
    return false;
}