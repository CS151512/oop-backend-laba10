#pragma once
#include "../repository/ITimeRepo.h"
#include "string"

class TimeService {
private:
    ITimeRepository& repo;
public:
    explicit TimeService(ITimeRepository& repository);

    void createTimeRecord(int id, const std::string& timeStr);
    int getDiffBtwRecord(int id_1,int id_2) const;
    void addSecondsToRecord(int id, int seconds);
    Time getRecord(int id) const;
};