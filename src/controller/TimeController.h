#pragma once
#include "../service/TimeService.h"

class TimeController {
private:
    TimeService& service;
public:
    explicit TimeController(TimeService& service);
    void run();
};