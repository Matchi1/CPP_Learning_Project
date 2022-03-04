#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace(aircraft->get_flight_num(), std::move(aircraft));
}

bool AircraftManager::move()
{
    for (const auto& [key, value] : aircrafts)
    {
        if(value->move())
        {
            remove_queue.emplace_back(key);
        }
    }
    for (auto flight : remove_queue) 
    {
        remove(flight);
    }
    remove_queue.clear();
    return false;
}

void AircraftManager::remove(const std::string flight_num)
{
    aircrafts.erase(flight_num);
}
