#pragma once

#include "aircraft_manager.hpp"
#include "airport.hpp"

constexpr size_t NUM_AIRCRAFT_TYPES = 3;

class AircraftFactory {
    public:
        AircraftFactory ();
        std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport) const;
        std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport) const;

    private:
        const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
        AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES];
};
