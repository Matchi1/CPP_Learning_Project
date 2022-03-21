#include "tower.hpp"

#include "airport.hpp"
#include "terminal.hpp"

#include <cassert>

WaypointQueue Tower::get_circle() const
{
    return { { Point3D { -1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, 1.5f, .5f }, wp_air },
             { Point3D { -1.5f, 1.5f, .5f }, wp_air } };
}

WaypointQueue Tower::get_instructions(Aircraft& aircraft)
{
    aircraft.waiting = false;
    if (!aircraft.is_at_terminal)
    {
        // if the aircraft is far, then just guide it to the airport vicinity
        if (aircraft.distance_to(airport.pos) < 5)
        {
            // try and reserve a terminal for the craft to land
            const auto vp = airport.reserve_terminal(aircraft);
            if (!vp.first.empty())
            {
                reserved_terminals.emplace(&aircraft, vp.second);
                return vp.first;
            }
            else
            {
                aircraft.waiting = true;
                return get_circle();
            }
        }
        else
        {
            aircraft.waiting = true;
            return get_circle();
        }
    }
    else
    {
        // get a path for the craft to start
        const auto it = reserved_terminals.find(&aircraft);
        assert(it != reserved_terminals.end());
        const auto terminal_num = it->second;
        Terminal& terminal      = airport.get_terminal(terminal_num);
        if (!terminal.is_servicing())
        {
            terminal.finish_service();
            reserved_terminals.erase(it);
            aircraft.is_at_terminal = false;
            return airport.start_path(terminal_num);
        }
        else
        {
            return {};
        }
    }
}

void Tower::arrived_at_terminal(const Aircraft& aircraft)
{
    const auto it = reserved_terminals.find(&aircraft);
    assert(it != reserved_terminals.end());
    airport.get_terminal(it->second).start_service(aircraft);
}

void Tower::remove_aircraft(const Aircraft& aircraft)
{
    // get a path for the craft to start
    if(aircraft.has_terminal())
    {
        const auto it = reserved_terminals.find(&aircraft);
        assert(it != reserved_terminals.end());
        const auto terminal_num = it->second;
        auto& terminal          = airport.get_terminal(terminal_num);
        terminal.remove_craft();
        reserved_terminals.erase(it);
    }
}

WaypointQueue Tower::reserve_terminal(Aircraft& aircraft)
{
    // try and reserve a terminal for the craft to land
    const auto vp = airport.reserve_terminal(aircraft);
    if (!vp.first.empty())
    {
        reserved_terminals.emplace(&aircraft, vp.second);
        return vp.first;
    }
    return {};
}