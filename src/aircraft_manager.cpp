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

int AircraftManager::count_aircrafts(std::string airline)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
    [airline](std::unique_ptr<Aircraft>& aircraft){ return aircraft->get_flight_num().substr(0, 2) == airline;});
}