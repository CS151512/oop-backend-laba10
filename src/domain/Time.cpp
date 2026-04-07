#include "Time.h"
#include "stdexcept"
#include "iomanip"
#include "sstream"
#include "cmath"

using namespace std;

void Time::normalize() {
    if (seconds < 0) {
        int minsToSub = (-seconds + 59) / 60;
        minutes -= minsToSub;
        seconds += minsToSub * 60;
    }
    if (minutes < 0) {
        int minsToSub = -minutes;
        minutes = 0;
        seconds -= minsToSub * 60;
    }
    hours = (hours % 24 + 24) % 24;
    minutes %= 60;
    seconds %= 60;
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
