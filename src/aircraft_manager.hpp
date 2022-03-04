#pragma once

#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::unordered_map<std::string, std::unique_ptr<Aircraft>> aircrafts;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    void remove(const std::string flight_num);
    void move() override;
};

inline std::vector<std::string> remove_queue;