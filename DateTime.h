#pragma once
#include<iostream>
#include <chrono>
#include <ctime>
using namespace std;
class Time {
public:
    int hours;
    int minutes;
    int seconds;

    Time(int h=0, int m=0, int s=0) : hours(h), minutes(m), seconds(s) {}

    void display() const {
        std::cout << hours << ":" << minutes << ":" << seconds;
    }

    bool operator<(const Time& other) const {
        if (hours != other.hours) return hours < other.hours;
        if (minutes != other.minutes) return minutes < other.minutes;
        return seconds < other.seconds;
    }

    bool operator>(const Time& other) const {
        return other < *this;
    }

    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
    }

    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

    friend std::istream& operator>>(std::istream& in, Time& time) {
        char colon;
        in >> time.hours >> colon >> time.minutes >> colon >> time.seconds;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Time& time) {
        out << time.hours << ":" << time.minutes << ":" << time.seconds;
        return out;
    }
};

class Date {
public:
    int day;
    int month;
    int year;

    Date(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {}

    void display() const {
        std::cout << day << "/" << month << "/" << year;
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator>(const Date& other) const {
        return other < *this;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    friend std::istream& operator>>(std::istream& in, Date& date) {
        char slash;
        in >> date.day >> slash >> date.month >> slash >> date.year;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Date& date) {
        out << date.day << "/" << date.month << "/" << date.year;
        return out;
    }
};

class DateTime 
{
private:
    Date date;
    Time time;
public:
    DateTime() {}

    DateTime(const Date& d, const Time& t) : date(d), time(t) {}

    // Constructor to initialize with the current system date and time
    DateTime(bool initializeWithSystemDateTime) 
    {
        if (initializeWithSystemDateTime) {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            struct tm timeInfo;

            // Use localtime_s for thread-safe localtime in Windows
            if (localtime_s(&timeInfo, &now) == 0) {
                date = Date(timeInfo.tm_mday, timeInfo.tm_mon + 1, timeInfo.tm_year + 1900);
                time = Time(timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
            }
            else {
                // Handle error, e.g., throw an exception or set default values
                cout << "Error getting local time." << endl;
                //date = Date(0, 0, 0);
                //time = Time(0, 0, 0);
            }
        }
    }

    void display() const 
    {
        date.display();
        cout << " ";
        time.display();
        cout << endl;
    }

    bool operator<(const DateTime& other) const {
        if (date != other.date) return date < other.date;
        return time < other.time;
    }

    bool operator>(const DateTime& other) const {
        return other < *this;
    }

    bool operator==(const DateTime& other) const {
        return date == other.date && time == other.time;
    }

    bool operator!=(const DateTime& other) const {
        return !(*this == other);
    }

    friend istream& operator>>(istream& in, DateTime& dateTime) {
        cout << "Enter date and time in the format (DD/MM/YYYY HH:MM:SS): ";
        in >> dateTime.date >> dateTime.time;
        return in;
    }

    friend ostream& operator<<(ostream& out, const DateTime& dateTime) {
        out << dateTime.date << " " << dateTime.time;
        return out;
    }
};