#pragma once
#include "iostream"
#include "string"

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize();
public:
    Time();
    Time(int h, int m, int s);
    Time(int totalSeconds);
    Time(const std::string& timeStr);
    Time(const Time& other);
    ~Time() = default;

    int toSeconds() const;
    int toMinutes() const;
    int diffInSeconds(const Time& other) const;
    Time addSeconds(int s) const;
    Time subSeconds(int s) const;

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& t);
    friend std::istream& operator>>(std::istream& in, Time& t);
};