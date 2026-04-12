#pragma once
#include "../service/MathService.h"
#include "httplib.h"

class MathRestController {
private:
    MathService& service;
    httplib::Server svr;
    void setupRoutes();

public:
    explicit MathRestController(MathService& srv);
    void run(int port);
};