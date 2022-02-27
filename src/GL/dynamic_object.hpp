#pragma once

#include <unordered_set>

namespace GL {

class DynamicObject
{
public:
    virtual ~DynamicObject() {}

    virtual void move() = 0;
};

inline std::unordered_set<DynamicObject*> move_queue;
inline std::unordered_set<void*> remove_queue;

} // namespace GL
