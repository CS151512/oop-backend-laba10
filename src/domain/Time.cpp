#include "Time.h"
#include "stdexcept"
#include "iomanip"
#include "sstream"
#include "cmath"

using namespace std;

const int SECONDS_IN_DAY = 86400;

void Time::normalize() {
    int total_s = hours * 3600 + minutes * 60 + seconds;

    total_s = (total_s % SECONDS_IN_DAY + SECONDS_IN_DAY) % SECONDS_IN_DAY;

    hours = total_s / 3600;
    minutes = (total_s % 3600) / 60;
    seconds = total_s % 60;
}

Time::Time() : hours(0), minutes(0), seconds(0) {}

Time::Time(int h, int m, int s): hours(h), minutes(m), seconds(s) {
    if (h < 0 || m < 0 || s < 0) {
        throw invalid_argument("Time elements cannot be negative");
    }
    normalize();
}

Time::Time(int totalSeconds) : hours(0), minutes(0), seconds(totalSeconds) {
    normalize();
}

Time::Time(const string& timeStr) {
    char delimiter1, delimiter2;
    stringstream ss(timeStr);
    if (!(ss >> hours >> delimiter1 >> minutes >> delimiter2 >> seconds) ||
        delimiter1 != ':' || delimiter2 != ':') {
        throw invalid_argument("Invalid format. Expected hh:mm:ss.");
        }
    normalize();
}

Time::Time(const Time& other) : hours(other.hours), minutes(other.minutes), seconds(other.seconds) {}

int Time::toSeconds() const {return hours * 3600 + minutes * 60 + seconds;}
int Time::toMinutes() const {return (toSeconds() + 30) / 60;}
int Time::diffInSeconds(const Time &other) const {return abs(this -> toSeconds() - other.toSeconds());}
Time Time::addSeconds(int s) const {return Time(this -> toSeconds() + s);}
Time Time::subSeconds(int s) const {return Time(this -> toSeconds() - s);}


bool Time::operator==(const Time &other) const {return toSeconds() == other.toSeconds();}
bool Time::operator!=(const Time &other) const {return !(*this == other);}
bool Time::operator<(const Time &other) const {return toSeconds() < other.toSeconds();}
bool Time::operator>(const Time &other) const {return toSeconds() > other.toSeconds();}


ostream& operator<<(ostream& out, const Time &t) {
    out << setfill('0') << setw(2) << t.hours << ":"
        << setfill('0') << setw(2) << t.minutes << ":"
        << setfill('0') << setw(2) << t.seconds;
    return out;
}

istream& operator>>(istream& in, Time &t) {
    string timeStr;
    in >> timeStr;
    t = Time(timeStr);
    return in;
}
