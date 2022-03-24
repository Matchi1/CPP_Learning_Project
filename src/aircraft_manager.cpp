#include "aircraft_manager.hpp"

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool sort_aircrafts(const std::unique_ptr<Aircraft>& a, const std::unique_ptr<Aircraft>& b)
{
    if (a->has_terminal())
    {
        if (b->has_terminal())
        {
            return a->get_fuel() < b->get_fuel();
        }
        else
        {
            return true;
        }
    }
    else
    {
        if (b->has_terminal())
        {
            return false;
        }
        else
        {
            return a->get_fuel() < b->get_fuel();
        }
    }
}

bool AircraftManager::move()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](std::unique_ptr<Aircraft>& aircraft) { return aircraft->move(); }),
                    aircrafts.end());
    std::sort(aircrafts.begin(), aircrafts.end(), sort_aircrafts);
    for (const auto& a : aircrafts)
    {
        std::cout << a->has_terminal() << "/" << a->get_fuel() << std::endl;
    }
    std::cout << "------------------" << std::endl;
    return false;
}

int AircraftManager::count_aircrafts(std::string airline)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [airline](std::unique_ptr<Aircraft>& aircraft)
                         { return aircraft->get_flight_num().substr(0, 2) == airline; });
}

int AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                           [](int res, const std::unique_ptr<Aircraft>& aircraft) { return res + 3000 - aircraft->get_fuel(); });
}
