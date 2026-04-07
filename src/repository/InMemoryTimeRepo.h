#pragma once
#include "ITimeRepo.h"
#include "unordered_map"

class InMemoryTimeRepo : public ITimeRepository {
private:
    std::unordered_map<int, Time> db;
public:
    void save(int id, const Time& time) override;
    Time get(int id) const override;
    bool exists(int id) const override;
};