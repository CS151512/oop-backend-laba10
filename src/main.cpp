#include "./repository/InMemoryTimeRepo.h"
#include "./service/TimeService.h"
#include "./controller/TimeController.h"

int main() {
    InMemoryTimeRepo repo;
    TimeService service(repo);
    TimeController controller(service);

    controller.run();

    return 0;
}