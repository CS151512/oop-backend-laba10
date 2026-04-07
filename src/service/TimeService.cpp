#include "TimeService.h"

using namespace std;

TimeService::TimeService(ITimeRepository &repository)
: repo(repository) {}

void TimeService::createTimeRecord(int id, const std::string &timeStr) {
    Time newTime(timeStr);
    repo.save(id, newTime);
}

int TimeService::getDiffBtwRecord(int id_1, int id_2) const {
    Time t1 = repo.get(id_1);
    Time t2 = repo.get(id_2);
    return t1.diffInSeconds(t2);
}

void TimeService::addSecondsToRecord(int id, int seconds) {
    Time t = repo.get(id);
    repo.save(id, t.addSeconds(seconds));
}

Time TimeService::getRecord(int id) const {
    return repo.get(id);
}