#pragma once

#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int number_crashes = 0;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    bool move() override;
    int count_aircrafts(std::string airline);
    int get_required_fuel() const;
    void display_crashes() const;

    friend class Airport;
};
