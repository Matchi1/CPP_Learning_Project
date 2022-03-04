#pragma once

#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::unordered_map<std::string, std::unique_ptr<Aircraft>> aircrafts;
    std::vector<std::string> remove_queue;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    void remove(const std::string flight_num);
    bool move() override;
};