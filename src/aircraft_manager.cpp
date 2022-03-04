#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace(aircraft->get_flight_num(), std::move(aircraft));
}

void AircraftManager::move()
{
    for (const auto& [key, value] : aircrafts)
    {
        value->move();
    }
    for (auto flight : remove_queue) 
    {
        remove(flight);
    }
    remove_queue.clear();
}

void AircraftManager::remove(const std::string flight_num)
{
    aircrafts.erase(flight_num);
}
