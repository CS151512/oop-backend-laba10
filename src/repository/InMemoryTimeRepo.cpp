#include "InMemoryTimeRepo.h"
#include "stdexcept"

void InMemoryTimeRepo::save(int id, const Time& time) {
    db[id] = time;
}

Time InMemoryTimeRepo::get(int id) const {
    if (!exists(id)) {
        throw std::out_of_range("No records found");
    }
    return db.at(id);
}

bool InMemoryTimeRepo::exists(int id) const {
    return db.find(id) != db.end();
}
