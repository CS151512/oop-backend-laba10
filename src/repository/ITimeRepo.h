#pragma once
#include "../domain/Time.h"

class ITimeRepository {
public:
    virtual ~ITimeRepository() = default;
    virtual void save(int id, const Time& time) = 0;
    virtual Time get(int id) const = 0;
    virtual bool exists(int id) const = 0; 
};