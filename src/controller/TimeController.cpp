#include "TimeController.h"
#include "iostream"

using namespace std;

TimeController::TimeController(TimeService &srv) : service(srv) {}

void TimeController::run() {
    cout << "--- Time Management System Started ---\n";
    try {
        cout << "Creating record 1 (12:30:00)...\n";
        service.createTimeRecord(1, "12:30:00");

        cout << "Creating record 2 (14:45:15)...\n";
        service.createTimeRecord(2, "14:45:15");

        cout << "Record 1: " << service.getRecord(1) << "\n";
        cout << "Record 2: " << service.getRecord(2) << "\n";

        int diff = service.getDiffBtwRecord(1, 2);
        cout << "Difference in seconds: " << diff << "\n";

        cout << "Adding 3600 seconds (1 hour) to record 1...\n";
        service.addSecondsToRecord(1, 3600);
        cout << "Updated Record 1: " << service.getRecord(1) << "\n";

        cout << "\nAttempting to create invalid record...\n";
        service.createTimeRecord(3, "invalid:format");

    } catch (const invalid_argument& e) {
        cerr << "[Validation Error]: " << e.what() << "\n";
    } catch (const out_of_range& e) {
        cerr << "[Not Found Error]: " << e.what() << "\n";
    } catch (const exception& e) {
        cerr << "[System Error]: " << e.what() << "\n";
    }
}